appname := lantern

#CXX := g++-5
CXXFLAGS := -std=c++11 -I.. -I../lib -I../lib/websocketpp -I../lib/shairplay/include -I../lib/Gist/src/ -I../lib/Gist/libs/kiss_fft130

CXXFLAGS += -DUSE_KISSFFT

srcfiles := $(shell find . -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

LDLIBS += -pthread

LDFLAGS += -luuid -lboost_system -lssl -lcrypto -lshairplay

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
