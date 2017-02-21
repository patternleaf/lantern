//
//  LanternState.cpp
//  lantern
//
//  Created by Eric Miller on 1/24/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

#include "LanternState.hpp"
#include "LanternEffect.hpp"
#include "EffectRegistry.hpp"

using namespace nlohmann;
using namespace std;
using namespace std::chrono;

const string kFilename = "lantern-state.json";

LanternState::LanternState(LanternServer* server, LanternMixer* mixer)
: mServer(server), mMixer(mixer), mRunning(true), mIsDirty(false)
{
	for (int i = 0; i < mMixer->numChannels(); i++) {
		LanternEffect* effect = dynamic_cast<LanternEffect*>(mMixer->getEffect(i));
		if (effect) {
			effect->subscribe([this, i](json event) {
				json message;
				message["event"] = "effectEvent";
				message["channel"] = i;
				message["effect"] = event;
				mServer->broadcast(message);
			});
		}
	}
	
	mPersistenceThread = thread(bind(&LanternState::persistenceWorker, this));
}

LanternState::~LanternState()
{
	mRunning = false;
	mPersistenceThread.join();
}

void LanternState::loadFromFile(std::string fileName)
{
	ifstream file(kFilename);
	json state;
	file >> state;
	setWith(state);
}

void LanternState::persistenceWorker()
{
	while (mRunning) {
		this_thread::sleep_for(seconds(1));
		if (mIsDirty) {
			
			
			ofstream file(kFilename);
			cout << "writing state to file" << endl;
			file << toJson();
			file.close();
			
			// TODO: dirty flag is unguarded. we could miss a change. :(
			mIsDirty = false;
		}
	}
}

void LanternState::setFader(int channel, float value)
{
	lock_guard<mutex> lock(mStateMutex);
	
	mMixer->setFader(channel, value);
	mIsDirty = true;
}

void LanternState::setEffect(string id, json effectJson)
{
	lock_guard<mutex> lock(mStateMutex);
	
	LanternEffect* effect = EffectRegistry::shared()->findEffect(id);
	if (effect) {
		effect->cacheStateUpdate(effectJson);
		mIsDirty = true;
	}
	else {
		cout << "No effect found with id " << id << endl;
	}
	
}

void LanternState::setWith(json newJson)
{
	lock_guard<mutex> lock(mStateMutex);
	
	json channels = newJson["channels"];
	
	mMixer->clear();
	
	for (auto it = channels.begin(); it != channels.end(); it++) {
		LanternEffect* effect = EffectRegistry::shared()->createEffect((*it)["effectKey"]);
		if (effect) {
			effect->cacheStateUpdate((*it)["effect"]);
			mMixer->add(effect, (*it)["fader"]);
		}
	}
}

json LanternState::toJson()
{
	lock_guard<mutex> lock(mStateMutex);
	
	json channels = json::array();
	
	LanternEffect* effect = nullptr;
	for (int i = 0; i < mMixer->numChannels(); i++) {
		json channel = json::object();
		
		channel["fader"] = mMixer->getFader(i);
		
		effect = dynamic_cast<LanternEffect*>(mMixer->getEffect(i));
		if (effect != nullptr) {	
			channel["effect"] = effect->getState();
			channel["effectKey"] = effect->getFactory().first;
		}
		else {
			channel["effect"] = {{ "id", "unknown-effect" }};
			channel["effectKey"] = "unknown";
		}
		
		channels.push_back(channel);
	}
	
	return {{ "channels", channels }};
}

