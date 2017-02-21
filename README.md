# lantern

![Animated gif of lantern in action.](/images/lantern-gif.gif?raw=true)

lantern is an interactive, audio-reactive home WS2812 LED installation. It consists of:

- a few stackable shelving units
- 336 WS2812 LEDs with some custom mounting/wiring hardware
- a Raspberry Pi 3
- a [fadecandy](https://github.com/scanlime/fadecandy/)
- custom server software, based on @scanlime's [C++ libraries](https://github.com/scanlime/fadecandy/tree/master/examples/cpp)
- custom iOS client software

This repo holds the server and client software, both of which are 
very much **Works In Progress**. :) Current master branch has
a known crash and a totally crap audio reactive effect. 

## Project Goals

The main things I wanted were:

<img src="/images/ipad-interface.png?raw=true" align="right" width="40%" title="Current iOS client interface."/>

- simple warm mood/back-lighting for the shelves
- more colorful lighting effects when desired
- audio-reactive installation/music visualizations for parties
- keep things modular and well-decoupled for reuse happiness, 
  both physically and in software
- ???? the future is unknown -- other forms of interactivity?
- effects and mixer remote-controllable with realtime feedback 
  from iOS devices

I also was on a self-imposed deadline to show off a prototype 
at a get-together in early February 2017. I was very pleased to make
the deadline!

## Technical Bits / Open-Source Love

<img src="/images/strips.jpg?raw=true" align="right" width="40%" title="Mounting hardware and connections."/>

The server should build on ~~OS X~~ macOS and recent versions of 
Raspbian, though there is a fair bit of set-up required there. 
The iOS client is targeting iOS 10. There are separate readmes in 
the client and server directories. 

The server is written in C++ based on @scanlime's awesome
[fadecandy mixer/effect examples](https://github.com/scanlime/fadecandy/tree/master/examples/cpp). 
The client is written in Swift 3. Client-server communication is over 
websockets, using 
[websocketpp](https://github.com/zaphoyd/websocketpp) on the server and
[Starscream](https://github.com/daltoniam/Starscream) on the iOS client.
For easy JSON serialization/deserialization, I'm using @nlohmann's 
[C++ json library](https://github.com/nlohmann/json) and 
[Freddy](https://github.com/bignerdranch/Freddy).

I have dipped my toes into [RxSwift](https://github.com/ReactiveX/RxSwift)
on the client for a clean observer implemntation, but I am barely 
scratching its surface.

Also currently using [HGCircularSlider](https://github.com/HamzaGhazouani/HGCircularSlider).

I use Airplay in my apartment to stream audio to a couple of sets of
speakers. Rather than trying to set up a mic for the Pi, I decided 
to try turning it into an Airplay server which could be targeted 
along with speakers. I have integrated 
[shairplay](https://github.com/juhovh/shairplay) into the server and
it's working pretty well. 

For analaysis of the audio stream I am using the wonderfully 
straightforward [Gist](https://github.com/adamstark/Gist/).

The actual audio visualization is currently really boring so there's
a lot of work to do there. 

<table width="75%">
	<tr>
		<td>
				<img src="/images/getting-started.jpg?raw=true" width="100%" title="Getting started ..."/>
				<p>The shelves themselves are from Closet Maid brand from Home Depot.</p>
		</td>
	</tr>
</table>

<table width="100%">
	<tr>
		<td width="33%">
				<img src="/images/messy.jpg?raw=true" width="100%" title="Messy!"/>
				<p>Messy!</p>
		</td>
		<td width="33%">
				<img src="/images/soldering.jpg?raw=true" width="100%" title="Lots of soldering!"/>
				<p>Lots of soldering!</p>
		</td>
		<td width="33%">
				<img src="/images/power-and-pi.jpg?raw=true" width="100%" title="Less messy ..."/>
				<p>Slightly less messy ...</p>
		</td>
	</tr>
</table>


## TODO / Known Issues

- recent persistence work on server is causing a crash
- settle on some audio reactive effects
- annotate effects that are audio-reactive; show this in client 
  (eg, a speaker icon)
- redesign client interface (prettier; also UISplitView is too 
  restrictive)
- expose some global settings (eg, Airplay buffer size)
- also client-side settings (server hostname at least)
- client should be able to request layout from server and render
  spatial controls based on that
- optimization of client/server synchronization
- .gitignore/repo cruft cleanup
- better documentation, both technically and of project

## Wish List

- turn client into more general-purpose LED installation 
  controller/design tool?

