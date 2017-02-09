//
//  EffectParameter.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/9/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import Freddy
import RxSwift
import RxCocoa

class EffectParameter: Model, JSONDecodable, Equatable {

	var id: String?
	var name: Variable<String> = Variable<String>("")
	var type: ParameterType?
	
	required init(json: JSON) throws {
		id = try json.getString(at: "id")
		name.value = try json.getString(at: "name")
		type = ParameterType(rawValue: try json.getString(at: "type"))
	}

	override func update(json: JSON) throws {
		name.value = try json.getString(at: "name")
	}
	

	static func ==(lhs: EffectParameter, rhs: EffectParameter) -> Bool {
		return lhs.id == rhs.id
	}
}

class ColorParameter: EffectParameter {
	var color: Variable<UIColor> = Variable<UIColor>(UIColor.black)
	
	required init(json: JSON) throws {
		color.value = UIColor(
			red: CGFloat(try json.getDouble(at: "value", 0)),
			green: CGFloat(try json.getDouble(at: "value", 1)),
			blue: CGFloat(try json.getDouble(at: "value", 2)),
			alpha: 1
		)
		try super.init(json: json)
	}
	
	override func update(json: JSON) throws {
		try super.update(json: json)
		color.value = UIColor(
			red: CGFloat(try json.getDouble(at: "value", 0)),
			green: CGFloat(try json.getDouble(at: "value", 1)),
			blue: CGFloat(try json.getDouble(at: "value", 2)),
			alpha: 1
		)
	}
}

class PointsParameter: EffectParameter {
	var points: Variable<[CGPoint]> = Variable<[CGPoint]>([])
	
	required init(json: JSON) throws {
		points.value = try json.getArray(at: "value").map({ json throws in
			return CGPoint(x: try json.getDouble(at: 0), y: try json.getDouble(at: 1))
		})
		try super.init(json: json)
	}
	
	override func update(json: JSON) throws {
		try super.update(json: json)
		points.value = try json.getArray(at: "value").map({ json throws in
			return CGPoint(x: try json.getDouble(at: 0), y: try json.getDouble(at: 1))
		})
	}
}

class RealParameter: EffectParameter {
	var real: Variable<Float> = Variable<Float>(0)
	
	required init(json: JSON) throws {
		real.value = Float(try json.getDouble(at: "value"))
		try super.init(json: json)
	}
	
	override func update(json: JSON) throws {
		try super.update(json: json)
		real.value = Float(try json.getDouble(at: "value"))
	}
}
