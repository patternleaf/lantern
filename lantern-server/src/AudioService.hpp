//
//  AudioService.hpp
//  lantern
//
//  Created by Eric Miller on 2/12/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef AudioService_hpp
#define AudioService_hpp

#include <iostream>
#include <fstream>

#include "AudioHandler.hpp"

class AudioService : public AudioHandler {
public:
	static AudioService* shared();
	
	const std::vector<float>& getMagnitudeSpectrum();
	const std::vector<float>& getMelFrequencySpectrum();
	
	virtual void handleAudio(RaopService::AudioBuffer buffer, float volume);
	virtual void handleAudioStreamEnded();
	
private:
	AudioService();
	~AudioService();
	static AudioService* sService;
	
	std::vector<float> mSummedFrame;

};

#include <stdio.h>

#endif /* AudioService_hpp */
