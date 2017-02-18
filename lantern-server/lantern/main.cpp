//
//  main.cpp
//  lantern
//
//  Created by Eric Miller on 1/16/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "RaopService.hpp"		// some boost-y weirdness is lessened if this is included first. :(
#include "AudioService.hpp"

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
#include "PulseEffect.hpp"

#include "LanternState.hpp"
#include "LanternServer.hpp"
#include "LanternMixer.hpp"



int main(int argc, char **argv)
{
	srand((unsigned int)clock());
	
	LanternMixer mixer;
	EffectRunner runner;
	LanternServer server;
	
	RaopService::shared()->expose("lantern");
	AudioService::shared();
	
	LanternState state(&server, &mixer);
	server.setState(&state);
	
	DripEffect dripEffect;
	LampEffect lampEffect;
	RippleEffect rippleEffect;
	RingsEffect ringsEffect("data/sky.png");
	PulseEffect pulseEffect;
	
	runner.setEffect(&mixer);
	
	// Defaults, overridable with command line options
	runner.setMaxFrameRate(100);
	runner.setLayout("./layout.json");

/*
	mixer.add(&dripEffect, 0.1f);
	mixer.add(&lampEffect, 0.5f);
	mixer.add(&rippleEffect, 0.0f);
	mixer.add(&ringsEffect, 1.0f);
*/
	mixer.add(&pulseEffect, 1.0f);
	
	int result = runner.main(argc, argv);
	
	RaopService::shared()->hide();
	
	return result;
}

