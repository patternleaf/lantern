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

class LanternMixer: public EffectMixer {
public:
	float getFader(int channel);
	Effect* getEffect(int channel);
};

#endif /* LanternMixer_hpp */
