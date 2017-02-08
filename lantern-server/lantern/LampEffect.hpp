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
#include "LanternEffect.hpp"

class LampEffect : public LanternEffect
{
public:
	LampEffect();
	
	virtual void beginFrame(const FrameInfo &f);
	virtual void shader(Vec3& rgb, const PixelInfo &p) const;
	
	virtual nlohmann::json getState();
	virtual void setState(nlohmann::json state);
	virtual nlohmann::json getParameterDescription();
	
	Vec3 mColor;
};


#endif /* LampEffect_hpp */
