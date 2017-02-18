
Intended to compile on OSX via the XCode project, or on a raspberry pi 3 (Raspbian Jessie w/Pixel kernel 4.4).

A few things you may need to install (assuming raspbian or other linux-y device):

```
sudo apt-get install uuid-dev
sudo apt-get install libboost-dev
sudo apt-get install libboost-system-dev
sudo apt-get install libssl-dev
```

A few things you will definitely need to install. cd to the project directory and:

```
git submodule init
git submodule update
```

Follow the instructions to build and install dependent libraries:

- [/lib/shairplay](https://github.com/juhovh/shairplay)


