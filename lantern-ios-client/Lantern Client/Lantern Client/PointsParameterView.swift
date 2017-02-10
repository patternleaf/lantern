//
//  PointsParameterView.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/9/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import UIKit

class PointsParameterView: ParameterView {

	var outlinesView: UIImageView!
	var pointViews: [UIImageView] = []
	var movingPoint: UIImageView?

	let frameOffset = CGPoint(x: 150, y: 80)
	let outlinesDimension:CGFloat = 300
	var pointScale: CGFloat
	
	var isMovingPoint: Bool

	init(parameter: PointsParameter) {
		outlinesView = UIImageView(image: UIImage(named: "outlines"))
		
		pointScale = outlinesDimension / 2
		
		isMovingPoint = false
		
		super.init(parameter: parameter)
		
		let touchGesture = UILongPressGestureRecognizer(target: self, action: #selector(self.touchRecognized(gestureRecognizer:)))
		touchGesture.minimumPressDuration = 0
		touchGesture.allowableMovement = CGFloat.greatestFiniteMagnitude
		self.addGestureRecognizer(touchGesture)
		
		addSubview(outlinesView)
		
		isExclusiveTouch = true
		
		outlinesView.frame = CGRect(x: frameOffset.x, y: frameOffset.y, width: outlinesDimension, height: outlinesDimension)
		
		parameter.points.asDriver().asObservable().subscribe(onNext: { newPoints in
			if !self.isMovingPoint {
				for pointView in self.pointViews {
					pointView.removeFromSuperview()
				}
				
				self.pointViews = []
				
				for newPoint in newPoints {
					let newView = UIImageView(image: UIImage(named: "reticle"))
					newView.frame.origin = self.frameOffset
					newView.frame.origin.x += (newPoint.x * self.pointScale)
					newView.frame.origin.y += (newPoint.y * self.pointScale)
					newView.frame.size = CGSize(width: 20, height: 20)
					self.pointViews.append(newView)
					self.addSubview(newView)
				}
			}
			else {
				print("holding off on update from server")
			}
		}).addDisposableTo(disposeBag)
	}
	
	override var requiredHeight: CGFloat {
		return 400
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}
	
	func touchRecognized(gestureRecognizer: UILongPressGestureRecognizer) {
		let point = gestureRecognizer.location(in: self)
		
		if gestureRecognizer.state == .began && !outlinesView.frame.contains(point) {
			gestureRecognizer.cancelsTouchesInView = false
		}
		else {
			gestureRecognizer.cancelsTouchesInView = true
		
			if movingPoint == nil {
				movingPoint = getClosestPointView(to: point)
			}
			else {
				if let pt = movingPoint {
					pt.frame.origin = point
					setNeedsLayout()
					print("setting origin to", pt.frame.origin)
				}
			}
			
			
			
			if gestureRecognizer.state == .ended {
				movingPoint = nil
				updateParameter()
			}
		}
		
	}
	/*
	override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
		isMovingPoint = true
		if let firstTouch = touches.first {
			let loc = firstTouch.location(in: self)
			movingPoint = getClosestPointView(to: loc)
		}
		super.touchesBegan(touches, with: event)
	}
	
	override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
		if let pt = movingPoint, let firstTouch = touches.first {
			pt.frame.origin = firstTouch.location(in: self)
			print("setting origin to", pt.frame.origin)
			setNeedsLayout()
		}
		super.touchesMoved(touches, with: event)
	}
	
	override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
		updateParameter()
		isMovingPoint = false
		super.touchesEnded(touches, with: event)
	}
	*/
	func getClosestPointView(to otherPoint: CGPoint) -> UIImageView? {
		var closestView: UIImageView?
		var smallestDistance: CGFloat = 100000
		for pointView in pointViews {
			let d = distance(a: pointView.frame.origin, b: otherPoint)
			if d < smallestDistance {
				smallestDistance = d
				closestView = pointView
			}
		}
		return closestView
	}
	
	func distance(a: CGPoint, b: CGPoint) -> CGFloat {
		let xDist = a.x - b.x
		let yDist = a.y - b.y
		return CGFloat(sqrt((xDist * xDist) + (yDist * yDist)))
	}
	
	func updateParameter() {
		print("updating parameter")
		let pointsParameter = parameter as! PointsParameter
		var newPoints: [CGPoint] = []
		for pointView in pointViews {
			var newPoint = CGPoint()
			newPoint.x = (pointView.frame.origin.x - frameOffset.x) / pointScale
			newPoint.y = (pointView.frame.origin.y - frameOffset.y) / pointScale
			newPoints.append(newPoint)
		}
		pointsParameter.points.value = newPoints
		LanternClient.current.sendEffect(parameter.effect)
		print("parameter updated", pointsParameter.points.value)
	}
}
