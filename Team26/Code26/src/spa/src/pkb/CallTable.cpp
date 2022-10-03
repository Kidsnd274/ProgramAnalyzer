//
// Created by QMS on 3/10/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "CallTable.h"

using namespace std;

void CallTable::insertCall(std::string procedureName, std::string procedureCalled) {
    if (this->callList.find(procedureName) != this->callList.end()) {
        this->callList.find(procedureName)->second.push_back(procedureCalled);
    } else {
        std::pair<std::string,std::vector<std::string>> call (procedureName, {procedureCalled});
        this->callList.insert(call);
    }
}

bool CallTable::existCall(std::string procedureName, std::string procedureCalled) {
    unordered_map<std::string ,std::vector<std::string>> list = this->callList;
    if (list.find(procedureName) != list.end() &&
         std::find(list[procedureName].begin(), list[procedureName].end(), procedureCalled)
         != list[procedureName].end()) {
        return true;
    }
    return false;
}
