//
//  AppDelegate.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/3/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import UIKit
import RxSwift

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

	var window: UIWindow?

	var client: LanternClient?

	var disposeBag: DisposeBag = DisposeBag()

	func printFonts() {
		for familyName in UIFont.familyNames {
			print("------------------------------")
			print("Font Family Name = [\(familyName)]")
			let names = UIFont.fontNames(forFamilyName: familyName)
			print("Font Names = [\(names)]")
		}
	}

	func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
		// Override point for customization after application launch.
		
		let splitViewController = self.window!.rootViewController as! UISplitViewController
		let leftNavController = splitViewController.viewControllers.first as! UINavigationController
		let mixerViewController = leftNavController.topViewController as! MixerViewController
		let effectNavController = splitViewController.viewControllers.last as! UINavigationController
		let effectViewController = effectNavController.topViewController as! EffectViewController
				
		mixerViewController.selectedChannel.subscribe(onNext: { indexPath in
			splitViewController.showDetailViewController(effectNavController, sender: nil)
			effectViewController.showEffect(atIndex: indexPath.row)
		}).addDisposableTo(disposeBag)
		
//		printFonts()
		
		effectViewController.navigationItem.leftItemsSupplementBackButton = true
		effectViewController.navigationItem.leftBarButtonItem = splitViewController.displayModeButtonItem
		
		return true
	}

	func applicationWillResignActive(_ application: UIApplication) {
		// Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
		// Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
		
		LanternClient.current.pause()
	}

	func applicationDidEnterBackground(_ application: UIApplication) {
		// Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
		// If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.	
	}

	func applicationWillEnterForeground(_ application: UIApplication) {
		// Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
	}

	func applicationDidBecomeActive(_ application: UIApplication) {
		// Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
		
		LanternClient.current.listen()
	}

	func applicationWillTerminate(_ application: UIApplication) {
		// Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
		
		LanternClient.current.pause()
	}


}

