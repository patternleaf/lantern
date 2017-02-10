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
		
		view.backgroundColor = Style.Color.dark
		
		print("width: ", view.frame.width)
		scrollView.contentSize.width = view.frame.width / 2
		
		noParametersLabel = UILabel()
		noParametersLabel.translatesAutoresizingMaskIntoConstraints = false
		view.addSubview(noParametersLabel)
		
		
		noParametersLabel.widthAnchor.constraint(equalTo: view.widthAnchor).isActive = true
		noParametersLabel.heightAnchor.constraint(equalToConstant: 200).isActive = true
		noParametersLabel.centerXAnchor.constraint(equalTo: view.centerXAnchor).isActive = true
		noParametersLabel.centerYAnchor.constraint(equalTo: view.centerYAnchor).isActive = true
		
		noParametersLabel.font = Style.Font.bigControl
		noParametersLabel.textColor = Style.Color.light
		noParametersLabel.text = "No Parameters (Yet)"
		noParametersLabel.textAlignment = .center
		noParametersLabel.isHidden = true
		
	}

	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}

	func showEffect(atIndex effectIndex: Int) {

		for view in scrollView.subviews {
			view.removeFromSuperview()
		}
		
		
		if let effect = State.current.mixer.channels.value[effectIndex].effect {
			var lastParameterView: ParameterView? = nil
			var height: CGFloat = 0
			for parameter in effect.parameters.value {
				if let parameterView = makeParameterView(for: parameter) {
				
					scrollView.addSubview(parameterView)
					
					parameterView.widthAnchor.constraint(equalTo: view.widthAnchor, multiplier: 1).isActive = true
										
					if lastParameterView != nil {
						parameterView.topAnchor.constraint(equalTo: lastParameterView!.bottomAnchor, constant: 8).isActive = true
					}
					else {
						parameterView.topAnchor.constraint(equalTo: scrollView.topAnchor).isActive = true
					}
					
					parameterView.leadingAnchor.constraint(equalTo: scrollView.leadingAnchor).isActive = true
					
					height += parameterView.frame.height
					lastParameterView = parameterView

				}
			}
			
			if effect.parameters.value.count == 0 {
				noParametersLabel.isHidden = false
			}
			else {
				noParametersLabel.isHidden = true
			}
			
			scrollView.contentSize.height = height
		}
		
	}
	
	// where should this knowledge live?
	func makeParameterView(for parameter: EffectParameter) -> ParameterView? {
		if let type = parameter.type {
			switch type {
			case .color: return ColorParameterView(parameter: parameter as! ColorParameter)
			case .real: return RealParameterView(parameter: parameter as! RealParameter)
			case .points: return ParameterView(parameter: parameter)
			}
		}
		return nil
	}

}

