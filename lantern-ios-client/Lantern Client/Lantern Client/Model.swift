//
//  Model.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/6/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import Freddy
import RxSwift

class Model {

	enum ErrorType: Error, CustomStringConvertible {
		case unknownParameterType(String)
		case mismatchedParameterCount(String, Int, Int)
		case mismatchedParameterId(String, String)
		
		var description: String {
			switch self {
			
			case let .unknownParameterType(str):
				return "Unknown parameter type: \(str)"
				
			case let .mismatchedParameterCount(effectName, existingCount, incomingCount):
				return "Parameter count from server (\(incomingCount) does not match local count (\(existingCount)) for effect \(effectName)"
			
			case let .mismatchedParameterId(effectName, paramName):
				return "Parameter id from server does not match local parameter id in effect \(effectName), parameter \(paramName)"
			}
		}
	}

	func update(json: JSON) throws {}
	
}
