//
//  RealParameterView.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/8/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import UIKit
import HGCircularSlider
//import HGCircularSlider

class RealParameterView: ParameterView {
	var label: UILabel!
	var slider: CircularSlider!
	
	init(parameter: RealParameter) {
	
		label = UILabel(frame: CGRect(x: 300, y: 70, width: 200, height: 200))
		slider = CircularSlider(frame: CGRect(x: 20, y: 80, width: 200, height: 200))
		slider.backgroundColor = UIColor.clear
		slider.diskColor = UIColor.clear
		slider.diskFillColor = Style.Color.light
		slider.trackColor = Style.Color.mid
		slider.trackFillColor = Style.Color.highlight
		slider.endThumbStrokeColor = Style.Color.mid
		slider.endThumbStrokeHighlightedColor = Style.Color.highlight
		slider.lineWidth = 5
	
		label.textColor = Style.Color.highlight
		label.font = Style.Font.bigControl
	
		super.init(parameter: parameter)
	
		parameter.rangeEnd.asDriver().asObservable().subscribe(onNext: { (value: Float) -> Void in
			self.slider.maximumValue = CGFloat(value)
		}).addDisposableTo(disposeBag)
		
		parameter.rangeStart.asDriver().asObservable().subscribe(onNext: { (value: Float) -> Void in
			self.slider.minimumValue = CGFloat(value)
		}).addDisposableTo(disposeBag)
		
		parameter.real.asDriver().asObservable().subscribe(onNext: { (value: Float) -> Void in
			self.slider.endPointValue = CGFloat(value)
			self.label.text = "\(value)"
		}).addDisposableTo(disposeBag)

		slider.addTarget(self, action: #selector(sliderDidChange), for: .valueChanged)
	
		addSubview(slider)
		addSubview(label)
		
		heightAnchor.constraint(equalToConstant: 300).isActive = true
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}
	
	func sliderDidChange() {
		(parameter as! RealParameter).real.value = Float(slider.endPointValue)
		LanternClient.current.sendEffect(parameter.effect)
	}
}
