//
//  CheckerCubeIds.h
//  lantern
//
//  Created by Eric Miller on 1/16/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef CheckerCubeIds_h
#define CheckerCubeIds_h

#include <vector>

//static int ids[] = { 0, 2, 3, 5, 7, 9, 10, 12, 14, 16, 18, 20 };
static int ids[] = { 0, 1, 3, 5 };
static std::vector<int> kCheckerCubeIds(ids, ids + sizeof(ids) / sizeof(ids[0]));

//bool isCheckerCubeId(int cubeId) {
//	return std::find(kCheckerCubeIds.begin(), kCheckerCubeIds.end(), cubeId) == kCheckerCubeIds.end();
//}

inline bool isCheckerCubeId(int cubeId) {
	return std::find(kCheckerCubeIds.begin(), kCheckerCubeIds.end(), cubeId) == kCheckerCubeIds.end();
}


#endif /* CheckerCubeIds_h */
