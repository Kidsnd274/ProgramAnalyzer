//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_CALLTABLE_H
#define SPA_CALLTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

class CallTable {
private:
    std::unordered_map<std::string, std::vector<std::string>> callList;
public:
    void insertCall(std::string procedureName, std::string procedureCalled);
    bool existCall(std::string procedureName, std::string procedureCalled);
    std::vector<std::string> getProcsCalled(std::string procedureName);
    std::unordered_map<std::string, std::vector<std::string>> getAllCalls();
};

#endif //SPA_CALLTABLE_H
