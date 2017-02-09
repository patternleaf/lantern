//
//  LanternEffect.cpp
//  lantern
//
//  Created by Eric Miller on 1/24/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "LanternEffect.hpp"
#include <uuid/uuid.h>

using namespace std;

static string makeUuid() {
	uuid_t uuid;
	char s[37];
	uuid_generate_random(uuid);
	uuid_unparse(uuid, s);
	return string(s);
}

LanternEffect::LanternEffect()
{
	mId = makeUuid();
}

string LanternEffect::getId()
{
	return mId;
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

void LanternEffect::createParameterIds(int count)
{
	for (int i = 0; i < count; i++) {
		mParameterIds.push_back(makeUuid());
	}
}
