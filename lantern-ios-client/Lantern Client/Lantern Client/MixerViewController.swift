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

	override func viewDidLoad() {
		super.viewDidLoad()
		// Do any additional setup after loading the view, typically from a nib.
		
		tableView.delegate = nil
		tableView.dataSource = nil
		
		tableView.rowHeight = 80
		
		State.current.mixer.channels
			.asObservable()
			.bindTo(tableView.rx.items(cellIdentifier: "ChannelCell")) { (row, element, cell) in
				let view = ChannelStripView(channel: element, index: row)
				cell.addSubview(view)
			}
			.addDisposableTo(disposeBag)
		
		tableView.rx.itemSelected.subscribe(onNext: { value in
			
		}).addDisposableTo(disposeBag)
	}

	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}

}

