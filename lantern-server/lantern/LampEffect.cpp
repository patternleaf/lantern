//
//  LampEffect.cpp
//  lantern
//
//  Created by Eric Miller on 1/16/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "LampEffect.hpp"
#include "../lib/noise.h"
#include "CheckerCubeIds.h"
#include "../lib/color.h"

using namespace nlohmann;

LampEffect::LampEffect()
{
	float h = 0.09, s = 0.7, v = 0.6;
	hsv2rgb(mColor, h, s, v);
}

void LampEffect::beginFrame(const FrameInfo &f)
{
}

void LampEffect::shader(Vec3& rgb, const PixelInfo &p) const
{
	rgb[0] = mColor[0];
	rgb[1] = mColor[1];
	rgb[2] = mColor[2];
}

json LampEffect::getState()
{
	return {
		{ "id", mId },
		{ "name", "Lamp" },
		{ "parameters", getParameterDescription() }
	};
}

void LampEffect::setState(json state)
{
	mColor = JsonConversions::fromJson<Vec3>(state["color"]);
}

json LampEffect::getParameterDescription()
{
	return {
		{ "color", {
			{ "name", "Color" },
			{ "type", "color" }
		} },
	};
}
