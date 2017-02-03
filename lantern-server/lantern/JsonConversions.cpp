//
//  JsonConversions.cpp
//  lantern
//
//  Created by Eric Miller on 1/25/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include <sstream>
#include "JsonConversions.hpp"
#include "lib/svl/SVL.h"

using namespace nlohmann;
using namespace std;

template <>
json JsonConversions::toJson<Vec3>(const Vec3& v)
{
	return json::array({ v[0], v[1], v[2] });
}

template <>
Vec3 JsonConversions::fromJson<Vec3>(const json& json)
{
	Vec3 result;
	result[0] = json[0];
	result[1] = json[1];
	result[2] = json[2];
	return result;
}
