//
//  Style.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/9/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import UIKit


class Style {

	struct Color {
		static let light = UIColor(withInt32: 0x91BAE5FF)
		static let mid = UIColor(withInt32: 0x799BBFFF)
		static let shadow = UIColor(withInt32: 0x51677FFF)
		static let dark = UIColor(withInt32: 0x283440FF)
		static let highlight = UIColor(withInt32: 0xFFF3A1FF)
	}

	/*
	Font Family Name = [Helvetica Neue]
	Font Names = [["HelveticaNeue-Italic", "HelveticaNeue-Bold", "HelveticaNeue-UltraLight", "HelveticaNeue-CondensedBlack", "HelveticaNeue-BoldItalic", "HelveticaNeue-CondensedBold", "HelveticaNeue-Medium", "HelveticaNeue-Light", "HelveticaNeue-Thin", "HelveticaNeue-ThinItalic", "HelveticaNeue-LightItalic", "HelveticaNeue-UltraLightItalic", "HelveticaNeue-MediumItalic", "HelveticaNeue"]]
	*/
	struct Font {
		static let parameterLabel = UIFont(name: "HelveticaNeue-Bold", size: 30)
		static let bigControl = UIFont(name: "HelveticaNeue-Thin", size: 80)
	}
	
}

extension UIColor {
	// cf http://alisoftware.github.io/swift/enum/constants/2015/07/19/enums-as-constants/
	convenience init(withInt32 int32: UInt32) {
		let rgbaValue = int32
		let red   = CGFloat((rgbaValue >> 24) & 0xff) / 255.0
		let green = CGFloat((rgbaValue >> 16) & 0xff) / 255.0
		let blue  = CGFloat((rgbaValue >>  8) & 0xff) / 255.0
		let alpha = CGFloat((rgbaValue      ) & 0xff) / 255.0
		
		self.init(red: red, green: green, blue: blue, alpha: alpha)
	}
}

extension UIColor {
	var coreImageColor: CIColor {
		return CIColor(color: self)
	}
	var components: (red: CGFloat, green: CGFloat, blue: CGFloat, alpha: CGFloat) {
		let color = coreImageColor
		return (color.red, color.green, color.blue, color.alpha)
	}
}
