//
//  LanternState.hpp
//  lantern
//
//  Created by Eric Miller on 1/24/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef LanternState_hpp
#define LanternState_hpp

#include <stdio.h>
#include <mutex>
#include <thread>
#include "lib/effect_runner.h"

#include "JsonConversions.hpp"

#include "LanternMixer.hpp"
#include "LanternServer.hpp"

class LanternState {
public:
	LanternState(LanternServer* server, LanternMixer* mixer);
	~LanternState();
	
	void setWith(nlohmann::json json);
	
	void setFader(int channel, float value);
	void setEffect(std::string id, nlohmann::json effect);
	
	nlohmann::json toJson();
	
	void loadFromFile(std::string fileName = "lantern-state.json");
	
private:
	void persistenceWorker();
	std::thread mPersistenceThread;
	bool mRunning;
	bool mIsDirty;

	LanternServer* mServer;
	LanternMixer* mMixer;
	
	std::mutex mStateMutex;
};


#endif /* LanternState_hpp */
