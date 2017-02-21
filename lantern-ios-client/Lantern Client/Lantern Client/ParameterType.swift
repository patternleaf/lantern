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
	case range = "range"
	
	static func create(json: JSON, effect: Effect) throws -> EffectParameter {
		let typeString = try json.getString(at: "type")
		if let type = ParameterType(rawValue: typeString) {
			switch type {
			case .real: return try RealParameter(json: json, effect: effect)
			case .points: return try PointsParameter(json: json, effect: effect)
			case .color: return try ColorParameter(json: json, effect: effect)
			case .range: return try RangeParameter(json: json, effect: effect)
			}
		}
		throw Model.ErrorType.unknownParameterType(typeString)
	}
}
