//
// Created by QMS on 3/10/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "CallStarTable.h"

using namespace std;

void CallStarTable::insertCallStar(std::string procedureName, std::string procedureCalled) {
    if (this->callStarList.find(procedureName) != this->callStarList.end()) {
        this->callStarList.find(procedureName)->second.insert(procedureCalled);
    } else {
        std::pair<std::string,std::unordered_set<std::string>> callStar (procedureName, {procedureCalled});
        this->callStarList.insert(callStar);
    }
}

bool CallStarTable::existCallStar(std::string procedureName, std::string procedureCalled) {
    unordered_map<std::string ,std::unordered_set<std::string>> list = this->callStarList;
    if (list.find(procedureName) != list.end() &&
         list[procedureName].find(procedureCalled) != list[procedureName].end()) {
        return true;
    }
    return false;
}

std::unordered_set<std::string> CallStarTable::getProcsStarCalled(std::string procedureName) {
    return this->callStarList[procedureName];
}

std::unordered_map<std::string, std::unordered_set<std::string>> CallStarTable::getAllCallStars() {
    return this->callStarList;
}

void CallStarTable::clear() {
    this->callStarList.clear();
}
