//
//  RippleEffect.cpp
//  lantern
//
//  Created by Eric Miller on 1/16/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "RippleEffect.hpp"
#include "../lib/color.h"
#include "../lib/noise.h"
#include "CheckerCubeIds.h"

RippleEffect::RippleEffect()
: mMaxDistance(0)
{
	for (int i = 0; i < 3; i++) {
		mRippleOrigins.push_back(Vec3(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 0));
		std::cout << mRippleOrigins[i][0] << ", " << mRippleOrigins[i][1] << std::endl;
	}
	
}


void RippleEffect::beginFrame(const FrameInfo &f)
{
	mCycle += f.timeDelta * 1;
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
			
			if (isCheckerCubeId(p.get("cubeId").GetInt())) {
				hsv2rgb(contribution, 0.3, 0.5, (sinf(mCycle + (distance * (32 * wavelength) / mMaxDistance)) * 0.6));
			}
			else {
				hsv2rgb(contribution, 0.6, 0.5, (sinf(mCycle + (distance * (32 * wavelength) / mMaxDistance)) * 0.6));
			}
			
//			hsv2rgb(contribution, 0.6, 0.5, (sinf(mCycle + (distance * (32 * wavelength) / mMaxDistance)) * 0.6));
			
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
