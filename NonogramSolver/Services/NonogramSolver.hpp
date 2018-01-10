//
//  NonogramSolver.hpp
//  NonogramSolver
//
//  Created by John Zakharov on 07.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

#ifndef NonogramSolver_hpp
#define NonogramSolver_hpp

#include "DataModel/Nonogram.hpp"

#include <vector>

namespace Services {
    
    using DataModel::Nonogram;
    
    struct NonogramSolver {
        
        NonogramSolver(const Nonogram &nonogram);
        
        void start();
        
    protected:
        enum class CellValue {
            Filled,
            Empty,
            Undefined,
        };
        
        const Nonogram &nonogram;
        std::vector<CellValue> field;
    };
}

#endif /* NonogramSolver_hpp */
