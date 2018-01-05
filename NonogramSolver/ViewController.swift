//
//  ViewController.swift
//  NonogramSolver
//
//  Created by John Zakharov on 05.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {
    let nonogramView = NonogramView(frame: .zero)
    let nonogramModelView = NonogramModelView()!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        if let trainPath = Bundle.main.path(forResource: "train", ofType: "json") {
            self.nonogramModelView.loadNonogram(fromFile: trainPath)
        }

        nonogramView.frame = self.view.bounds
        nonogramView.wantsLayer = true
        nonogramView.layer?.backgroundColor = CGColor.black
        nonogramView.autoresizingMask = [.width, .height]
        nonogramView.drawCallback = { (rect: NSRect) -> () in
            self.nonogramModelView.draw(rect)
        }
        self.view.addSubview(nonogramView)
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }

    /*override func awakeFromNib() {
        if self.view.layer != nil {
            let color = CGColor(red: 1.0, green: 1, blue: 1, alpha: 1.0)
            self.view.layer?.backgroundColor = color
        }
        
    }*/

}

