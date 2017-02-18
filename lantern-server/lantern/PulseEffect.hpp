//
//  PulseEffect.hpp
//  lantern
//
//  Created by Eric Miller on 2/12/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef PulseEffect_hpp
#define PulseEffect_hpp

#include <iostream>
#include <fstream>
#include "LanternEffect.hpp"
//#include "../lib/particle.h"

//class PulseEffect : public ParticleEffect {
class PulseEffect : public LanternEffect {
public:
	PulseEffect();
	~PulseEffect();
	
	virtual void beginFrame(const FrameInfo &f);
	virtual void shader(Vec3& rgb, const PixelInfo &p) const;
	
	nlohmann::json getState();
	void setState(nlohmann::json state);
	nlohmann::json getParameters();
	
private:

	Vec3 mLayoutMax;
	std::pair<float, float> mSpectrumRange;
	std::vector<float> mMagSpectrum;
	std::vector<float> mBallistics;
};

#endif /* PulseEffect_hpp */
