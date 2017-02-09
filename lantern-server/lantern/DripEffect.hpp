//
//  DripEffect.hpp
//  lantern
//
//  Created by Eric Miller on 2/7/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef DripEffect_hpp
#define DripEffect_hpp

#include <stdio.h>
#include "LanternEffect.hpp"

class DripEffect: public LanternEffect {
public:
	DripEffect();
	
	virtual void beginFrame(const FrameInfo &f);
	virtual void shader(Vec3& rgb, const PixelInfo &p) const;
	
	virtual nlohmann::json getState();
	virtual void setState(nlohmann::json state);
	virtual nlohmann::json getParameters();
	
	float mCycle;
	Vec3 mBaseColor;

};


#endif /* DripEffect_hpp */
