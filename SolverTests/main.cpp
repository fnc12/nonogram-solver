//
//  main.cpp
//  SolverTests
//
//  Created by John Zakharov on 10.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

#include "Services/NonogramSolver.hpp"
#include "DataModel/Nonogram.hpp"

using namespace Services;
//using CellValue = NonogramSolver::CellValue;

/*CellValue operator""_f(unsigned long long value) {
    switch(value){
        case 0: return CellValue::Empty;
        case 1: return CellValue::Filled;
        default: return CellValue::Undefined;
    }
}*/

int main(int argc, const char * argv[]) {
    
    Nonogram nonogram;
    
    NonogramSolver solver(nonogram);
    
    auto createUndefinedLine = [](int length) {
        std::string res;
        res.reserve(length);
        for(auto i = 0; i < length; ++i) {
            res.push_back('0');
        }
        return res;
    };
    
    {   //  line 2:[1]
        auto line = createUndefinedLine(2);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {1});
        assert(options.size() == 2);
        assert(std::find(options.begin(),
                         options.end(),
                         "21") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "12") != options.end());
        
        options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "11") != options.end());
    }
    {   //  line 3:[1]
        auto line = createUndefinedLine(3);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {1});
        assert(options.size() == 3);
        assert(std::find(options.begin(),
                         options.end(),
                         "122") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "212") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "221") != options.end());
    }
    {
        //  line 3:[2]
        auto line = createUndefinedLine(3);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 2);
        assert(std::find(options.begin(),
                         options.end(),
                         "112") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "211") != options.end());
    }
    {
        //  line 4:[2]
        auto line = createUndefinedLine(4);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 3);
        assert(std::find(options.begin(),
                         options.end(),
                         "1122") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "2112") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "2211") != options.end());
    }
    {
        //  line 3:[1, 1]
        auto line = createUndefinedLine(3);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {1, 1});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "121") != options.end());
    }
    {
        //  line 4:[1, 1]
        auto line = createUndefinedLine(4);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {1, 1});
        assert(options.size() == 3);
        assert(std::find(options.begin(),
                         options.end(),
                         "1212") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "1221") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "2121") != options.end());
    }
    {
        //  line 4:[1, 2]
        auto line = createUndefinedLine(4);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {1, 2});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "1211") != options.end());
    }
    {
        //  line 4:[2, 1]
        auto line = createUndefinedLine(4);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2, 1});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "1121") != options.end());
    }
    {
        //  line 4:[3]
        auto line = createUndefinedLine(4);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {3});
        assert(options.size() == 2);
        assert(std::find(options.begin(),
                         options.end(),
                         "1112") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "2111") != options.end());
    }
    
    /*{   // test [1 * 10] in [0 * 12]
        auto options = solver.evaluateOptions(createUndefinedLine(12), {10});
        assert(options.size() == 3);
        assert(std::find(options.begin(),
                         options.end(),
                         "111111111100") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "011111111110") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "001111111111") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "111111111111") == options.end());
        
        //  test evaluate clean
        auto cleanLine = solver.evaluateClean(options);
        decltype(cleanLine) expectedCleanLine = "221111111122";
        assert(std::equal(expectedCleanLine.begin(),
                          expectedCleanLine.end(),
                          cleanLine.begin(),
                          cleanLine.end()));
    }
    {   // test [1 * 9] in [0 * 12]
        auto options = solver.evaluateOptions(createUndefinedLine(12), {9});
        assert(options.size() == 4);
        assert(std::find(options.begin(),
                         options.end(),
                         "111111111000") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "011111111100") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "001111111110") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "000111111111") != options.end());
        
        //  test evaluate clean
        auto cleanLine = solver.evaluateClean(options);
        decltype(cleanLine) expectedCleanLine = "222111111222";
        assert(std::equal(expectedCleanLine.begin(),
                          expectedCleanLine.end(),
                          cleanLine.begin(),
                          cleanLine.end()));
    }
    {   //  test [1 * 8] in [0[10]_1_0]
        auto options = solver.evaluateOptions("222222222212", {8});
        assert(options.size() == 2);
        assert(std::find(options.begin(),
                         options.end(),
                         "000011111111") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "000111111110") != options.end());
        
        //  test evaluate clean
        auto cleanLine = solver.evaluateClean(options);
        decltype(cleanLine) expectedCleanLine = "222211111112";
        assert(std::equal(expectedCleanLine.begin(),
                          expectedCleanLine.end(),
                          cleanLine.begin(),
                          cleanLine.end()));
    }*/
    
    return 0;
}
