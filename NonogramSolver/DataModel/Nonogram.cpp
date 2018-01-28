//
//  Nonogram.cpp
//  NonogramSolver
//
//  Created by John Zakharov on 05.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

#include "Nonogram.hpp"

#include <algorithm>

namespace Keys {
    const std::string vertical = "vertical";
    const std::string horizontal = "horizontal";
}

void DataModel::from_json(const json &j, Nonogram &o) {
    using namespace Keys;
    o.vertical = j[vertical].get<decltype(o.vertical)>();
    o.horizontal = j[horizontal].get<decltype(o.horizontal)>();
}

void DataModel::to_json(json &j, const Nonogram &o) {
    using namespace Keys;
    j = {
        { vertical, o.vertical },
        { horizontal, o.horizontal },
    };
}

int DataModel::Nonogram::verticalNumbersCount() const {
    auto res = 0;
    for(auto &numbers : vertical) {
        res += std::accumulate(numbers.begin(), numbers.end(), 0);
    }
    return res;
}

int DataModel::Nonogram::horizontalNumbersCount() const {
    auto res = 0;
    for(auto &numbers : horizontal) {
        res += std::accumulate(numbers.begin(), numbers.end(), 0);
    }
    return res;
}
