//
//  ChannelStripView.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/3/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import UIKit
import RxSwift
import RxCocoa

class ChannelStripView: UIView {

	var channel: Channel?
	var index: Int
	var slider: UISlider
	var effectName: UILabel
	
	var disposeBag: DisposeBag = DisposeBag()

	init(channel: Channel, index: Int) {
		self.channel = channel
		self.index = index
		slider = UISlider()
		effectName = UILabel()
		
		super.init(frame: CGRect.zero)
		
		slider.maximumValue = 1
		slider.minimumValue = 0

		addSubview(slider)
		addSubview(effectName)

		effectName.font = Style.Font.channelStripName
		effectName.textColor = Style.Color.highlight
		
		
		backgroundColor = Style.Color.shadow

		channel.fader.asDriver().drive(onNext: { value in
			self.slider.value = value
		}).addDisposableTo(disposeBag)
		
		if let effect = channel.effect {
			effect.name.asDriver().drive(onNext: { value in
				self.effectName.text = value
			}).addDisposableTo(disposeBag)
		}
		
		slider.rx.value.subscribe(onNext: { value in
			LanternClient.current.sendFader(channel: self.index, value: value)
		}).addDisposableTo(disposeBag)
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}

	override func didMoveToSuperview() {
		if let parent = superview {
			frame.size.width = parent.frame.width
			frame.size.height = parent.frame.height
			
			effectName.frame = CGRect(
				origin: CGPoint(x: 12, y: 12),
				size: CGSize(width: parent.frame.width - 12, height: 30)
			)
			slider.frame = CGRect(
				origin: CGPoint(x: 12, y: 40),
				size: CGSize(width: parent.frame.width - 40, height: 40)
			)
		}
	}
	
	
	
}
