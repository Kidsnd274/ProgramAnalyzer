//
// Created by QMS on 3/10/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "CallStarTable.h"

using namespace std;

void CallStarTable::insertCallStar(std::string procedureName, std::string procedureCalled) {
    if (this->callStarList.find(procedureName) != this->callStarList.end()) {
        this->callStarList.find(procedureName)->second.push_back(procedureCalled);
    } else {
        std::pair<std::string,std::vector<std::string>> callStar (procedureName, {procedureCalled});
        this->callStarList.insert(callStar);
    }
}

bool CallStarTable::existCallStar(std::string procedureName, std::string procedureCalled) {
    unordered_map<std::string ,std::vector<std::string>> list = this->callStarList;
    if (list.find(procedureName) != list.end() &&
         std::find(list[procedureName].begin(), list[procedureName].end(), procedureCalled)
         != list[procedureName].end()) {
        return true;
    }
    return false;
}

std::vector<std::string> CallStarTable::getProcsStarCalled(std::string procedureName) {
    return this->callStarList[procedureName];
}

std::unordered_map<std::string, std::vector<std::string>> CallStarTable::getAllCallStars() {
    return this->callStarList;
}

void CallStarTable::clear() {
    this->callStarList.clear();
}
