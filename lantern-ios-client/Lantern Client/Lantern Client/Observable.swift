//
//  Observable.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/6/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation

/* oh, swift ...

protocol Observable {

	var observers: [Observer] { get set }

	func notifyObservers()
	func addObserver(observable: Observer)
	func removeObserver(observable: Observer)
}

protocol Observer {
	func observableDidUpdate()
}

extension Observable {
	func notifyObservers() {
		for observer in observers {
			observer.observableDidUpdate()
		}
	}
	
	mutating func addObserver(observer: Observer) {
		observers.append(observer)
	}
	
	mutating func removeObserver(observer: Observer) {
		var i = 0
		for ob in observers {
			if ob == observer {
				observers.remove(at: i)
			}
			i += 1
		}
		
	}
}
*/
