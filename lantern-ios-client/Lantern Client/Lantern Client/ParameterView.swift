//
//  ParameterView.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/9/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import Foundation
import UIKit
import RxSwift
import RxCocoa

class ParameterView: UIView {
	var parameter: EffectParameter
	var nameLabel: UILabel
	
	var disposeBag: DisposeBag
	
	init(parameter: EffectParameter) {
		self.parameter = parameter
		nameLabel = UILabel()
		disposeBag = DisposeBag()
		
		super.init(frame: CGRect.zero)
		
		translatesAutoresizingMaskIntoConstraints = false
		
		backgroundColor = Style.Color.shadow
		
		addSubview(nameLabel)
		
		
		nameLabel.translatesAutoresizingMaskIntoConstraints = false
		
		nameLabel.widthAnchor.constraint(equalTo: widthAnchor).isActive = true
		nameLabel.heightAnchor.constraint(equalToConstant: 80).isActive = true
		nameLabel.topAnchor.constraint(equalTo: topAnchor, constant: 8).isActive = true
		nameLabel.leadingAnchor.constraint(equalTo: leadingAnchor, constant: 8).isActive = true
		
		parameter.name.asDriver().asObservable().subscribe(onNext: { value in
			self.nameLabel.text = value
		}).addDisposableTo(disposeBag)
	}
	
	required init?(coder aDecoder: NSCoder) {
		fatalError("init(coder:) has not been implemented")
	}
	
	override func didMoveToSuperview() {
		
		
		nameLabel.frame.origin = CGPoint(x: 40, y: 8)
		nameLabel.frame.size = CGSize(width: self.frame.width, height: 30)
		nameLabel.font = Style.Font.parameterLabel
		nameLabel.textColor = Style.Color.light
	}
}
