//
//  NonogramSolver.cpp
//  NonogramSolver
//
//  Created by John Zakharov on 07.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

#include "NonogramSolver.hpp"

#include <algorithm>
#include <iosfwd>
#include <ostream>

using std::cout;
using std::endl;

std::ostream& operator<<(std::ostream &os, const decltype(DataModel::Nonogram::vertical)::value_type &line) {
    for(size_t i = 0; i < line.size(); ++i) {
        os << line[i];
        if(i < line.size() - 1) {
            os << ",";
        }
    }
    return os;
}

Services::NonogramSolver::NonogramSolver(const Nonogram &nonogram_):nonogram(nonogram_){
    auto cellsCount = nonogram.vertical.size() * nonogram.horizontal.size();
    field.reserve(cellsCount);
    std::fill(field.begin(),
              field.end(),
              CellValue::Undefined);
}

void Services::NonogramSolver::start() {
    auto nonogramWidth = nonogram.vertical.size();
    auto nonogramHeight = nonogram.horizontal.size();
    for(size_t x = 0; x < nonogram.vertical.size(); ++x) {
        auto &line = nonogram.vertical[x];
        cout << "line = " << line << endl;
    }
}
