//
//  LanternEffect.cpp
//  lantern
//
//  Created by Eric Miller on 1/24/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "LanternEffect.hpp"
#include "EffectRegistry.hpp"
#include <uuid/uuid.h>

using namespace std;
using namespace nlohmann;

LanternEffect::LanternEffect()
{
	mId = EffectRegistry::makeUuid();
	EffectRegistry::shared()->registerEffect(this);
}

LanternEffect::~LanternEffect()
{
	EffectRegistry::shared()->unregisterEffect(this);
}

string LanternEffect::getId()
{
	return mId;
}

void LanternEffect::cacheStateUpdate(json state)
{
	mLatestUpdate = state;
}

void LanternEffect::beginFrame(const FrameInfo &f)
{
	if (mLatestUpdate.is_object()) {
		this->setState(mLatestUpdate);
		mLatestUpdate = "null"_json;
	}
}

void LanternEffect::subscribe(LanternEffect::EventHandler handler)
{
	mHandlers.push_back(handler);
}

void LanternEffect::broadcast(nlohmann::json event)
{
	for (auto handler: mHandlers) {
		handler(event);
	}
}
