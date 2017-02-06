//
//  ChannelView.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/3/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import UIKit

class ChannelView: UIView {

	var effectId: String

	init(effectId: String) {
		self.effectId = effectId
		super.init(frame: CGRect.zero)
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}
	
	
	
}
