//
//  EffectRegistry.hpp
//  lantern
//
//  Created by Eric Miller on 2/9/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef EffectRegistry_hpp
#define EffectRegistry_hpp

#include <stdio.h>
#include <map>

class LanternEffect;
class EffectParameter;

class EffectRegistry {

private:
	EffectRegistry();
	~EffectRegistry();
	static EffectRegistry* sSingleton;
	
public:

	static EffectRegistry* shared();
	
	typedef std::function<LanternEffect*()> FactoryFn;
	typedef std::string FactoryKey;
	typedef std::pair<FactoryKey, FactoryFn> EffectFactory;
	
	void registerFactory(EffectFactory factory);
	LanternEffect* createEffect(std::string effectKey);
	
	void registerEffect(LanternEffect* effect);
	void unregisterEffect(LanternEffect* effect);
	
	void registerParameter(EffectParameter* param);
	void unregisterParameter(EffectParameter* param);
	
	static std::string makeUuid();
	
	EffectParameter* findParameter(const std::string& id);
	LanternEffect* findEffect(const std::string& id);
	
private:

	std::map<std::string, LanternEffect*> mEffects;
	std::map<std::string, EffectParameter*> mParameters;
	
	std::map<std::string, FactoryFn> mFactories;

};

#endif /* EffectRegistry_hpp */
