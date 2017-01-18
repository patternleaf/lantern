//
//  RippleEffect.hpp
//  lantern
//
//  Created by Eric Miller on 1/16/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef RippleEffect_hpp
#define RippleEffect_hpp

#include <stdio.h>
#include "../lib/effect.h"

class RippleEffect : public Effect
{
public:
	RippleEffect();
	
	virtual void beginFrame(const FrameInfo &f);
	virtual void shader(Vec3& rgb, const PixelInfo &p) const;
	virtual void postProcess(const Vec3& rgb, const PixelInfo& p);
	
	float mMaxDistance;
	float mCycle;
	std::vector<Vec3> mRippleOrigins;
//	Vec3 mRippleOrigin;
};


#endif /* RippleEffect_hpp */
