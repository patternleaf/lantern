//
//  State.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/6/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation

class State {

	static private var _current: State?
	
	static var current: State {
		if _current == nil {
			_current = State()
		}
		return _current!
	}

	var mixer: Mixer

	private init() {
		mixer = Mixer()
	
		NotificationCenter.default.addObserver(
			self,
			selector: #selector(serverStateDidChange),
			name: NSNotification.Name("server-state-changed"),
			object: nil
		)
	}
	
	@objc func serverStateDidChange() {
		if let json = LanternClient.current.latestStateJson {
			mixer.update(json: json)
		}
	}

	
}
