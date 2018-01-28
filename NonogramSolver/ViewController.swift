//
//  ViewController.swift
//  NonogramSolver
//
//  Created by John Zakharov on 05.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

import Cocoa

class ViewController: NSViewController, NonogramModelViewDelegate {
    let nonogramView = NonogramView(frame: .zero)
    let nonogramModelView = NonogramModelView()!
    let solveBtn = NSButton()
    
//    let defaultNonogramName = "train"
//    let defaultNonogramName = "horse"
//    let defaultNonogramName = "camel"
//    let defaultNonogramName = "moon"
    let defaultNonogramName = "rabbit"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        var s = CGSize()
        var o = CGPoint()
        let b = self.view.frame.size
        
        if let trainPath = Bundle.main.path(forResource: self.defaultNonogramName, ofType: "json") {
            self.nonogramModelView.loadNonogram(fromFile: trainPath)
        }
        nonogramModelView.delegate = self

        nonogramView.frame = self.view.bounds
        nonogramView.wantsLayer = true
        nonogramView.layer?.backgroundColor = CGColor.black
        nonogramView.autoresizingMask = [.width, .height]
        nonogramView.drawCallback = { (rect: NSRect) -> () in
            self.nonogramModelView.draw(rect)
        }
        self.view.addSubview(nonogramView)
        
        solveBtn.title = "Solve"
        solveBtn.target = self
        solveBtn.action = #selector(solveBtnTouched(sender:))
        solveBtn.bezelStyle = .rounded
        s = CGSize(width: 100, height: 30)
        o = CGPoint(x: 10, y: b.height - s.height - 10)
        solveBtn.frame = CGRect(origin: o, size: s)
        solveBtn.autoresizingMask = [.maxXMargin, .minYMargin]
        self.view.addSubview(solveBtn)
    }

    //  MARK: - Events
    
    @objc func solveBtnTouched(sender: AnyObject) {
        if !self.nonogramModelView.isSolvingNonogram {
            self.solveBtn.isEnabled = false
            self.nonogramModelView.startSolvingNonogram()
        }
    }
    
    //  MARK: - NonogramModelViewDelegate
    
    func nonogramModelViewDidUpdateNonogramSolution(_ sender: NonogramModelView!) {
        self.nonogramView.needsDisplay = true
    }
    
    func nonogramModelViewDidFinishNonogramSolving(_ sender: NonogramModelView!) {
        print("Done!")
        self.solveBtn.isEnabled = true
    }

}

