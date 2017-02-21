//
//  LanternMixer.cpp
//  lantern
//
//  Created by Eric Miller on 2/3/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "LanternMixer.hpp"
#include "LanternEffect.hpp"

using namespace std;

float LanternMixer::getFader(int channel)
{
	return channels[channel].fader;
}

Effect* LanternMixer::getEffect(int channel)
{
	return channels[channel].effect;
}

int LanternMixer::add(LanternEffect *effect, float fader)
{
	cout << "mixer adding effect " << effect->getId() << endl;
	return EffectMixer::add(effect, fader);
}

