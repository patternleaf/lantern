//
//  main.cpp
//  lantern
//
//  Created by Eric Miller on 1/16/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include <math.h>
#include "lib/color.h"
#include "lib/effect.h"
#include "lib/effect_runner.h"
#include "lib/effect_mixer.h"
#include "lib/noise.h"

#include "LampEffect.hpp"

class MyEffect : public Effect
{
public:
	MyEffect()
	: cycle (0) {}
	
	float cycle;
	
	virtual void beginFrame(const FrameInfo &f)
	{
		const float speed = 2.0;
		cycle = fmodf(cycle + f.timeDelta * speed, 2 * M_PI);
	}
	
	virtual void shader(Vec3& rgb, const PixelInfo &p) const
	{
		float distance = len(p.point);
		float wave = sinf(3.0 * distance - cycle) + noise3(p.point);
		hsv2rgb(rgb, 0.2, 0.3, wave);
	}
};

int main(int argc, char **argv)
{
	EffectMixer mixer;
	EffectRunner r;
	
	MyEffect defaultEffect;
	LampEffect lampEffect;
	
	r.setEffect(&mixer);
	
	// Defaults, overridable with command line options
	r.setMaxFrameRate(100);
	r.setLayout("./layout.json");
	
	mixer.add(&defaultEffect, 0.0f);
	mixer.add(&lampEffect, 1.0f);
	
	return r.main(argc, argv);
}
