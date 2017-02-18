//
//  AudioService.cpp
//  lantern
//
//  TODO: currently just hooks into the raop service with assumed
//  samplerates, etc. Make it accept other audio sources too.
//
//  Created by Eric Miller on 2/12/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "AudioService.hpp"
#include "Gist.h"

using namespace std;

// TODO: dynamic based on session? meh.
const static int kSampleRate = 44100;
const static int kSampleSize = 2;		// in bytes natch
const static int kNChannels = 2;
const static int kFrameSize = 512;

static Gist<float> sGist(kFrameSize, kSampleRate);

AudioService* AudioService::sService = nullptr;

AudioService* AudioService::shared()
{
	if (sService == nullptr) {
		sService = new AudioService();
	}
	return sService;
}


// TODO:
AudioService::AudioService()
{

	mSummedFrame.reserve(kFrameSize);

	RaopService::shared()->registerAudioHandler(this);
//	mTestOut.open("test.pcm");
}

AudioService::~AudioService()
{
	RaopService::shared()->unregisterAudioHandler(this);
}

const vector<float>& AudioService::getMagnitudeSpectrum()
{
	return sGist.getMagnitudeSpectrum();
}

const vector<float>& AudioService::getMelFrequencySpectrum()
{
	return sGist.getMelFrequencySpectrum();
}

void AudioService::handleAudio(RaopService::AudioBuffer buffer, float volume)
{
//	auto start = buffer.begin()
//	int window = 1024;
//	int traversed = 0;
//	for (auto it = start; it < start + window && it < buffer.end(); it++, traversed++) {
//		cout << "     " << *it << endl;
//	}
//	for (auto sample : buffer) {
//		mTestOut << sample;
//	}

	mSummedFrame.clear();
	
	int stride = kSampleSize * kNChannels;
	uint16_t fullCodeSample = -1;
	
//	cout << "constructing frame" << endl;
	
	for (int i = 0; i < buffer.size() && mSummedFrame.size() < kFrameSize; i += stride) {
		uint16_t lSample = (buffer[i] | buffer[i + 1] << 8);
		uint16_t rSample = (buffer[i + 2] | buffer[i + 3] << 8);
		
		mSummedFrame.push_back((lSample / (float)fullCodeSample / 2.0) + (rSample / (float)fullCodeSample / 2.0));
//		cout << "  buffer (4 bytes)" << endl;
//		cout << hex << showbase;// << internal;
//		cout << "    " << buffer[i] << ", " << buffer[i + 1] << ", " << buffer[i + 2] << ", " << buffer[i + 3] << endl;
//		cout << dec << noshowbase;
//		cout << "  sample" << endl;
//		cout << "    L: " << lSample << " --- " << (lSample / (float)fullCodeSample) << endl;
//		cout << "    R: " << rSample << " --- " << (rSample / (float)fullCodeSample) << endl;
//		cout << "  summed: " << mSummedFrame.back() << endl;
	}
	
	sGist.processAudioFrame(mSummedFrame);
	
}

void AudioService::handleAudioStreamEnded()
{
	mSummedFrame.resize(kFrameSize, 0);
	fill(mSummedFrame.begin(), mSummedFrame.end(), 0);
	cout << "zeroing gist buffer (size " << mSummedFrame.size() << ")" << endl;
//	for (auto it : mSummedFrame) { cout << " " << it; }
	sGist.processAudioFrame(mSummedFrame);
}
