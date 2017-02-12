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
		
		translatesAutoresizingMaskIntoConstraints = false
		slider.translatesAutoresizingMaskIntoConstraints = false
		effectName.translatesAutoresizingMaskIntoConstraints = false
		
		slider.maximumValue = 1
		slider.minimumValue = 0

		addSubview(slider)
		addSubview(effectName)

		effectName.font = Style.Font.channelStripName
		effectName.textColor = Style.Color.highlight
		
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
			
			topAnchor.constraint(equalTo: parent.topAnchor).isActive = true
			bottomAnchor.constraint(equalTo: parent.bottomAnchor).isActive = true
			leadingAnchor.constraint(equalTo: parent.leadingAnchor).isActive = true
			trailingAnchor.constraint(equalTo: parent.trailingAnchor).isActive = true
			
			effectName.leadingAnchor.constraint(equalTo: leadingAnchor, constant: 12).isActive = true
			effectName.topAnchor.constraint(equalTo: topAnchor, constant: 12).isActive = true
			
			effectName.widthAnchor.constraint(equalTo: widthAnchor).isActive = true
			effectName.heightAnchor.constraint(equalToConstant: 30).isActive = true
			
			slider.leadingAnchor.constraint(equalTo: leadingAnchor, constant: 12).isActive = true
			slider.centerYAnchor.constraint(equalTo: centerYAnchor).isActive = true
			slider.widthAnchor.constraint(equalTo: widthAnchor, constant: -60).isActive = true
			slider.heightAnchor.constraint(equalToConstant: 40).isActive = true
			

		}
	}
	
	
	
}
