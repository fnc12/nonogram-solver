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
    {
        //  line [1, 0, 0, 0] : [2]
        auto line = createUndefinedLine(4);
        line[0] = '1';
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "1122") != options.end());
    }
    {
        //  line [0, 1, 0, 0] : [2]
        auto line = createUndefinedLine(4);
        line[1] = '1';
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 2);
        assert(std::find(options.begin(),
                         options.end(),
                         "1122") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "2112") != options.end());
    }
    {
        //  line [0, 0, 1, 0] : [2]
        auto line = createUndefinedLine(4);
        line[2] = '1';
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 2);
        assert(std::find(options.begin(),
                         options.end(),
                         "2112") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "2211") != options.end());
    }
    {
        //  line [0, 0, 0, 1] : [2]
        auto line = createUndefinedLine(4);
        line[3] = '1';
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "2211") != options.end());
    }
    {
        //  line [1, 1, 0, 0] : [2]
        auto line = createUndefinedLine(4);
        line[0] = '1';
        line[1] = '1';
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "1122") != options.end());
    }
    {
        //  line [0, 1, 1, 0] : [2]
        auto line = createUndefinedLine(4);
        line[1] = '1';
        line[2] = '1';
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "2112") != options.end());
    }
    {
        //  line [0, 0, 1, 1] : [2]
        auto line = createUndefinedLine(4);
        line[2] = '1';
        line[3] = '1';
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "2211") != options.end());
    }
    {
        //  line 5 : [4]
        auto line = createUndefinedLine(5);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {4});
        assert(options.size() == 2);
        assert(std::find(options.begin(),
                         options.end(),
                         "11112") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "21111") != options.end());
        auto clean = solver.evaluateClean(options);
        assert(clean == "01110");
    }
    {
        //  line 5 : [2]
        auto line = createUndefinedLine(5);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 4);
        auto clean = solver.evaluateClean(options);
        assert(clean == "00000");
    }
    {
        //  line 5 : [3]
        auto line = createUndefinedLine(5);
        auto options = solver.evaluateOptions(line.begin(), line.end(), {3});
        assert(options.size() == 3);
        auto clean = solver.evaluateClean(options);
        assert(clean == "00100");
    }
    {
        //  line [1, 0, 0, 0, 0] : [2, 1]
        std::string line = "10000";
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2, 1});
        assert(options.size() == 2);
        assert(std::find(options.begin(),
                         options.end(),
                         "11212") != options.end());
        assert(std::find(options.begin(),
                         options.end(),
                         "11221") != options.end());
        auto clean = solver.evaluateClean(options);
        assert(clean == "11200");
    }
    {
        std::string line = "10110";
        auto options = solver.evaluateOptions(line.begin(), line.end(), {4});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "11112") != options.end());
        auto clean = solver.evaluateClean(options);
        assert(clean == "11112");
    }
    {
        std::string line = "10000";
        auto options = solver.evaluateOptions(line.begin(), line.end(), {1, 1});
        assert(options.size() == 3);
        auto clean = solver.evaluateClean(options);
        assert(clean == "12000");
    }
    {
        std::string line = "01120";
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "21122") != options.end());
        auto clean = solver.evaluateClean(options);
        assert(clean == "21122");
    }
    {
        std::string line = "02100";
        auto options = solver.evaluateOptions(line.begin(), line.end(), {3});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "22111") != options.end());
        auto clean = solver.evaluateClean(options);
        assert(clean == "22111");
    }
    {
        std::string line = "12100";
        auto options = solver.evaluateOptions(line.begin(), line.end(), {1, 1});
        assert(options.size() == 1);
        assert(std::find(options.begin(),
                         options.end(),
                         "12122") != options.end());
        auto clean = solver.evaluateClean(options);
        assert(clean == "12122");
    }
    {
        std::string line = "022000";
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 2);
        auto clean = solver.evaluateClean(options);
        assert(clean == "222010");
    }
    {
        std::string line = "02200";
        auto options = solver.evaluateOptions(line.begin(), line.end(), {2});
        assert(options.size() == 1);
        auto clean = solver.evaluateClean(options);
        assert(clean == "22211");
    }
    {
        std::string line = "10000";
        auto options = solver.evaluateOptions(line.begin(), line.end(), {1});
        assert(options.size() == 1);
        auto clean = solver.evaluateClean(options);
        assert(clean == "12222");
    }
    {
        std::string line = "21110";
        auto options = solver.evaluateOptions(line.begin(), line.end(), {4});
        assert(options.size() == 1);
        auto clean = solver.evaluateClean(options);
        assert(clean == "21111");
    }
    
    return 0;
}
