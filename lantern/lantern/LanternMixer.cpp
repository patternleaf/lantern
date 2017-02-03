//
//  LanternMixer.cpp
//  lantern
//
//  Created by Eric Miller on 2/3/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "LanternMixer.hpp"


float LanternMixer::getFader(int channel)
{
	return channels[channel].fader;
}

Effect* LanternMixer::getEffect(int channel)
{
	return channels[channel].effect;
}
