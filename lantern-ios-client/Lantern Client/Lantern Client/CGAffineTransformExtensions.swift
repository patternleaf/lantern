//
//  CGAffineTransformExtensions.swift
//  ScannerGunTest
//
//  Adapted from https://gist.github.com/detomon/864a6b7c51f8bed7a022
//
//  Created by Eric Miller on 1/20/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//


import Foundation
import CoreGraphics

/**
* CGAffineTransform
*
* var a = CGAffineTransformMakeRotation(45.0 * M_PI / 180.0)
* var b = CGPointMake(30.0, 43.3)
*/

/**
* ...
* a + b
*/
func + (left: CGAffineTransform, right: CGPoint) -> CGAffineTransform {
	return left.translatedBy(x: right.x, y: right.y)
}

/**
* ...
* a += b
*/
func += ( left: inout CGAffineTransform, right: CGPoint) {
	left = left + right
}

/**
* ...
* a - b
*/
func - (left: CGAffineTransform, right: CGPoint) -> CGAffineTransform {
	return left.translatedBy(x: -right.x, y: -right.y)
}

/**
* ...
* a -= b
*/
func -= ( left: inout CGAffineTransform, right: CGPoint) {
	left = left - right
}

/**
* ...
* a * b
*/
func * (left: CGAffineTransform, right: CGPoint) -> CGAffineTransform {
	return left.scaledBy(x: right.x, y: right.y)
}

/**
* ...
* a *= b
*/
func *= ( left: inout CGAffineTransform, right: CGPoint) {
	left = left * right
}

/**
* Multiply transformation with CGPoint
*/
func * (left: CGAffineTransform, right: CGPoint) -> CGPoint {
	return CGPoint(
		x: left.a * right.x + left.b * right.y + left.tx,
		y: left.c * right.x + left.d * right.y + left.ty
	)
}

/**
* Multiply transformation with CGSize
*/
func * (left: CGAffineTransform, right: CGSize) -> CGSize {
	return CGSize(
		width: left.a * right.width + left.b * right.height + left.tx,
		height: left.c * right.width + left.d * right.height + left.ty
	)
}

/**
* Multiply transformation with CGRect
* Only scale and translation operations are meaningful
*/
func * (left: CGAffineTransform, right: CGRect) -> CGRect {
	var point1 = CGPoint(x: right.origin.x, y: right.origin.y)
	var point2 = CGPoint(x: right.maxX, y: right.maxY)
	
	point1 = left * point1
	point2 = left * point2
	
	return CGRect(x: point1.x, y: point1.y, width: point2.x - point1.x, height: point2.y - point1.y)
}

func * (left: CGAffineTransform, right: CGAffineTransform) -> CGAffineTransform {
	// should this be right.concatenating(left) ? 
	return left.concatenating(right)
}

/**
* Rotation operator
*/
infix operator *^ { associativity left precedence 130 }

/**
* Rotate transformation
*
* var transform = CGAffineTransformMakeTranslation(100, 120)
* transform = transform *^ (45.0 * M_PI / 180.0)
*/
func *^ (left: CGAffineTransform, right: CGFloat) -> CGAffineTransform {
	return left.rotated(by: right)
}

/**
* Invert transformation
*
* var transform = CGAffineTransformMakeRotation(127.0 * M_PI / 180.0)
* transform = ~transform
*/
prefix func ~ (left: CGAffineTransform) -> CGAffineTransform {
	return left.inverted()
}
