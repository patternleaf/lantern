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
	var numberFormatter: NumberFormatter!
	
	init(parameter: RealParameter) {
	
		label = UILabel(frame: CGRect(x: 380, y: 70, width: 200, height: 200))
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
	
		numberFormatter = NumberFormatter()
		numberFormatter.numberStyle = .decimal
		numberFormatter.minimumFractionDigits = 1
		numberFormatter.maximumFractionDigits = 1
	
		super.init(parameter: parameter)
	
		parameter.rangeEnd.asDriver().asObservable().subscribe(onNext: { (value: Float) -> Void in
			self.slider.maximumValue = CGFloat(value)
		}).addDisposableTo(disposeBag)
		
		parameter.rangeStart.asDriver().asObservable().subscribe(onNext: { (value: Float) -> Void in
			self.slider.minimumValue = CGFloat(value)
		}).addDisposableTo(disposeBag)
		
		parameter.real.asDriver().asObservable().subscribe(onNext: { (value: Float) -> Void in
			self.slider.endPointValue = CGFloat(value)
			self.label.text = self.numberFormatter.string(from: NSNumber(value: value))
		}).addDisposableTo(disposeBag)

		slider.addTarget(self, action: #selector(sliderDidChange), for: .valueChanged)
	
		addSubview(slider)
		addSubview(label)
		
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}
	
	override var requiredHeight: CGFloat {
		return 300
	}
	
	func sliderDidChange() {
		(parameter as! RealParameter).real.value = Float(slider.endPointValue)
		LanternClient.current.sendEffect(parameter.effect)
	}
}
