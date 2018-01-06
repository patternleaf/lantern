//
//  http_server.cpp
//  lantern-server
//
//  Adapted from https://github.com/labcoder/simple-webserver
//
//  Created by Eric Miller on 1/6/18.
//  Copyright © 2018 patternleaf LLC. All rights reserved.
//

#include "LanternHttpServer.hpp"
#include "lib/Simple-Web-Server/server_http.hpp"

#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

using namespace std;

static HttpServer server;

void configureServer() {
	server.default_resource["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
    try {
      auto web_root_path = boost::filesystem::canonical("data/http-docs");
      auto path = boost::filesystem::canonical(web_root_path / request->path);
      // Check if path is within web_root_path
      if(distance(web_root_path.begin(), web_root_path.end()) > distance(path.begin(), path.end()) ||
         !equal(web_root_path.begin(), web_root_path.end(), path.begin()))
        throw invalid_argument("path must be within root path");
      if(boost::filesystem::is_directory(path))
        path /= "index.html";

      SimpleWeb::CaseInsensitiveMultimap header;

      // Uncomment the following line to enable Cache-Control
      // header.emplace("Cache-Control", "max-age=86400");

      auto ifs = make_shared<ifstream>();
      ifs->open(path.string(), ifstream::in | ios::binary | ios::ate);

      if(*ifs) {
        auto length = ifs->tellg();
        ifs->seekg(0, ios::beg);

        header.emplace("Content-Length", to_string(length));
        response->write(header);

        // Trick to define a recursive function within this scope (for example purposes)
        class FileServer {
        public:
          static void read_and_send(const shared_ptr<HttpServer::Response> &response, const shared_ptr<ifstream> &ifs) {
            // Read and send 128 KB at a time
            static vector<char> buffer(131072); // Safe when server is running on one thread
            streamsize read_length;
            if((read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount()) > 0) {
              response->write(&buffer[0], read_length);
              if(read_length == static_cast<streamsize>(buffer.size())) {
                response->send([response, ifs](const SimpleWeb::error_code &ec) {
                  if(!ec)
                    read_and_send(response, ifs);
                  else
                    cerr << "Connection interrupted" << endl;
                });
              }
            }
          }
        };
        FileServer::read_and_send(response, ifs);
      }
      else
        throw invalid_argument("could not read file");
    }
    catch(const exception &e) {
      response->write(SimpleWeb::StatusCode::client_error_bad_request, "Could not open path " + request->path + ": " + e.what());
    }
  };

  server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
    // Handle errors here
  };

}

LanternHttpServer::LanternHttpServer()
{
	unsigned short port = 8080;
	server.config.port = port;
	configureServer();
	mServerThread = thread([]() { server.start(); });
	std::cout << "HTTP Server listening on " << port << "." << std::endl;
}

LanternHttpServer::~LanternHttpServer()
{
	mServerThread.join();
}


