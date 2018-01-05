//
//  NonogramView.swift
//  NonogramSolver
//
//  Created by John Zakharov on 05.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

import Cocoa

class NonogramView: NSView {
    
    var drawCallback: ((_ rect: NSRect) -> ())?
    
    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
    }
    
    required init?(coder decoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func draw(_ dirtyRect: NSRect) {
        super.draw(dirtyRect)
        if let c = self.drawCallback{
            c(dirtyRect)
        }
    }
    
}
