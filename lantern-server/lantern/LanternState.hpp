//
//  LanternState.hpp
//  lantern
//
//  Created by Eric Miller on 1/24/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef LanternState_hpp
#define LanternState_hpp

#include <stdio.h>
#include <mutex>
#include "lib/effect_runner.h"

#include "JsonConversions.hpp"

#include "LanternMixer.hpp"

class LanternState {
public:
	LanternState(EffectRunner* runner, LanternMixer* mixer);
	~LanternState();
		
	void setWith(nlohmann::json json);
	
	nlohmann::json toJson();
	
private:
	EffectRunner* mRunner;
	LanternMixer* mMixer;
	
	std::mutex mStateMutex;
};


#endif /* LanternState_hpp */
