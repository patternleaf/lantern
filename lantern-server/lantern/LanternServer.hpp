//
//  LanternServer.hpp
//  lantern
//
//  Created by Eric Miller on 1/17/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

#ifndef LanternServer_hpp
#define LanternServer_hpp

#include <stdio.h>
#include <set>
#include "websocketpp/server.hpp"
#include "websocketpp/config/core.hpp"
#include "websocketpp/config/asio.hpp"
#include "lib/tinythread.h"

#include "LanternState.hpp"

typedef websocketpp::server<websocketpp::config::asio> WSServer;

class LanternServer {
	
public:
	LanternServer(LanternState* state, int port = 9002);
	~LanternServer();
	
	void broadcastState();
	void broadcast(const std::string& message);
	
private:
	static void serverThreadFunc(void* ctx);
	static void broadcastThreadFunc(void* ctx);
	void onOpen(websocketpp::connection_hdl hdl);
	void onClose(websocketpp::connection_hdl hdl);
	void onMessage(websocketpp::connection_hdl hdl, WSServer::message_ptr msg);
	
private:
	LanternState* mState;

	WSServer mWSServer;
	int mPort;
	bool mIsStopping;
	int mBroadcastSleepDuration;

	typedef std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> ConnectionSet;

	ConnectionSet mConnections;
	std::mutex mConnectionMutex;
	
	tthread::thread* mServerThread;
	tthread::thread* mBroadcastThread;
	
};


#endif /* LanternServer_hpp */
