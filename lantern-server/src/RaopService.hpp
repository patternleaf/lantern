//
//  RaopService.hpp
//  lantern
//
//  Created by Eric Miller on 2/12/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef RaopService_hpp
#define RaopService_hpp

#include <boost/circular_buffer.hpp>

#include <stdio.h>
#include <string>
#include <functional>
#include <vector>
#include <set>

#include "shairplay/raop.h"
#include "shairplay/dnssd.h"


class AudioHandler;
struct AudioSession;

void* raop_service_audio_init(void *cls, int bits, int channels, int samplerate);
void raop_service_audio_process(void *cls, void *session, const void *buffer, int buflen);
void raop_service_audio_destroy(void *cls, void *session);
void processThreadFunc(void* ctx);

class RaopService {
public:
	static RaopService* shared();

	void expose(std::string serverName, unsigned short port = 5000);
	bool isExposed();
	void hide();
	
	int getSampleSize();
	int getSampleRate();
	
	typedef boost::circular_buffer<uint8_t> AudioBuffer;
	
	void registerAudioHandler(AudioHandler* handler);
	void unregisterAudioHandler(AudioHandler* handler);
	
private:
	RaopService();
	~RaopService();
	static RaopService* sService;

	void handleAudioStarted();
	void handleAudio(AudioSession* session);
	void handleAudioEnded();

	std::set<AudioHandler*> mAudioHandlers;

	dnssd_t* mDnssdRef;
	raop_t* mRaopRef;

	AudioSession* mSession;
	
	float mBufferTime;
	
	friend void raop_service_audio_process(void *cls, void *session, const void *buffer, int buflen);
	friend void* raop_service_audio_init(void *cls, int bits, int channels, int samplerate);
	friend void raop_service_audio_flush(void *cls, void *session);
	friend void raop_service_audio_destroy(void *cls, void *session);
	friend void consumerThreadFunc(void* ctx);
};

#endif /* RaopService_hpp */
