//
//  LanternEffect.cpp
//  lantern
//
//  Created by Eric Miller on 1/24/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "LanternEffect.hpp"
#include <uuid/uuid.h>


LanternEffect::LanternEffect()
{
	uuid_t uuid;
	char s[37];
	uuid_generate_random(uuid);
	uuid_unparse(uuid, s);
	mId = std::string(s);
}

std::string LanternEffect::getId()
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
