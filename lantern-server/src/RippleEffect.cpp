//
//  RippleEffect.cpp
//  lantern
//
//  Created by Eric Miller on 1/16/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include <sstream>
#include <limits>

#include "RippleEffect.hpp"
#include "../lib/color.h"
#include "../lib/noise.h"
#include "CheckerCubeIds.h"
#include "LanternState.hpp"
#include "EffectRegistry.hpp"

using namespace nlohmann;
using namespace std;

RippleEffect::RippleEffect()
: LanternEffect(), mMaxDistance(0), mSpeed(1), mCycle(0)
{
	for (int i = 0; i < 3; i++) {
		mRippleOrigins.push_back(Vec3(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 0));
		//std::cout << mRippleOrigins[i][0] << ", " << mRippleOrigins[i][1] << std::endl;
	}
}


void RippleEffect::beginFrame(const FrameInfo &f)
{
	LanternEffect::beginFrame(f);
	
	mCycle += f.timeDelta * mSpeed;
	if (mCycle > std::numeric_limits<float>::max()) {
		mCycle = 0;
	}
//	for (auto it = mRippleOrigins.begin(); it != mRippleOrigins.end(); it++) {
//		(*it)[0] += noise3((*it)) * 0.6;
//		(*it)[1] += noise2(Vec2((*it)[0], (*it)[1])) * 0.6;
//	}
}

void RippleEffect::shader(Vec3& rgb, const PixelInfo &p) const
{
	
	if (mMaxDistance > 0) {
		int wavelength = 1;
		for (auto it = mRippleOrigins.begin(); it != mRippleOrigins.end(); it++) {
			Vec3 contribution;
			float distance = len(*it - p.point);
			
			if (p.get("checker").GetBool()) {
				hsv2rgb(contribution, 0.3, 0.5, (sinf(mCycle + (distance * (32 * wavelength) / mMaxDistance)) * 0.6));
			}
			else {
				hsv2rgb(contribution, 0.6, 0.5, (sinf(mCycle + (distance * (32 * wavelength) / mMaxDistance)) * 0.6));
			}
						
			rgb[0] += contribution[0];
			rgb[1] += contribution[1];
			rgb[2] += contribution[2];
			
			wavelength++;
		}
		
	}
	
}


void RippleEffect::postProcess(const Vec3& rgb, const PixelInfo& p)
{
	if (len(p.point) > mMaxDistance) {
		mMaxDistance = len(p.point);;
	}
//	std::cout << rgb[0] << ", " << mMaxDistance << std::endl;
}

json RippleEffect::getState()
{
	return {
		{ "id", mId },
		{ "name", "Ripple" },
		{ "parameters", getParameters() }
	};
}

void RippleEffect::setState(json state)
{
	json parameters = state["parameters"];

	mSpeed = parameters[0]["real"];

	mRippleOrigins.clear();
	
	auto origins = parameters[1]["value"];
	
	for (auto origin: origins) {
		cout << "origin: " << origin << endl;
		mRippleOrigins.push_back(JsonConversions::fromJson<Vec3>(origin));
	}
}

json RippleEffect::getParameters()
{
	json origins = json::array();
	
	for (auto it = mRippleOrigins.begin(); it != mRippleOrigins.end(); it++) {
		origins.push_back(JsonConversions::toJson(*it));
	}
	
	return {
		{
			{ "name", "Speed" },
			{ "type", "real" },
			{ "range", { 0, 10 } },
			{ "value", mSpeed }
		},
		{
			{ "name", "Ripple Origins" },
			{ "type", "points" },
			{ "value", origins }
		}
	};
}
