//
//  LanternClient.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/6/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import Starscream
import Freddy

let hostname: String = "localhost"
//let hostname: String = "10.0.0.191"
let port: Int = 9002

class LanternClient: WebSocketDelegate {
	
	static private var _current: LanternClient?
	
	static var current: LanternClient {
		if _current == nil {
			_current = LanternClient()
		}
		return _current!
	}
	
	var socket: WebSocket?
//	var latestStateJson: String?
	var latestStateJson: JSON?
	
	private init() {
		socket = WebSocket(url: URL(string: "ws://\(hostname):\(port)")!)
		socket?.delegate = self
	}
	
	func listen() {
		if let socket = socket, !socket.isConnected {
			socket.connect()
		}
	}
	
	func pause() {
		if let socket = socket, socket.isConnected {
			socket.disconnect()
		}
	}
	
	func websocketDidConnect(socket: WebSocket) {
		print("websocket is connected")
	}
	
	func websocketDidDisconnect(socket: WebSocket, error: NSError?) {
		print("websocket is disconnected: \(error?.localizedDescription)")
	}
	
	func websocketDidReceiveMessage(socket: WebSocket, text: String) {
//		print("got some text: \(text)")
		latestStateJson = try? JSON(jsonString: text)
		
		if latestStateJson != nil {
			NotificationCenter.default.post(name: NSNotification.Name("server-state-changed"), object: nil)
		}		
	}
	
	func websocketDidReceiveData(socket: WebSocket, data: Data) {
		print("got some data: \(data.count)")
	}
	
	func sendFader(channel: Int, value: Float) {
		let json = JSON.dictionary([
			"command": "setFader",
			"channel": .int(channel),
			"value": .double(Double(value))
		])
		if let data = try? json.serialize() {
			socket?.write(data: data)
		}
	}

}
