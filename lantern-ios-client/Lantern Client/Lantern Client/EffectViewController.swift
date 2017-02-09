//
//  EffectViewController.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/3/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import UIKit

class EffectViewController: UIViewController {

	override func viewDidLoad() {
		super.viewDidLoad()
		// Do any additional setup after loading the view, typically from a nib.
	}

	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}

	var controlViews: [UIView] = []

	func showEffect(atIndex: Int) {
		for view in controlViews {
			view.removeFromSuperview()
		}
		controlViews = []
	}

}

