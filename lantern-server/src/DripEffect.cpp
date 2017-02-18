//
//  DripEffect.cpp
//  lantern
//
//  Created by Eric Miller on 2/7/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "DripEffect.hpp"
#include "../lib/color.h"

using namespace nlohmann;
using namespace std;

DripEffect::DripEffect()
: mSpeed(1), mCycle(0), mColor(0.3, 0.5, 0.9), mOrigin(0, 0, 0)
{
	
}


void DripEffect::beginFrame(const FrameInfo &f)
{
	LanternEffect::beginFrame(f);
	
	mCycle = fmod(mCycle + f.timeDelta * -mSpeed, 2 * M_PI);
}

void DripEffect::shader(Vec3& rgb, const PixelInfo &p) const
{
	float distance = len(p.point - mOrigin);
	float wave = sin(3 * distance + mCycle);
	
	rgb[0] = mColor[0] * wave;
	rgb[1] = mColor[1] * wave;
	rgb[2] = mColor[2] * wave;
}


json DripEffect::getState()
{
	return {
		{ "id", mId },
		{ "name", "Drip" },
		{ "parameters", getParameters() }
	};
}

void DripEffect::setState(json state)
{
	json parameters = state["parameters"];
	
	auto origins = parameters[0]["value"];
	mOrigin = JsonConversions::fromJson<Vec3>(origins[0]);
	mColor = JsonConversions::fromJson<Vec3>(parameters[1]["value"]);
	mSpeed = parameters[2]["real"];	
}

json DripEffect::getParameters()
{
	json origins = json::array();
	
	origins.push_back(JsonConversions::toJson(mOrigin));
	
	return {
		{
			{ "name", "Origin" },
			{ "type", "points" },
			{ "value", origins }
		},
		{
			{ "name", "Color" },
			{ "type", "color" },
			{ "value", JsonConversions::toJson(mColor) }
		},
		{
			{ "name", "Speed" },
			{ "type", "real" },
			{ "range", { 0, 80 } },
			{ "value", mSpeed }
		}
	};
}
