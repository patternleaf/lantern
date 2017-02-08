//
//  Effect.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/6/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import Freddy
import RxSwift
import RxCocoa

class Effect: Model, JSONDecodable, Equatable {
	
	var id: String?
	var name: Variable<String> = Variable<String>("")
	
	required init(json: JSON) throws {
		id = try json.getString(at: "id")
		if id == "unknown-effect" {
			name.value = "Unknown Effect"
		}
		else {
			name.value = try json.getString(at: "name")
		}
		
	}
	
	override func update(json: JSON) throws {
		if id == "unknown-effect" {
			name.value = "Unknown Effect"
		}
		else {
			name.value = try json.getString(at: "name")
		}
	}
	
	static func ==(lhs: Effect, rhs: Effect) -> Bool {
		if let lid = lhs.id, let rid = rhs.id {
			return lid == rid
		}
		return false
	}
}

