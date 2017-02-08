//
//  Channel.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/6/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import Freddy
import RxSwift

class Channel: Model, JSONDecodable, Equatable {

	var effect: Effect?
	var fader: Variable<Float> = Variable<Float>(0)

	required init(json: JSON) throws {
		super.init()
		
		if let effectJson = json["effect"] {
			effect = try Effect(json: effectJson)
		}
		if let faderValue = try? json.getDouble(at: "fader") {
			fader.value = Float(faderValue)
		}	
	}
	
	override func update(json: JSON) throws {
		if let faderValue = try? json.getDouble(at: "fader") {
			fader.value = Float(faderValue)
		}
		if let effect = effect, let effectJson = json["effect"] {
			_ = try? effect.update(json: effectJson)
		}
	}
	
	static func ==(lhs: Channel, rhs: Channel) -> Bool {
		if let leffect = lhs.effect, let reffect = rhs.effect {
			return leffect == reffect
		}
		return false
	}

}


