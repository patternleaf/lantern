//
//  ColorParameterView.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/8/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import UIKit

class ColorParameterView: ParameterView, HSBColorPickerDelegate {
	var colorPicker: HSBColorPicker!
	var colorWell: UIView!
	
	init(parameter: ColorParameter) {
		colorPicker = HSBColorPicker(frame: CGRect(x: 20, y: 80, width: 400, height: 200))
		colorWell = UIView(frame: CGRect(x: 450, y: 80, width: 200, height: 200))
		
		super.init(parameter: parameter)
		
		addSubview(colorPicker)
		addSubview(colorWell)
		
		colorPicker.delegate = self
		
		colorWell.layer.cornerRadius = 10
		colorWell.layer.masksToBounds = true
		
		colorPicker.layer.cornerRadius = 10
		colorPicker.layer.masksToBounds = true
		
		colorWell.backgroundColor = parameter.color.value
		
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}
	
	override var requiredHeight: CGFloat {
		return 330
	}
	
	func HSBColorColorPickerTouched(sender: HSBColorPicker, color: UIColor, point: CGPoint, state: UIGestureRecognizerState) {
		colorWell.backgroundColor = color
		let components = color.components
		if !components.red.isNaN && !components.green.isNaN && !components.blue.isNaN {
			(parameter as! ColorParameter).color.value = color
			LanternClient.current.sendEffect(parameter.effect)
		}
	}
	
}
