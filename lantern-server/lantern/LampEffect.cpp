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
//	const float speed = 1;
	mTimeDelta += (f.timeDelta * speed);
//	std::cout << mTimeDelta << std::endl;
	mCycle = fmodf(mCycle + f.timeDelta * speed, 2 * M_PI);
}

void LampEffect::shader(Vec3& rgb, const PixelInfo &p) const
{
	Vec3 noisePt = p.point;
	
	
	noisePt[1] -= mTimeDelta;
//	noisePt[0] += mCycle;
	
	float h = 0.09, s = 0.7, v = 0.6;
	Vec3 flatWarm;
	Vec3 lava;
	
	if (!isCheckerCubeId(p.get("cubeId").GetInt())) {
//		lava[0] = 0.6;
//		lava[1] = fminf(1.0, 0.0 + noise3(noisePt));
//		lava[2] = 0.2;
		lava[0] = lava[1] = lava[2] = 0;
	}
	else {
		lava[0] = 0.2;
		lava[1] = 0.4;//fminf(1.0, 0.4 + noise3(noisePt));
		lava[2] = fminf(1.0, 0.4 + noise3(noisePt));
//		v = 0.4;
		lava[0] = lava[1] = lava[2] = 0;
	}
	
	hsv2rgb(flatWarm, h, s, v);
	
	rgb[0] = fminf(1.0, flatWarm[0] + lava[0]);
	rgb[1] = fminf(1.0, flatWarm[1] + lava[1]);
	rgb[2] = fminf(1.0, flatWarm[2] + lava[2]);
}
