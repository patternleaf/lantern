//
//  AudioService.hpp
//  lantern
//
//  Created by Eric Miller on 2/12/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef AudioService_hpp
#define AudioService_hpp

#include <boost/circular_buffer.hpp>

#include <iostream>
#include <fstream>
#include <chrono>

#include "AudioHandler.hpp"

class AudioService : public AudioHandler {
public:
	static AudioService* shared();
	
	typedef std::chrono::system_clock::duration time_duration;
	typedef std::chrono::time_point<std::chrono::system_clock, time_duration> time_stamp;
	
	const std::vector<float>& getMagnitudeSpectrum();
	const std::vector<float>& getMelFrequencySpectrum();
	
	// measure of headroom, https://en.wikipedia.org/wiki/Crest_factor
	float getSpectralCrest();
	
	float getSpectralCentroid();
	
	float getEnergyDifference();
	
//	time_duration getBeatTime();
		
	virtual void handleAudio(RaopService::AudioBuffer buffer, float volume);
	virtual void handleAudioStreamEnded();
	
private:
	AudioService();
	~AudioService();
	static AudioService* sService;

	std::vector<float> mSummedFrame;

	boost::circular_buffer<time_duration> mOnsetPeriods;
	boost::circular_buffer<float> mOnsetSamples;

};

#include <stdio.h>

#endif /* AudioService_hpp */
