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
	
	// assumes that the number of points won't change!
	var movingPointIndex: Int?

	let lanternWidth: CGFloat = 1.83		// meters; points sent to server expressed in meters
	var frameOffset = CGPoint.zero
	var pointScale: CGFloat
	
	init(parameter: PointsParameter) {
		outlinesView = UIImageView(image: UIImage(named: "outlines"))
		
		pointScale = 1
		
		super.init(parameter: parameter)
		
		let touchGesture = UILongPressGestureRecognizer(target: self, action: #selector(touchRecognized(gestureRecognizer:)))
		touchGesture.minimumPressDuration = 0
		touchGesture.allowableMovement = CGFloat.greatestFiniteMagnitude
		addGestureRecognizer(touchGesture)
		
		addSubview(outlinesView)
		
		isExclusiveTouch = true
		
		translatesAutoresizingMaskIntoConstraints = false
		outlinesView.translatesAutoresizingMaskIntoConstraints = false
		
		let widthConstraint = outlinesView.widthAnchor.constraint(equalTo: widthAnchor, multiplier: 0.7)
		
		outlinesView.centerYAnchor.constraint(equalTo: centerYAnchor).isActive = true
		outlinesView.centerXAnchor.constraint(equalTo: centerXAnchor).isActive = true
		
		// aspect ratio constraint
		outlinesView.heightAnchor.constraint(equalTo: outlinesView.widthAnchor).isActive = true
		
		// max height
		outlinesView.heightAnchor.constraint(equalTo: heightAnchor, multiplier: 0.8).isActive = true
		
		// sacrifice width if needed
		widthConstraint.priority = 750
		widthConstraint.isActive = true
		
		parameter.points.asDriver().asObservable().subscribe(onNext: { newPoints in
			self.updatePointViews(withPoints: newPoints)
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
		
			if movingPointIndex == nil {
				movingPointIndex = getClosestPointViewIndex(to: point)
			}
			
			if let index = movingPointIndex, index <= pointViews.count {
				let pt = pointViews[index]
				pt.frame.origin = (CGVector(point: point) + CGVector(dx: -15, dy: -15)).asPoint()
				updateParameter()
			}
			
			if gestureRecognizer.state == .ended {
				movingPointIndex = nil
				updateParameter()
			}
		}
		
	}
	
	func updatePointViews(withPoints newPoints: [CGPoint]) {
		for pointView in self.pointViews {
			pointView.removeFromSuperview()
		}
		
		self.pointScale = self.outlinesView.frame.width / self.lanternWidth
		self.frameOffset = self.outlinesView.frame.origin
		
		// TODO: don't suck quite so much.
		self.pointViews = []
		for newPoint in newPoints {
			self.createPointView(forPoint: newPoint)
		}

	}
	
	func createPointView(forPoint point: CGPoint) {
		let newView = UIImageView(image: UIImage(named: "reticle"))
		newView.frame.origin = frameOffset
		newView.frame.origin.x += (point.x * pointScale)
		newView.frame.origin.y += (point.y * pointScale)
		newView.frame.size = CGSize(width: 30, height: 30)
		pointViews.append(newView)
		addSubview(newView)
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
	
	override func layoutSubviews() {
		super.layoutSubviews()
		updatePointViews(withPoints: (parameter as! PointsParameter).points.value)
	}
	
	func getClosestPointViewIndex(to otherPoint: CGPoint) -> Int? {
		var closestViewIndex: Int?
		var smallestDistance: CGFloat = 100000
		for index in (0 ..< pointViews.count) {
			let pointView = pointViews[index]
			let d = distance(a: pointView.frame.origin, b: otherPoint)
			if d < smallestDistance {
				smallestDistance = d
				closestViewIndex = index
			}
		}
		
		return closestViewIndex
	}
	
	func distance(a: CGPoint, b: CGPoint) -> CGFloat {
		let xDist = a.x - b.x
		let yDist = a.y - b.y
		return CGFloat(sqrt((xDist * xDist) + (yDist * yDist)))
	}
	
	func updateParameter() {
		
		pointScale = outlinesView.frame.width / self.lanternWidth
		frameOffset = outlinesView.frame.origin
		
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
//		print("parameter updated", pointsParameter.points.value)
	}
}
