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
	mVisibleBandRange.first = 0;
	mVisibleBandRange.second = 1;
	mHighFreqContent = 0;
	mEnergyDiff = 0;
	EffectRegistry::shared()->registerFactory(getFactory());
}

PulseEffect::~PulseEffect()
{

}

PulseEffect::Ripple::Ripple()
: intensity(0), speed(0), radius(0), origin(0, 0, 0), band(0), cycle(-1), age(0)
{
}

EffectRegistry::EffectFactory PulseEffect::getFactory()
{
	return EffectRegistry::EffectFactory("pulse", []() { return new PulseEffect(); });
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
	
	float energyDiff = AudioService::shared()->getEnergyDifference();
	float highFreqContent = AudioService::shared()->getEnergyDifference();
	
	if (mEnergyDiff > 255 || mEnergyDiff < 0) {
		cout << "energy diff outside of expected range: " << mEnergyDiff << endl;
	}
	if (mHighFreqContent > 255 || mHighFreqContent < 0) {
		cout << "energy diff outside of expected range: " << mHighFreqContent << endl;
	}
	
	if (energyDiff > mEnergyDiff * 1.2) {
		mEnergyDiff = energyDiff / 255.0;
	}
	else if (mEnergyDiff > 0) {
		mEnergyDiff -= 0.001;
	}
	
	if (highFreqContent > mHighFreqContent * 1.2) {
		mHighFreqContent = highFreqContent / 255.0;
	}
	else if (mHighFreqContent > 0) {
		mHighFreqContent -= 0.001;
	}
	
	
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
			mRipples[i].speed = (1 + mRipples[i].band);
			mRipples[i].intensity = mBallistics[i].first;
			mBallistics[i].second = false;
		}
		else {
			mRipples[i].intensity = mBallistics[i].first;
			mRipples[i].origin[0] = mLayoutMax[0] / 2;
			mRipples[i].origin[1] = mLayoutMax[1] / 2;
//			mRipples[i].origin[0] = (noise2(mRipples[i].age / (30 + i), 40.2 + i) * 2 * mLayoutMax[0]);
//			mRipples[i].origin[1] = (noise2(mRipples[i].age / (30 + i), 30.4 + i) * 2 * mLayoutMax[1]);
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
/*
	unsigned firstVisible = floor(mVisibleBandRange.first * mRipples.size());
	unsigned lastVisible = ceil(mVisibleBandRange.second * mRipples.size());
	for (unsigned i = 0; i < mRipples.size(); i++) {
		if (i < firstVisible || i > lastVisible) {
			continue;
		}
		const Ripple& ripple = mRipples[i];
		float distance = len(ripple.origin - p.point);
//		float innerFactor = (distance / (ripple.band + sinf(ripple.age)));
//		float value = sinf(((1 + ripple.band) * 32) * ripple.age) * (1 - ((distance * distance) / mLayoutMax[0]));
		
		float value = sinf((20 * (0.1 + ripple.band)) * (-ripple.cycle + distance)) * (ripple.intensity / distance);
		
//		value *= (1 - (distance / mLayoutMax[0]));
		
		Vec3 contribution;
		
		hsv2rgb(contribution, ripple.band, 0.5, value);
		
		rgb[0] += contribution[0];
		rgb[1] += contribution[1];
		rgb[2] += contribution[2];
//		break;
	}
*/
	
	rgb[0] = mEnergyDiff;
	rgb[1] = mHighFreqContent;
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
	json parameters = state["parameters"];
	mVisibleBandRange.first = parameters[0]["value"][0];
	mVisibleBandRange.second = parameters[0]["value"][1];
}

json PulseEffect::getParameters()
{
	return {
		{
			{ "name", "Visible Band Range" },
			{ "type", "range" },
			{ "valueType", "real" },
			{ "range", { 0, 1 } },
			{ "value", { mVisibleBandRange.first, mVisibleBandRange.second } }
		}
	};
}

