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

DripEffect::DripEffect()
: mCycle(0), mBaseColor(0.3, 0.5, 0.9)
{
	
}


void DripEffect::beginFrame(const FrameInfo &f)
{
	const float speed = 1.0;
	mCycle = fmod(mCycle + f.timeDelta * speed, 2 * M_PI);
}

void DripEffect::shader(Vec3& rgb, const PixelInfo &p) const
{
	float distance = len(p.point);
	float wave = sin(3 * distance + mCycle);
	hsv2rgb(rgb, 0.2, 0.3, wave);
}


json DripEffect::getState()
{
	return {
		{ "id", mId },
		{ "name", "Drip" },
		{ "parameters", getParameterDescription() }
	};
}

void DripEffect::setState(json state)
{
	
}

json DripEffect::getParameterDescription()
{
	return {{}};
}
