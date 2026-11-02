//
//  http_server.hpp
//  lantern-server
//
//  Created by Eric Miller on 1/6/18.
//  Copyright © 2018 patternleaf LLC. All rights reserved.
//

#ifndef http_server_hpp
#define http_server_hpp

#include <thread>

class LanternHttpServer {
public:
	LanternHttpServer();
	~LanternHttpServer();
private:
	std::thread mServerThread;
};

#endif /* http_server_hpp */
