# lantern-server

An OpenPixelControl LED effect mixer and websocket server built on 
top of @scanlime's [fadecandy](http://github.com/scanlime/fadecandy) 
C++ effects library.

Very much a work in progress! :)

## Features

### Remote Controllable

lantern exposes a websocket server on port 9002. It accepts commands
to change mixer levels, effects parameters, and broadcast current
state.

### Airplay Server

lantern uses [shairplay](https://github.com/juhovh/shairplay) to 
expose an Airplay server. By streaming audio to speakers and to
lantern at the same time, you can build audio-reactive effects 
without the hassle of audio input hardware. 

lantern also uses [Gist](https://github.com/adamstark/Gist)

## Building / Installation

Intended to compile on OSX via the XCode project, or on a Raspberry 
Pi 3 (Raspbian Jessie w/Pixel kernel 4.4).

A few things you may need to install (assuming raspbian or other 
linux-y device):

```
sudo apt-get install uuid-dev
sudo apt-get install libboost-dev
sudo apt-get install libboost-system-dev
sudo apt-get install libssl-dev
sudo apt-get install autoconf automake libtool
sudo apt-get install libltdl-dev libao-dev libavahi-compat-libdnssd-dev
sudo apt-get install avahi-daemon
```

A few things you will definitely need to install. cd to the project 
directory and:

```
git submodule init
git submodule update
```

Follow the instructions to build and install a couple of dependent 
libraries:

- [/lib/shairplay](https://github.com/juhovh/shairplay)
- [FFTW3](http://www.fftw.org)

FFTW is not included as a submodule. You'll have to download it and
install it by hand. Something like:

```
curl -o fftw-3.3.6-pl1.tar.gz http://fftw.org/fftw-3.3.6-pl1.tar.gz
tar -xvzf fftw-3.3.6-pl1.tar.gz
cd fftw-3.3.6-pl1
./configure
make
sudo make install
```

If that doesn't work, see if the 
[FFTW installation page](http://www.fftw.org/fftw2_doc/fftw_6.html)
helps.

Next, wire up shared libraries:

```
sudo ldconfig
```

You should now be ready to build lantern. cd to 
`lantern-server/lantern` (TODO: fix this) and `make`.

Invoke lantern with your layout file.

## Layout Files

Lantern uses the same [JSON LED layout file format](https://github.com/scanlime/fadecandy/tree/master/examples#led-layouts) 
as openpixelcontrol and fadecandy. The home shelf project for which
lantern was built uses the committed layout.json file.

Note that you can embed extra properties about each pixel into the 
layout file and read those proprties from effects.

## A Note About FFT Libraries

Note that Gist is configured to use kiss fft (included in Gist) in 
the XCode project and FFTW via the Makefile. Gist failed its tests 
using kiss fft on the pi, and anyway I suppose fftw should yield 
better performance.

## Dependencies / Credit

- fadecandy
- shairplay
- Gist
- websocketpp
- [openpixelcontrol](https://github.com/zestyping/openpixelcontrol)

## TODO

- Clean up libs folder generally. 
- There are a couple of modifications to fadecandy's headers needed to 
  build. Make a proper branch/fork for this.
- Ability to add/remove effects on the fly from remote clients.
- Separate layout generator / layout files in some reasonable way.
- Don't crash on layout files lacking lantern-specific properties.


## Wishlist

- Larger library of effects.