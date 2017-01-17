//
//  LampEffect.hpp
//  lantern
//
//  Created by Eric Miller on 1/16/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef LampEffect_hpp
#define LampEffect_hpp

#include <stdio.h>
#include "lib/effect.h"

class LampEffect : public Effect
{
public:
	LampEffect();
	
	virtual void beginFrame(const FrameInfo &f);
	virtual void shader(Vec3& rgb, const PixelInfo &p) const;
	
	float mCycle;
	float mTimeDelta;
};


#endif /* LampEffect_hpp */
