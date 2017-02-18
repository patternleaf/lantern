//
//  LanternMixer.hpp
//  lantern
//
//  Created by Eric Miller on 2/3/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef LanternMixer_hpp
#define LanternMixer_hpp

#include <stdio.h>
#include "lib/effect_mixer.h"

class LanternEffect;

class LanternMixer: public EffectMixer {
public:
	float getFader(int channel);
	Effect* getEffect(int channel);
	int add(LanternEffect *effect, float fader = 1.0);
};

#endif /* LanternMixer_hpp */
