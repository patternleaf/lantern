//
//  EffectParameter.cpp
//  lantern
//
//  Created by Eric Miller on 2/9/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "EffectParameter.hpp"

using namespace nlohmann;

EffectParameter::EffectParameter(json json)
: mState(json)
{
	mId = json["id"];
}

std::string EffectParameter::getId()
{
	return mId;
}
void EffectParameter::setState(json json)
{
	mState = json;
}

json EffectParameter::getState()
{
	return mState;
}
