//
//  LanternEffect.hpp
//  lantern
//
//  Created by Eric Miller on 1/24/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef LanternEffect_hpp
#define LanternEffect_hpp

#include <stdio.h>
#include <mutex>
#include "lib/effect.h"
#include "EffectParameter.hpp"
#include "JsonConversions.hpp"
#include "EffectRegistry.hpp"

class LanternEffect : public Effect {
public:
	LanternEffect();
	virtual ~LanternEffect();

	virtual nlohmann::json getState() = 0;
	virtual void setState(nlohmann::json state) = 0;
	virtual nlohmann::json getParameters() = 0;
	
	virtual EffectRegistry::EffectFactory getFactory() = 0;
	
	void cacheStateUpdate(nlohmann::json state);
	virtual void beginFrame(const FrameInfo &f);
	
	std::string getId();
	
	typedef std::function<void(nlohmann::json event)> EventHandler;
	
	void subscribe(EventHandler handler);
	
protected:

	void broadcast(nlohmann::json event);
	nlohmann::json mLatestUpdate;
	std::string mId;
	std::vector<EventHandler> mHandlers;
	
	std::mutex mStateMutex;
	
};

#endif /* LanternEffect_hpp */
