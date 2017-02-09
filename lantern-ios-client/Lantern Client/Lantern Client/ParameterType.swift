//
//  ParameterType.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/9/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import Freddy

enum ParameterType: String {
	case real = "real"
	case points = "points"
	case color = "color"
	
	static func create(json: JSON) throws -> EffectParameter {
		let typeString = try json.getString(at: "type")
		if let type = ParameterType(rawValue: typeString) {
			switch type {
			case .real: return try RealParameter(json: json)
			case .points: return try PointsParameter(json: json)
			case .color: return try ColorParameter(json: json)
			}
		}
		throw Model.ErrorType.unknownParameterType(typeString)
	}
}
