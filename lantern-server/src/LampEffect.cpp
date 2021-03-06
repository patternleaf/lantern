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
	
	EffectRegistry::shared()->registerFactory(getFactory());
}

void LampEffect::beginFrame(const FrameInfo &f)
{
	LanternEffect::beginFrame(f);
}

void LampEffect::shader(Vec3& rgb, const PixelInfo &p) const
{
	rgb[0] = mColor[0];
	rgb[1] = mColor[1];
	rgb[2] = mColor[2];
}

EffectRegistry::EffectFactory LampEffect::getFactory()
{
	return EffectRegistry::EffectFactory("lamp", []() { return new LampEffect(); });
}


json LampEffect::getState()
{
	return {
		{ "id", mId },
		{ "name", "Lamp" },
		{ "parameters", getParameters() }
	};
}

void LampEffect::setState(json state)
{
	json parameters = state["parameters"];
	
	mColor = JsonConversions::fromJson<Vec3>(parameters[0]["value"]);
}

json LampEffect::getParameters()
{
	return {
		{
			{ "name", "Color" },
			{ "type", "color" },
			{ "value", JsonConversions::toJson(mColor) }
		},
	};
}
