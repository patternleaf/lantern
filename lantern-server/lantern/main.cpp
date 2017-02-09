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


#include "LanternState.hpp"
#include "LampEffect.hpp"
#include "RippleEffect.hpp"
#include "DripEffect.hpp"
#include "LanternServer.hpp"
#include "LanternMixer.hpp"

int main(int argc, char **argv)
{
	srand((unsigned int)clock());
	
	LanternMixer mixer;
	EffectRunner runner;
	LanternServer server;
	
	LanternState state(&server, &mixer);
	
	DripEffect dripEffect;
	LampEffect lampEffect;
	RippleEffect rippleEffect;
	
	runner.setEffect(&mixer);
	
	// Defaults, overridable with command line options
	runner.setMaxFrameRate(100);
	runner.setLayout("./layout.json");
	
	mixer.add(&dripEffect, 1.0f);
	mixer.add(&lampEffect, 0.0f);
	mixer.add(&rippleEffect, 0.0f);
	
	return runner.main(argc, argv);
}
