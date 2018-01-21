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
#include <string>

namespace Services {
    
    using DataModel::Nonogram;
    
    struct NonogramSolver {
        
        /*enum class CellValue {
            Filled,
            Empty,
            Undefined,
        };*/
        
        NonogramSolver(const Nonogram &nonogram);
        
        void start();
        
        std::vector<std::string> evaluateOptions(std::string::iterator from,
                                                 std::string::iterator to,
                                                 std::vector<int> numbers) const;
        
        std::string evaluateClean(const std::vector<std::string> &options) const;
        
        std::vector<int> countNumbers(const std::string &line) const;
        
    protected:
        
        const Nonogram &nonogram;
        std::string field;
    };
}

#endif /* NonogramSolver_hpp */
