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
#include "LanternEffect.hpp"
#include "JsonConversions.hpp"

class RippleEffect : public LanternEffect
{
public:
	RippleEffect();
	
	virtual void beginFrame(const FrameInfo &f);
	virtual void shader(Vec3& rgb, const PixelInfo &p) const;
	virtual void postProcess(const Vec3& rgb, const PixelInfo& p);

	virtual nlohmann::json getState();
	virtual void setState(nlohmann::json state);
	virtual nlohmann::json getParameterDescription();
	
	float mMaxDistance;
	float mCycle;
	float mSpeed;
	std::vector<Vec3> mRippleOrigins;
//	Vec3 mRippleOrigin;
};


#endif /* RippleEffect_hpp */
