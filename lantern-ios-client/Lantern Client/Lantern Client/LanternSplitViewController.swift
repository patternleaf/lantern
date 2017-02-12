//
//  LanternSplitViewController.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/11/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import UIKit

class LanternSplitViewController : UISplitViewController, UISplitViewControllerDelegate {
	override func viewDidLoad() {
		super.viewDidLoad()

		self.delegate = self
		
	}

	func splitViewController(_ splitViewController: UISplitViewController, collapseSecondary secondaryViewController: UIViewController, onto primaryViewController: UIViewController) -> Bool {
		guard let navController = secondaryViewController as? UINavigationController else { return false }
		guard let detailController = navController.topViewController as? EffectViewController else { return false }
		
		if detailController.displayedEffect == nil {
			return true
		}
		return false
	}
	
}
