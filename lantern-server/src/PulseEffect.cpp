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

using namespace nlohmann;
using namespace std;



PulseEffect::PulseEffect()
	: LanternEffect()
{
	
}

PulseEffect::~PulseEffect()
{

}

void PulseEffect::beginFrame(const FrameInfo &f)
{
	LanternEffect::beginFrame(f);
	
	mLayoutMax = f.modelMax;

	const vector<float>& mag = AudioService::shared()->getMelFrequencySpectrum();
//	const vector<float>& mag = AudioService::shared()->getMagnitudeSpectrum();
	
	if (mMagSpectrum.size() != mag.size()) {
		mMagSpectrum.resize(mag.size());
		mBallistics.resize(mag.size(), 0);
	}
	
//	copy(mag.begin(), mag.end(), mMagSpectrum.begin());
	
	mMagSpectrum.clear();
	mSpectrumRange.first = numeric_limits<float>::max();
	mSpectrumRange.second = -numeric_limits<float>::max();
	
	for (float intensity : mag) {
		if (intensity < mSpectrumRange.first) {
			mSpectrumRange.first = intensity;
		}
		if (intensity > mSpectrumRange.second) {
			mSpectrumRange.second = intensity;
		}
		mMagSpectrum.push_back(intensity);
	}
	
	for (int i = 0; i < mag.size(); i++) {
		float intensity = mag[i];
		bool wasReset = false;
		if (mSpectrumRange.second - mSpectrumRange.first != 0) {
			intensity = (intensity - mSpectrumRange.first) / (mSpectrumRange.second - mSpectrumRange.first);
			if (intensity > mBallistics[i]) {
				mBallistics[i] = intensity;
				wasReset = true;
			}
		}
		
		if (!wasReset) {
			mBallistics[i] -= 0.0005;
		}
	}

//	cout << "wtf ";
//	for (float blah = 0; blah < 1.0; blah += 0.01) {
//		cout << "  " << blah << ", " << ((M_E + log(blah)) / M_E) << endl;
//	}
//	cout << endl;

//	cout << "ballistics: ";
//	for (int i = 0; i < mBallistics.size(); i++) { cout << mBallistics[i] << " "; }
//	cout << endl;

	
//	cout << "mag spectrum has " << mag.size() << " elements, min: " << mSpectrumRange.first << ", second: " << mSpectrumRange.second << endl;
//	for (int i = 0; i < mag.size(); i++) {
//		if (mag[i] > 0) {
//			cout << "    mag spectrum value " << i << ": " << mag[i] << endl;
//		}
//	}
}

void PulseEffect::shader(Vec3& rgb, const PixelInfo &p) const
{
//	rgb[0] = rgb[1] = rgb[2] = 0;
	float xPos = p.point[0] / mLayoutMax[0];
	float yPos = 1 - (p.point[1] / mLayoutMax[1]);
	
	xPos = xPos == 0 ? 0 : ((M_E + log(xPos)) / M_E);
	yPos = yPos == 0 ? 0 : ((M_E + log(yPos)) / M_E);
	
	int magIndex = floor(xPos * mBallistics.size());
	float intensity = mBallistics[magIndex];
//	intensity = (2 + log(intensity)) / 2;
	hsv2rgb(rgb, magIndex / (float)mBallistics.size() / 2.0, 1.0, (intensity * 50) - yPos);
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

