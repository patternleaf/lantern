//
//  EffectViewController.swift
//  Lantern Client
//
//  Created by Eric Miller on 2/3/17.
//  Copyright © 2017 patternleaf LLC. All rights reserved.
//

import UIKit

class EffectViewController: UIViewController {

	var stackView: UIStackView!
	var scrollView: UIScrollView!
	var contentView: UIView!
	var contentViewHeightConstraint: NSLayoutConstraint!
	var noParametersLabel: UILabel!

	override func viewDidLoad() {
		super.viewDidLoad()
		// Do any additional setup after loading the view, typically from a nib.
		
		scrollView = UIScrollView()
		scrollView.translatesAutoresizingMaskIntoConstraints = false
		view.addSubview(scrollView)
		
		scrollView.leadingAnchor.constraint(equalTo: view.leadingAnchor).isActive = true
		scrollView.trailingAnchor.constraint(equalTo: view.trailingAnchor).isActive = true
		scrollView.topAnchor.constraint(equalTo: view.topAnchor).isActive = true
		scrollView.bottomAnchor.constraint(equalTo: view.bottomAnchor).isActive = true
		
		scrollView.canCancelContentTouches = false
		
		contentView = UIView()
		scrollView.addSubview(contentView)
		contentView.translatesAutoresizingMaskIntoConstraints = false
		
//		contentView.backgroundColor = UIColor.red
//		scrollView.backgroundColor = UIColor.green
		
		contentView.widthAnchor.constraint(equalTo: view.widthAnchor).isActive = true
		contentView.topAnchor.constraint(equalTo: scrollView.topAnchor).isActive = true
		contentView.leadingAnchor.constraint(equalTo: scrollView.leadingAnchor).isActive = true

		contentViewHeightConstraint = contentView.heightAnchor.constraint(equalToConstant: 0)
		contentViewHeightConstraint.isActive = true
		
		view.backgroundColor = Style.Color.dark
		
		noParametersLabel = UILabel()
		noParametersLabel.translatesAutoresizingMaskIntoConstraints = false
		view.addSubview(noParametersLabel)
		
		
		noParametersLabel.widthAnchor.constraint(equalTo: view.widthAnchor).isActive = true
		noParametersLabel.heightAnchor.constraint(equalToConstant: 200).isActive = true
		noParametersLabel.centerXAnchor.constraint(equalTo: view.centerXAnchor).isActive = true
		noParametersLabel.centerYAnchor.constraint(equalTo: view.centerYAnchor).isActive = true
		
		noParametersLabel.font = Style.Font.noParametersLabel
		noParametersLabel.textColor = Style.Color.light
		noParametersLabel.text = "No Parameters"
		noParametersLabel.textAlignment = .center
		noParametersLabel.isHidden = true
		
	}

	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}

	func showEffect(atIndex effectIndex: Int) {

		for view in contentView.subviews {
			view.removeFromSuperview()
		}
		
		
		if let effect = State.current.mixer.channels.value[effectIndex].effect {
			var lastParameterView: ParameterView? = nil
			var height: CGFloat = 0
			for parameter in effect.parameters.value {
				if let parameterView = makeParameterView(for: parameter) {
				
					contentView.addSubview(parameterView)
					
					parameterView.widthAnchor.constraint(equalTo: view.widthAnchor, multiplier: 1).isActive = true
										
					if lastParameterView != nil {
						parameterView.topAnchor.constraint(equalTo: lastParameterView!.bottomAnchor, constant: 8).isActive = true
					}
					else {
						parameterView.topAnchor.constraint(equalTo: contentView.topAnchor).isActive = true
					}
					
					parameterView.leadingAnchor.constraint(equalTo: contentView.leadingAnchor).isActive = true
					
					height += parameterView.requiredHeight
					lastParameterView = parameterView

				}
			}
			
			if effect.parameters.value.count == 0 {
				noParametersLabel.isHidden = false
			}
			else {
				noParametersLabel.isHidden = true
			}
//			print("setting height constant", height)
			contentViewHeightConstraint.constant = height
			view.setNeedsLayout()
			view.setNeedsUpdateConstraints()
//			print("content view frame height", contentView.frame.height)
		}
		
	}
	
	override func viewDidLayoutSubviews() {
		var height:CGFloat = 0
		for view in contentView.subviews {
			if let parameterView = view as? ParameterView {
//				print("   view frame", view.frame)
//				print("   view required height", parameterView.requiredHeight)
				height += parameterView.requiredHeight
			}
		}
		
		scrollView.contentSize.height = height // this shouldn't be necessary ... ?!?
		
		contentViewHeightConstraint.constant = height
//		print("height (again)", contentView.frame.height)
//		print("scrollview height:", scrollView.frame.height)
	}
	
	// where should this knowledge live?
	func makeParameterView(for parameter: EffectParameter) -> ParameterView? {
		if let type = parameter.type {
			switch type {
			case .color: return ColorParameterView(parameter: parameter as! ColorParameter)
			case .real: return RealParameterView(parameter: parameter as! RealParameter)
			case .points: return PointsParameterView(parameter: parameter as! PointsParameter)
			}
		}
		return nil
	}

}

