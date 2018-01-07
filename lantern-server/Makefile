appname := lantern-server

#CXX := g++-5
CXXFLAGS := -std=c++11 -I. -I./lib -I./lib/websocketpp -I./lib/shairplay/include -I./lib/Gist/src/

CXXFLAGS += -DUSE_FFTW

CXXFLAGS += -g

srcfiles := $(shell find ./src -name "*.cpp")

srcfiles += $(shell find ./lib/Gist/src/core -name "*.cpp")
srcfiles += ./lib/Gist/src/fft/WindowFunctions.cpp
srcfiles += $(shell find ./lib/Gist/src/mfcc -name "*.cpp")
srcfiles += $(shell find ./lib/Gist/src/onset-detection-functions -name "*.cpp")
srcfiles += $(shell find ./lib/Gist/src/pitch -name "*.cpp")
srcfiles += ./lib/Gist/src/Gist.cpp

objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

LDLIBS += -pthread -lfftw3

LDFLAGS += -luuid -lboost_system -lboost_filesystem -lssl -lcrypto -lshairplay

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(objects)

dist-clean: clean
	rm -f *~ .depend

include .depend

