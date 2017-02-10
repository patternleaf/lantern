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
#include "DripEffect.hpp"
#include "RingsEffect.hpp"

#include "LanternState.hpp"
#include "LanternServer.hpp"
#include "LanternMixer.hpp"

int main(int argc, char **argv)
{
	srand((unsigned int)clock());
	
	LanternMixer mixer;
	EffectRunner runner;
	LanternServer server;
	
	LanternState state(&server, &mixer);
	server.setState(&state);
	
	DripEffect dripEffect;
	LampEffect lampEffect;
	RippleEffect rippleEffect;
	RingsEffect ringsEffect("data/sky.png");
	
	runner.setEffect(&mixer);
	
	// Defaults, overridable with command line options
	runner.setMaxFrameRate(100);
	runner.setLayout("./layout.json");
	
	mixer.add(&dripEffect, 0.0f);
	mixer.add(&lampEffect, 0.0f);
	mixer.add(&rippleEffect, 1.0f);
	mixer.add(&ringsEffect, 1.0f);
	
	return runner.main(argc, argv);
}
