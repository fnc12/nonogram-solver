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
#include <set>
#include <thread>
#include <chrono>

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
              '0');
}

void Services::NonogramSolver::start(std::function<void(std::string)> progressCallback, std::function<void()> doneCallback) {
    struct UndefinedDetector {
        bool operator()(char c){
            return c == '0';
        }
    };
    assert(nonogram.verticalNumbersCount() == nonogram.horizontalNumbersCount());
    auto nonogramWidth = nonogram.vertical.size();
    auto nonogramHeight = nonogram.horizontal.size();
    field.clear();
    auto fieldSize = nonogramWidth * nonogramHeight;
    field.reserve(fieldSize);
    for(size_t i = 0; i < fieldSize; ++i) {
        field.push_back('0');
    }
    auto weAreStuck = false;
    auto undefinedCells = std::count_if(field.begin(),
                                        field.end(),
                                        UndefinedDetector());
    while(undefinedCells > 0 and !weAreStuck) {
        for(size_t x = 0; x < nonogramWidth; ++x) {
            auto &numbers = nonogram.vertical[x];
            auto line = verticalLineAt(x);
            auto undefinedCellsBefore = std::count_if(line.begin(),
                                                      line.end(),
                                                      UndefinedDetector());
            auto options = evaluateOptions(line.begin(),
                                           line.end(),
                                           numbers);
            auto clean = evaluateClean(options);
            auto undefinedCellsAfter = std::count_if(clean.begin(),
                                                     clean.end(),
                                                     UndefinedDetector());
            if(undefinedCellsAfter < undefinedCellsBefore) {
                setVerticalLineAt(x, clean);
            }else{
//                cout << "we are stuck" << endl;
            }
        }
        for(size_t y = 0; y < nonogramHeight; ++y) {
            auto &numbers = nonogram.horizontal[y];
            auto line = horizontalLineAt(y);
            auto undefinedCellsBefore = std::count_if(line.begin(),
                                                      line.end(),
                                                      UndefinedDetector());
            auto options = evaluateOptions(line.begin(),
                                           line.end(),
                                           numbers);
            auto clean = evaluateClean(options);
            auto undefinedCellsAfter = std::count_if(clean.begin(),
                                                     clean.end(),
                                                     UndefinedDetector());
            if(undefinedCellsAfter < undefinedCellsBefore) {
                setHorizontalLineAt(y, clean);
            }else{
//                cout << "we are stuck" << endl;
            }
        }
        progressCallback(field);
        auto newUndefinedCells = std::count_if(field.begin(),
                                               field.end(),
                                               UndefinedDetector());
        if(newUndefinedCells == undefinedCells) {
            cout << "we are stuck, unable to solve" << endl;
            break;
        }
        undefinedCells = newUndefinedCells;
//        using namespace std::chrono_literals;
//        std::this_thread::sleep_for(1s);
    }
    doneCallback();
}

void Services::NonogramSolver::setVerticalLineAt(size_t index, const std::string &line) {
    assert(std::find(field.begin(), field.end(), '\0') == field.end());
    auto nonogramHeight = nonogram.horizontal.size();
    std::copy(line.begin(),
              line.end(),
              field.begin() + index * nonogramHeight);
    assert(std::find(field.begin(), field.end(), '\0') == field.end());
}

void Services::NonogramSolver::setHorizontalLineAt(size_t index, const std::string &line) {
    assert(std::find(line.begin(), line.end(), '\0') == line.end());
    assert(std::find(field.begin(), field.end(), '\0') == field.end());
    auto nonogramWidth = nonogram.vertical.size();
    auto nonogramHeight = nonogram.horizontal.size();
    assert(line.length() == nonogramWidth);
    for(size_t i = 0; i < nonogramWidth; ++i) {
        field[i * nonogramHeight + index] = line[i];
    }
    assert(std::find(field.begin(), field.end(), '\0') == field.end());
}

std::string Services::NonogramSolver::verticalLineAt(size_t index) const {
    auto nonogramHeight = nonogram.horizontal.size();
    return field.substr(index * nonogramHeight, nonogramHeight);
}

std::string Services::NonogramSolver::horizontalLineAt(size_t index) const {
    auto nonogramWidth = nonogram.vertical.size();
    auto nonogramHeight = nonogram.horizontal.size();
    std::string res;
    res.reserve(nonogramWidth);
    for(size_t i = 0; i < nonogramWidth; ++i) {
        res.push_back(field[nonogramHeight * i + index]);
    }
    return res;
}

