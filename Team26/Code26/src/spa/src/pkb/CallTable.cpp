//
// Created by QMS on 3/10/2022.
//
#include <stdio.h>
#include <string>
#include <unordered_set>
#include <algorithm>
#include "CallTable.h"

using namespace std;

void CallTable::insertCall(std::string procedureName, std::string procedureCalled) {
    if (this->callList.find(procedureName) != this->callList.end()) {
        this->callList.find(procedureName)->second.insert(procedureCalled);
    } else {
        std::pair<std::string,std::unordered_set<std::string>> call (procedureName, {procedureCalled});
        this->callList.insert(call);
    }
}

bool CallTable::existCall(std::string procedureName, std::string procedureCalled) {
    unordered_map<std::string ,std::unordered_set<std::string>> list = this->callList;
    if (list.find(procedureName) != list.end() &&
         list[procedureName].find(procedureCalled) != list[procedureName].end()) {
        return true;
    }
    return false;
}

std::unordered_set<std::string> CallTable::getProcsCalled(std::string procedureName) {
    return this->callList[procedureName];
}

std::unordered_map<std::string, std::unordered_set<std::string>> CallTable::getAllCalls() {
    return this->callList;
}

void CallTable::clear() {
    this->callList.clear();
}
