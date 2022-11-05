//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_CALLTABLE_H
#define SPA_CALLTABLE_H

#include <stdio.h>
#include <string>
#include <unordered_set>
#include <unordered_map>

class CallTable {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> callList;
public:
    void insertCall(std::string procedureName, std::string procedureCalled);
    bool existCall(std::string procedureName, std::string procedureCalled);
    std::unordered_set<std::string> getProcsCalled(std::string procedureName);
    std::unordered_map<std::string, std::unordered_set<std::string>> getAllCalls();
    void clear();
};

#endif //SPA_CALLTABLE_H
