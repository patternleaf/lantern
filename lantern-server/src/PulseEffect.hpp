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
#include <chrono>
#include "LanternEffect.hpp"

class PulseEffect : public LanternEffect {
public:
	PulseEffect();
	~PulseEffect();
	
	virtual void beginFrame(const FrameInfo &f);
	virtual void shader(Vec3& rgb, const PixelInfo &p) const;
	
	nlohmann::json getState();
	void setState(nlohmann::json state);
	nlohmann::json getParameters();
	
	EffectRegistry::EffectFactory getFactory();
	
private:

	typedef std::chrono::system_clock::duration time_duration;
	typedef std::chrono::time_point<std::chrono::system_clock, time_duration> time_stamp;

	typedef struct Ripple {
		Ripple();
		Vec3 origin;
		float band;
		float speed;
		float radius;	// -1 if not alive
		float intensity;
		float age;
		float cycle;
	} Ripple;
	
	void manageRipples(float timeDelta);
	
	Vec3 mLayoutMax;
	std::pair<float, float> mSpectrumRange;
	float mEnergyDiff;
	float mHighFreqContent;
	std::vector<std::pair<float, bool>> mBallistics;
	std::vector<Ripple> mRipples;
	std::pair<float, float> mVisibleBandRange;

};

#endif /* PulseEffect_hpp */
