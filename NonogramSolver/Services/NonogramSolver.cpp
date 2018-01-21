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

using std::cout;
using std::endl;

//using CellValue = Services::NonogramSolver::CellValue;

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

void Services::NonogramSolver::start() {
    auto nonogramWidth = nonogram.vertical.size();
    auto nonogramHeight = nonogram.horizontal.size();
    for(size_t x = 0; x < nonogram.vertical.size(); ++x) {
        auto &line = nonogram.vertical[x];
        cout << "line = " << line << endl;
    }
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
                    for(auto j = 0; j < groupLength; ++j) {
                        if(*(startIt + j) != '0') {
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
                            newResLine.push_back('2');
                        }
                        for(auto j = 0; j < groupLength; ++j) {
                            newResLine.push_back('1');
                        }
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
                                    res.push_back(std::move(resLine));
                                }
                            }else{
                                if(newResLine.size() == lineLength){
                                    res.push_back(std::move(newResLine));
                                }
                            }
                        }else{
                            res.push_back(std::move(newResLine));
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
            newResLine.push_back('2');
        }
        res.push_back(std::move(newResLine));
    }
    /*auto groupLength = numbers.front();
    auto x = 0;
    while(x + groupLength <= line.size()){
        std::string newResLine;
        newResLine.reserve(line.size());
        auto groupCanBePlacedAtX = true;
        for(auto i = 0; i < x; ++i) {
            newResLine.push_back('0');
        }
        auto cellBeforeGroupIsEmpty = true;
        auto beforeStartX = x - 1;
        if(beforeStartX >= 0) {
            cellBeforeGroupIsEmpty = line[beforeStartX] != '1';
        }
        if(cellBeforeGroupIsEmpty){
            for(auto i = 0; i < groupLength; ++i) {
                auto targetIndex = x + i;
                newResLine.push_back('1');
                groupCanBePlacedAtX = line[targetIndex] != '2';
                if(!groupCanBePlacedAtX){
                    break;
                }
            }
            auto cellAfterGroupIsEmpty = true;
            auto afterGroupX = x + groupLength;
            if(afterGroupX < line.size()) {
                cellAfterGroupIsEmpty = line[afterGroupX] != '1';
            }
            if(cellAfterGroupIsEmpty) {
                if(groupCanBePlacedAtX){
                    while(newResLine.size() < line.size()) {
                        auto lineValue = line[newResLine.size()];
                        if(lineValue == '1'){
                            newResLine.push_back(lineValue);
                        }else{
                            newResLine.push_back('2');
                        }
                    }
                    auto realNumbers = countNumbers(newResLine);
                    if(realNumbers == numbers){
                        res.push_back(std::move(newResLine));
                    }else{
                        
                    }
                }
            }
        }
        ++x;
    }*/
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
    /*for(auto i = 0; i < res.size(); ++i) {
        if(res[i] == CellValue::Undefined) {
            res[i] = CellValue::Empty;
        }
    }*/
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
