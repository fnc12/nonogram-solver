//
//  Nonogram.hpp
//  NonogramSolver
//
//  Created by John Zakharov on 05.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

#ifndef Nonogram_hpp
#define Nonogram_hpp

#include <stdio.h>
#include <vector>
#include <json/json.hpp>

namespace DataModel {
    
    struct Nonogram {
        std::vector<std::vector<int>> vertical; //  columns
        std::vector<std::vector<int>> horizontal;   //  rows
        
        int verticalNumbersCount() const;
        int horizontalNumbersCount() const;
    };
    
    using nlohmann::json;
    
    void from_json(const json &j, Nonogram &o);
    
    void to_json(json &j, const Nonogram &o);
}

#endif /* Nonogram_hpp */
