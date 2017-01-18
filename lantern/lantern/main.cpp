//
//  main.cpp
//  lantern
//
//  Created by Eric Miller on 1/16/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include <math.h>
#include "../lib/color.h"
#include "../lib/effect.h"
#include "../lib/effect_runner.h"
#include "../lib/effect_mixer.h"
#include "../lib/noise.h"

#include "LampEffect.hpp"
#include "RippleEffect.hpp"

class MyEffect : public Effect
{
public:
	MyEffect()
	: cycle (0) {}
	
	float cycle;
	
	virtual void beginFrame(const FrameInfo &f)
	{
		const float speed = 1.0;
		cycle = fmodf(cycle + f.timeDelta * speed, 2 * M_PI);
	}
	
	virtual void shader(Vec3& rgb, const PixelInfo &p) const
	{
		float distance = len(p.point);
//		float wave = sinf(3.0 * distance - cycle) + noise3(p.point);
		float wave = sinf(3 * distance + cycle);
		hsv2rgb(rgb, 0.2, 0.3, fminf(0.6, abs(wave)));
	}
};

int main(int argc, char **argv)
{
	srand(clock());
	EffectMixer mixer;
	EffectRunner r;
	
	MyEffect defaultEffect;
	LampEffect lampEffect;
	RippleEffect rippleEffect;
	
	r.setEffect(&mixer);
	
	// Defaults, overridable with command line options
	r.setMaxFrameRate(100);
	r.setLayout("./layout.json");
	
	mixer.add(&defaultEffect, 0.0f);
	mixer.add(&lampEffect, 0.0f);
	mixer.add(&rippleEffect, 0.5f);
	
	return r.main(argc, argv);
}
