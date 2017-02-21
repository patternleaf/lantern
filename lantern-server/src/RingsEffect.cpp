//
//  RingsEffect.cpp
//  lantern
//
//  Created by Eric Miller on 2/9/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#include "RingsEffect.hpp"

using namespace nlohmann;

json RingsEffect::getState()
{
	return {
		{ "id", mId },
		{ "name", "Rings" },
		{ "parameters", getParameters() }
	};
}

void RingsEffect::setState(json state)
{
	
}

json RingsEffect::getParameters()
{
	return json::array();
}

EffectRegistry::EffectFactory RingsEffect::getFactory()
{
	Texture paletteCopy(palette);
	return EffectRegistry::EffectFactory("rings", [paletteCopy]() { return new RingsEffect(paletteCopy); });
}
