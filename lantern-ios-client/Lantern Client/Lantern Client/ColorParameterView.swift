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
		colorPicker = HSBColorPicker()
		colorWell = UIView()
		
		super.init(parameter: parameter)
		
		translatesAutoresizingMaskIntoConstraints = false
		colorPicker.translatesAutoresizingMaskIntoConstraints = false
		colorWell.translatesAutoresizingMaskIntoConstraints	= false
		
		addSubview(colorPicker)
		addSubview(colorWell)
		
		colorPicker.delegate = self
		
		colorWell.layer.cornerRadius = 10
		colorWell.layer.masksToBounds = true
		
		colorPicker.layer.cornerRadius = 10
		colorPicker.layer.masksToBounds = true
		
		colorWell.backgroundColor = parameter.color.value
		
		colorPicker.leadingAnchor.constraint(equalTo: leadingAnchor, constant: Style.Dim.parameterViewPadding).isActive = true
		colorPicker.topAnchor.constraint(equalTo: nameLabel.bottomAnchor, constant: Style.Dim.parameterViewSpacing).isActive = true
		colorPicker.widthAnchor.constraint(equalTo: widthAnchor, multiplier: 0.6).isActive = true
		colorPicker.heightAnchor.constraint(equalToConstant: 200).isActive = true
		
		colorWell.topAnchor.constraint(equalTo: nameLabel.bottomAnchor, constant: Style.Dim.parameterViewSpacing).isActive = true
		colorWell.leadingAnchor.constraint(equalTo: colorPicker.trailingAnchor, constant: Style.Dim.parameterViewPadding).isActive = true
		colorWell.widthAnchor.constraint(equalTo: widthAnchor, multiplier: 0.2).isActive = true
		colorWell.heightAnchor.constraint(equalToConstant: 200).isActive = true
		
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
