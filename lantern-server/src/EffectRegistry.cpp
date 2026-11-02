//
//  EffectRegistry.cpp
//  lantern
//
//  Created by Eric Miller on 2/9/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include <functional>
#include "EffectRegistry.hpp"
#include "LanternEffect.hpp"
#include "EffectParameter.hpp"
#include <string>
#include <uuid/uuid.h>

using namespace std;

EffectRegistry* EffectRegistry::sSingleton = nullptr;

EffectRegistry::EffectRegistry()
{
	
}

EffectRegistry::~EffectRegistry()
{
	for (auto it = mEffects.begin(); it != mEffects.end(); it++) {
		delete it->second;
	}
}

EffectRegistry* EffectRegistry::shared()
{
	if (EffectRegistry::sSingleton == nullptr) {
		EffectRegistry::sSingleton = new EffectRegistry();
	}
	return EffectRegistry::sSingleton;
}

LanternEffect* EffectRegistry::createEffect(string effectKey)
{
	if (mFactories.count(effectKey)) {
		return mFactories[effectKey]();
	}
	return nullptr;
}

void EffectRegistry::registerFactory(EffectFactory factory)
{
	if (mFactories.count(factory.first) == 0) {
		mFactories.insert(factory);
	}
	else {
		cerr << "error: attempt to register an effect factory \"";
		cerr << factory.first << "\" that is already registered." << endl;
	}
}


string EffectRegistry::makeUuid() {
	uuid_t uuid;
	char s[37];
	uuid_generate_random(uuid);
	uuid_unparse(uuid, s);
	return string(s);
}

void EffectRegistry::registerEffect(LanternEffect* effect)
{
	mEffects[effect->getId()] = effect;
}

void EffectRegistry::unregisterEffect(LanternEffect* effect)
{
	mEffects.erase(effect->getId());
}

void EffectRegistry::registerParameter(EffectParameter* param)
{
	mParameters[param->getId()] = param;
}

void EffectRegistry::unregisterParameter(EffectParameter* param)
{
	mParameters.erase(param->getId());
}

EffectParameter* EffectRegistry::findParameter(const std::string& id)
{
	auto it = mParameters.find(id);
	return it == mParameters.end() ? nullptr : it->second;
}

LanternEffect* EffectRegistry::findEffect(const std::string& id)
{
	auto it = mEffects.find(id);
	return it == mEffects.end() ? nullptr : it->second;
}
