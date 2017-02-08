//
//  Mixer.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/6/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import Freddy
import RxSwift
import RxCocoa

class Mixer : Model {

	var channels: Variable<[Channel]>
	
	override init() {
		channels = Variable<[Channel]>([])
		super.init()
	}
	
	
	override func update(json: JSON) {
		
		if let incomingChannels = try? json.getArray(at: "channels") {
			var toRemove: [Channel] = []
			var toAdd: [Channel] = []
			var toUpdate: [(Channel, JSON)] = []
			
			for incomingChannel in incomingChannels {
				if let incomingEffect = incomingChannel["effect"], let incomingId = try? incomingEffect.getString(at: "id") {
					var matchingChannel: Channel?
					for existingChannel in channels.value {
						if let existingEffect = existingChannel.effect, existingEffect.id == incomingId {
							matchingChannel = existingChannel
						}
					}
					if matchingChannel != nil {
						toUpdate.append((matchingChannel!, incomingChannel))
					}
					else {
						if let newChannel = try? Channel(json: incomingChannel) {
							toAdd.append(newChannel)
						}
					}
				}
			}
			
			for existingChannel in channels.value {
				var removeMe: Channel? = existingChannel
				for incomingChannel in incomingChannels {
					if let incomingEffect = incomingChannel["effect"], let incomingId = try? incomingEffect.getString(at: "id") {
						if let effect = existingChannel.effect, effect.id == incomingId {
							removeMe = nil
						}
					}
				}
				if removeMe != nil {
					toRemove.append(removeMe!)
				}
			}
			
			for removeMe in toRemove {
				channels.value.remove(at: channels.value.index(of: removeMe)!)
			}
			
			for addMe in toAdd {
				channels.value.append(addMe)
			}
			
			for (updateMe, json) in toUpdate {
				_ = try? updateMe.update(json: json)
			}
		}
		
	}
}
