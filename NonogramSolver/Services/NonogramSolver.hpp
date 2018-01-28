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
#include <functional>

namespace Services {
    
    using DataModel::Nonogram;
    
    struct NonogramSolver {
        
        NonogramSolver(const Nonogram &nonogram);
        
        void start(std::function<void(std::string)> progressCallback, std::function<void()> doneCallback);
        
        std::vector<std::string> evaluateOptions(std::string::iterator from,
                                                 std::string::iterator to,
                                                 std::vector<int> numbers) const;
        
        std::string evaluateClean(const std::vector<std::string> &options) const;
        
        std::vector<int> countNumbers(const std::string &line) const;
        
        std::string verticalLineAt(size_t index) const;
        
        std::string horizontalLineAt(size_t index) const;
        
        void setVerticalLineAt(size_t index, const std::string &line);
        
        void setHorizontalLineAt(size_t index, const std::string &line);
        
    protected:
        
        const Nonogram &nonogram;
        std::string field;
    };
}

#endif /* NonogramSolver_hpp */
