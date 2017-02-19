//
//  PulseEffect.cpp
//  lantern
//
//  Created by Eric Miller on 2/12/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//


#include "PulseEffect.hpp"
#include "AudioService.hpp"
#include "../lib/color.h"
#include "../lib/noise.h"

using namespace nlohmann;
using namespace std;
using namespace std::chrono;

PulseEffect::PulseEffect()
	: LanternEffect()
{

}

PulseEffect::~PulseEffect()
{

}

PulseEffect::Ripple::Ripple()
: intensity(0), speed(0), radius(0), origin(0, 0, 0), band(0), cycle(-1), age(0)
{
}

void PulseEffect::beginFrame(const FrameInfo &f)
{
	LanternEffect::beginFrame(f);
	
	mLayoutMax = f.modelMax;

	const vector<float>& mag = AudioService::shared()->getMelFrequencySpectrum();
//	const vector<float>& mag = AudioService::shared()->getMagnitudeSpectrum();
	
	if (mBallistics.size() != mag.size()) {
		mBallistics.resize(mag.size(), make_pair(0, false));
		mRipples.resize(mag.size(), Ripple());
	}
	
	mSpectrumRange.first = numeric_limits<float>::max();
	mSpectrumRange.second = -numeric_limits<float>::max();
	
	for (float intensity : mag) {
		if (intensity < mSpectrumRange.first) {
			mSpectrumRange.first = intensity;
		}
		if (intensity > mSpectrumRange.second) {
			mSpectrumRange.second = intensity;
		}
	}
	
	for (int i = 0; i < mag.size(); i++) {
		float intensity = mag[i];
		float band = i / (float)mag.size();
		bool wasReset = false;
		
		// avoid divide by zero
		if (mSpectrumRange.second - mSpectrumRange.first != 0) {
		
			intensity = (intensity - mSpectrumRange.first) / (mSpectrumRange.second - mSpectrumRange.first);

			if (intensity > (mBallistics[i].first * (2 * (1 - band)))) {
				mBallistics[i].first = intensity;
				mBallistics[i].second = true;
				wasReset = true;
			}
		}
		
		if ((!wasReset || intensity == 0) && mBallistics[i].first > 0) {
//			mBallistics[i].first -= 0.0005;
			mBallistics[i].first -= 0.01;
		}
	}
	
	manageRipples(f.timeDelta);

}

void PulseEffect::manageRipples(float timeDelta)
{
	for (int i = 0; i < mRipples.size(); i++) {
	
		mRipples[i].cycle = fmodf(mRipples[i].cycle + (timeDelta * mRipples[i].speed), 2 * M_PI);
		mRipples[i].age += timeDelta;
		
		if (mBallistics[i].second || mRipples[i].intensity == -1) {	// was reset or new
			mRipples[i].band = (i / (float)mRipples.size());
			mRipples[i].speed = 0.01 + mRipples[i].band;
			mRipples[i].intensity = mBallistics[i].first;
			mBallistics[i].second = false;
		}
		else {
			mRipples[i].intensity = mBallistics[i].first;
			mRipples[i].origin[0] = (noise2(mRipples[i].age / (30 + i), 40.2 + i) * 2 * mLayoutMax[0]);
			mRipples[i].origin[1] = (noise2(mRipples[i].age / (30 + i), 30.4 + i) * 2 * mLayoutMax[1]);
//			cout << "(" << i << ")" <<  mRipples[i].age.count() / (double)system_clock::period::den << endl;
		}
		
//		if (i == 1) {
//			cout << "age: " << mRipples[i].age << ", noise: " << noise2(mRipples[i].age, 50.9) << endl;
//			cout << "(" << mRipples[i].origin[0] << ", " << mRipples[i].origin[1] << ")" << endl;
//		}
	}
}

void PulseEffect::shader(Vec3& rgb, const PixelInfo &p) const
{

	for (unsigned i = 0; i < mRipples.size(); i++) {
//		if (i != 4) {
//			continue;
//		}
		const Ripple& ripple = mRipples[i];
		float distance = len(ripple.origin - p.point);
//		float innerFactor = (distance / (ripple.band + sinf(ripple.age)));
//		float value = sinf(((1 + ripple.band) * 32) * ripple.age) * (1 - ((distance * distance) / mLayoutMax[0]));
		
		float value = sinf((20 * (0.1 + ripple.band)) * (-ripple.cycle + distance)) * ripple.intensity;
		
//		value *= (1 - (distance / mLayoutMax[0]));
		
		Vec3 contribution;
		
		hsv2rgb(contribution, ripple.band, 0.5, value);
		
		rgb[0] += contribution[0];
		rgb[1] += contribution[1];
		rgb[2] += contribution[2];
//		break;
	}

/*
	float xPos = p.point[0] / mLayoutMax[0];
	float yPos = 1 - (p.point[1] / mLayoutMax[1]);
	
//	xPos = xPos == 0 ? 0 : ((M_E + log(xPos)) / M_E);
//	yPos = yPos == 0 ? 0 : ((M_E + log(yPos)) / M_E);
	
	int magIndex = floor(xPos * mBallistics.size());
	float intensity = mBallistics[magIndex];
//	intensity = (2 + log(intensity)) / 2;
	hsv2rgb(rgb, magIndex / (float)mBallistics.size() / 2.0, 1.0, (intensity * 50) - yPos);
*/
	
}

json PulseEffect::getState()
{
	return {
		{ "id", mId },
		{ "name", "PulseEffect" },
		{ "parameters", getParameters() }
	};
}

void PulseEffect::setState(json state)
{
	
}

json PulseEffect::getParameters()
{
	return {{}};
}