std::vector<std::string> Services::NonogramSolver::evaluateOptions(std::string::iterator from,
                                                                   std::string::iterator to,
                                                                   std::vector<int> numbers) const
{
    std::vector<std::string> res;
    auto lineLength = to - from;
    if(numbers.size()){
        if(lineLength > 0){
            auto groupLength = numbers.front();
            if(groupLength <= lineLength){
                auto availableCombinationsCount = lineLength - groupLength + 1;
                for(auto i = 0; i < availableCombinationsCount; ++i) {
                    auto startIt = from + i;
                    auto groupCanFit = true;
                    if(from < startIt) {
                        auto cellBeforeStartIt = startIt - 1;
                        groupCanFit = *cellBeforeStartIt != '1';
                    }
                    if(groupCanFit){
                        for(auto j = 0; j < groupLength; ++j) {
                            if(*(startIt + j) == '2'){
                                groupCanFit = false;
                            }
                        }
                        auto afterGroupIt = startIt + groupLength;
                        if(afterGroupIt < to) {
                            if(*afterGroupIt == '1'){
                                groupCanFit = false;
                            }
                        }
                        if(groupCanFit){
                            std::string newResLine;
                            newResLine.reserve(lineLength);
                            for(auto j = 0; j < i; ++j) {
                                auto currentCellValue = *(from + j);
                                switch(currentCellValue){
                                    case '0':
                                    case '2':
                                        newResLine.push_back('2');
                                        break;
                                    case '1':
                                        newResLine.push_back('1');
                                        break;
                                    default:
                                        assert(0);
                                        break;
                                }
                            }
                            for(auto j = 0; j < groupLength; ++j) {
                                newResLine.push_back('1');
                            }
                            auto validateNumberOfNewLine = [](const std::string &line, int correct1CellsCount) -> bool {
                                auto line1CellsCount = 0;
                                for(auto &c : line) {
                                    if(c == '1') {
                                        ++line1CellsCount;
                                    }
                                }
                                return line1CellsCount == correct1CellsCount;
                            };
                            auto correct1CellsCount = std::accumulate(numbers.begin(),
                                                                      numbers.end(),
                                                                      0);
                            if(afterGroupIt < to){
                                newResLine.push_back('2');
                                decltype(numbers) numbersTail;
                                numbersTail.reserve(numbers.size() - 1);
                                std::copy(numbers.begin() + 1,
                                          numbers.end(),
                                          std::back_inserter(numbersTail));
                                auto subFrom = afterGroupIt + 1;
                                auto subLineLength = to - subFrom;
                                if(subLineLength == 0 and !numbersTail.empty()){
                                    return res;
                                }
                                auto subOptions = this->evaluateOptions(subFrom, to, numbersTail);
                                if(subOptions.size()){
                                    for(auto &subOption : subOptions) {
                                        auto resLine = newResLine + subOption;
                                        if(validateNumberOfNewLine(resLine, correct1CellsCount)){
                                            res.push_back(std::move(resLine));
                                        }
                                    }
                                }else{
                                    if(newResLine.size() == lineLength){
                                        if(validateNumberOfNewLine(newResLine, correct1CellsCount)){
                                            res.push_back(std::move(newResLine));
                                        }
                                    }
                                }
                            }else{
                                if(validateNumberOfNewLine(newResLine, correct1CellsCount)){
                                    res.push_back(std::move(newResLine));
                                }
                            }
                        }
                    }
                }
            }else{
                /*std::string emptyResult;
                emptyResult.reserve(lineLength);
                for(auto it = from; it != to; ++it) {
                    emptyResult.push_back('2');
                }
                res.push_back(std::move(emptyResult));*/
            }
        }
    }else{
        std::string newResLine;
        newResLine.reserve(lineLength);
        for(auto i = 0; i < lineLength; ++i) {
            auto currentCellValue = *(from + i);
            switch(currentCellValue){
                case '0':
                case '2':
                    newResLine.push_back('2');
                    break;
                case '1':
                    newResLine.push_back('1');
                    break;
                default:
                    assert(0);
                    break;
            }
        }
        res.push_back(std::move(newResLine));
    }
    return res;
}

std::string Services::NonogramSolver::evaluateClean(const std::vector<std::string> &options) const {
    std::string res;
    if(options.size()) {
        res.reserve(options.front().size());
        for(auto i = 0; i < options.front().size(); ++i) {
            auto cellValue = '0';
            std::set<char> values;
            for(auto &option : options) {
                values.insert(option[i]);
            }
            if(values.size() == 1) {
                cellValue = *values.begin();
            }
            res.push_back(cellValue);
        }
    }
    return res;
}

std::vector<int> Services::NonogramSolver::countNumbers(const std::string &line) const {
    std::vector<int> res;
    auto groupLength = 0;
    for(auto cellValue : line) {
        if(cellValue == '1') {
            ++groupLength;
        }else{
            if(groupLength){
                res.push_back(groupLength);
                groupLength = 0;
            }
        }
    }
    if(groupLength){
        res.push_back(groupLength);
        groupLength = 0;
    }
    return res;
}
