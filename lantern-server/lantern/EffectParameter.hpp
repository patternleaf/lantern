//
//  EffectParameter.hpp
//  lantern
//
//  Created by Eric Miller on 2/9/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef EffectParameter_hpp
#define EffectParameter_hpp

#include <stdio.h>
#include "lib/json.hpp"

// maybe will upgrade to generics/type safety someday ...
class EffectParameter {
public:
	EffectParameter(nlohmann::json json);
	void setState(nlohmann::json json);
	nlohmann::json getState();
	
	std::string getId();
protected:
	std::string mId;
	nlohmann::json mState;
};

#endif /* EffectParameter_hpp */
