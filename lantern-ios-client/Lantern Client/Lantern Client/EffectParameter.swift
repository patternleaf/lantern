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

class EffectParameter: Model, JSONDecodable, JSONEncodable {

//	var id: String?
	var name: Variable<String> = Variable<String>("")
	var type: ParameterType?
	var effect: Effect
	
	required init(json: JSON) throws {
		fatalError("init(json:) has not been implemented")
	}
	
	required init(json: JSON, effect: Effect) throws {
//		id = try json.getString(at: "id")
		name.value = try json.getString(at: "name")
		type = ParameterType(rawValue: try json.getString(at: "type"))
		self.effect = effect
	}
	
	func broadcast() {
		LanternClient.current.sendEffect(effect)
	}
	
	override func update(json: JSON) throws {
		name.value = try json.getString(at: "name")
	}
	
//	static func ==(lhs: EffectParameter, rhs: EffectParameter) -> Bool {
//		return lhs.id == rhs.id
//	}
	
	func toJSON() -> JSON {
		return .dictionary([
//			"id": .string(id!),
			"name": .string(name.value),
			"type": .string(type!.rawValue)
		])
	}
}

class ColorParameter: EffectParameter {
	var color: Variable<UIColor> = Variable<UIColor>(UIColor.black)

	required init(json: JSON) throws {
		fatalError("init(json:) has not been implemented")
	}	

	required init(json: JSON, effect: Effect) throws {
		color.value = UIColor(
			red: CGFloat(try json.getDouble(at: "value", 0)),
			green: CGFloat(try json.getDouble(at: "value", 1)),
			blue: CGFloat(try json.getDouble(at: "value", 2)),
			alpha: 1
		)
		try super.init(json: json, effect: effect)
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
	
	override func toJSON() -> JSON {
		var serialized = try! super.toJSON().getDictionary()
		let components = color.value.components
		serialized["value"] = .array([
			.double(Double(components.red)), .double(Double(components.green)), .double(Double(components.blue))
		])
		return .dictionary(serialized)
	}
}

class PointsParameter: EffectParameter {
	var points: Variable<[CGPoint]> = Variable<[CGPoint]>([])
	
	required init(json: JSON) throws {
		fatalError("init(json:) has not been implemented")
	}
	
	required init(json: JSON, effect: Effect) throws {
		points.value = try json.getArray(at: "value").map({ json throws in
			return CGPoint(x: try json.getDouble(at: 0), y: try json.getDouble(at: 1))
		})
		try super.init(json: json, effect: effect)
	}
	
	override func update(json: JSON) throws {
		try super.update(json: json)
		points.value = try json.getArray(at: "value").map({ json throws in
			return CGPoint(x: try json.getDouble(at: 0), y: try json.getDouble(at: 1))
		})
	}
	
	override func toJSON() -> JSON {
		var serialized = try! super.toJSON().getDictionary()
		serialized["value"] = .array(points.value.map { return .array([
			.double(Double($0.x)),
			.double(Double($0.y)),
			.double(Double(0)),
		]) })
		
		return .dictionary(serialized)
	}
}

class RealParameter: EffectParameter {
	var real = Variable<Float>(0)
	var rangeStart = Variable<Float>(0)
	var rangeEnd = Variable<Float>(0)
	
	required init(json: JSON) throws {
		fatalError("init(json:) has not been implemented")
	}
	
	required init(json: JSON, effect: Effect) throws {
		real.value = Float(try json.getDouble(at: "value"))
		rangeStart.value = Float(try json.getDouble(at: "range", 0))
		rangeEnd.value = Float(try json.getDouble(at: "range", 1))
		try super.init(json: json, effect: effect)
	}
	
	override func update(json: JSON) throws {
		try super.update(json: json)
		real.value = Float(try json.getDouble(at: "value"))
		rangeStart.value = Float(try json.getDouble(at: "range", 0))
		rangeEnd.value = Float(try json.getDouble(at: "range", 1))
	}
	
	override func toJSON() -> JSON {
		var serialized = try! super.toJSON().getDictionary()
		serialized["real"] = .double(Double(real.value))
		serialized["range"] = .array([
			.double(Double(rangeStart.value)),
			.double(Double(rangeEnd.value))
		])
		return .dictionary(serialized)
	}
}
