//
//  MixerViewController.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/3/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa

class MixerViewController: UITableViewController {

	var disposeBag: DisposeBag = DisposeBag()

	var selectedChannel: ControlEvent<IndexPath> {
		return tableView.rx.itemSelected
	}

	override func viewDidLoad() {
		super.viewDidLoad()
		// Do any additional setup after loading the view, typically from a nib.
		
		tableView.delegate = nil
		tableView.dataSource = nil
		
		tableView.rowHeight = 120
		
//		tableView.tableHeaderView.
		
		State.current.mixer.channels
			.asObservable()
			.bindTo(tableView.rx.items(cellIdentifier: "ChannelCell")) { (row, element, cell) in
				let view = ChannelStripView(channel: element, index: row)
				let bgColorView = UIView()
				bgColorView.backgroundColor = Style.Color.dark
				cell.selectedBackgroundView = bgColorView
				cell.accessoryType = .disclosureIndicator
				cell.contentView.addSubview(view)
				cell.backgroundColor = Style.Color.shadow
			}
			.addDisposableTo(disposeBag)


		tableView.backgroundColor = Style.Color.shadow
	}

	
	override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
		if segue.identifier == "showEffect" {
			if let indexPath = self.tableView.indexPathForSelectedRow {
				let controller = (segue.destination as! UINavigationController).topViewController as! EffectViewController
				print(indexPath, controller)
			}
		}
	}
	

	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}

	

}

