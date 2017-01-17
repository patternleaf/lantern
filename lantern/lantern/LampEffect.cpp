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

LampEffect::LampEffect()
: mCycle(0)
{
	
}

void LampEffect::beginFrame(const FrameInfo &f)
{
	const float speed = 0.1;
	mTimeDelta += (f.timeDelta * speed);
//	std::cout << mTimeDelta << std::endl;
	mCycle = fmodf(mCycle + f.timeDelta * speed, 2 * M_PI);
}

void LampEffect::shader(Vec3& rgb, const PixelInfo &p) const
{
	Vec3 noisePt = p.point;
	
	noisePt[1] -= mTimeDelta;
//	noisePt[0] += mCycle;
	
	float h = 0.7, s = 0.3, v = 1.0;
	float noiseOffset = noise3(noisePt) * 0.1;
	
	if (!isCheckerCubeId(p.get("cubeId").GetInt())) {
		rgb[0] = 0.6;
		rgb[1] = fminf(1.0, 0.4 + noise3(noisePt));
		rgb[2] = 0.2;
//		h = fminf(1.0, 0.0 + noiseOffset);
//		v -= noiseOffset;
	}
	else {
		rgb[0] = 0.2;
		rgb[1] = rgb[2] = fminf(1.0, 0.4 + noise3(noisePt));
		rgb[2] = 0.6;
//		rgb[0] = rgb[1] = rgb[2] = 0;
//		h = fminf(1.0, 0.4 + noiseOffset);
	}
//	hsv2rgb(rgb, h, s, v);
	
}
