#include "CallTable.h"

// S1 (Major): DRY - Code structure and methods are similar to CallStaTable

void CallTable::insertCall(std::string procedureName, std::string procedureCalled) {
    if (this->callList.find(procedureName) != this->callList.end()) {
        this->callList.find(procedureName)->second.push_back(procedureCalled);
    } else {
        std::pair<std::string, std::vector<std::string>> call(procedureName, {procedureCalled});
        this->callList.insert(call);
    }
}

bool CallTable::existCall(std::string procedureName, std::string procedureCalled) {
    std::unordered_map<std::string, std::vector<std::string>> list = this->callList;
    if (list.find(procedureName) != list.end() &&
         std::find(list[procedureName].begin(), list[procedureName].end(), procedureCalled)
         != list[procedureName].end()) {
        return true;
    }
    return false;
}

std::vector<std::string> CallTable::getProcsCalled(std::string procedureName) {
    return this->callList[procedureName];
}

std::unordered_map<std::string, std::vector<std::string>> CallTable::getAllCalls() {
    return this->callList;
}

void CallTable::clear() {
    this->callList.clear();
}
