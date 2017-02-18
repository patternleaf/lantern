//
//  JsonConversions.hpp
//  lantern
//
//  Created by Eric Miller on 1/25/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef JsonConversions_hpp
#define JsonConversions_hpp

#include <stdio.h>
#include "lib/json.hpp"


namespace JsonConversions {
	
	template <class T>
	nlohmann::json toJson(const T& value);
	
	template <class T>
	T fromJson(const nlohmann::json& json);
};

#endif /* JsonConversions_hpp */
