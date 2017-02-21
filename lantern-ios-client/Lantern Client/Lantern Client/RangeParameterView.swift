//
//  RangeParameterView.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/20/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import UIKit
import HGCircularSlider

class RangeParameterView : RealParameterView {

	init(parameter: RangeParameter) {
		super.init(parameter: parameter)
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}

	override func createSlider(with rect: CGRect) -> CircularSlider {
		return RangeCircularSlider(frame: rect)
	}
	
	override func observeParameter(_ parameter: EffectParameter) {
		if let parameter = parameter as? RangeParameter {
			parameter.rangeEnd.asDriver().asObservable().subscribe(onNext: { (value: Float) -> Void in
				self.slider.maximumValue = CGFloat(value)
			}).addDisposableTo(disposeBag)
			
			parameter.rangeStart.asDriver().asObservable().subscribe(onNext: { (value: Float) -> Void in
				self.slider.minimumValue = CGFloat(value)
			}).addDisposableTo(disposeBag)
			
			parameter.startValue.asDriver().asObservable().subscribe(onNext: { (value: Float) -> Void in
				(self.slider as! RangeCircularSlider).startPointValue = CGFloat(value)
			}).addDisposableTo(disposeBag)
			
			parameter.endValue.asDriver().asObservable().subscribe(onNext: { (value: Float) -> Void in
				self.slider.endPointValue = CGFloat(value)
			}).addDisposableTo(disposeBag)
		}
	}
	
	override func sliderDidChange() {
		(parameter as! RangeParameter).startValue.value = Float((slider as! RangeCircularSlider).startPointValue)
		(parameter as! RangeParameter).endValue.value = Float(slider.endPointValue)
		LanternClient.current.sendEffect(parameter.effect)
	}
}
