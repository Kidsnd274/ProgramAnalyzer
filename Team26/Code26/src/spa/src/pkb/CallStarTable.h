//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_CALLSTARTABLE_H
#define SPA_CALLSTARTABLE_H

#include <stdio.h>
#include <string>
#include <unordered_set>
#include <unordered_map>

class CallStarTable {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> callStarList;
public:
    void insertCallStar(std::string procedureName, std::string procedureCalled);
    bool existCallStar(std::string procedureName, std::string procedureCalled);
    std::unordered_set<std::string> getProcsStarCalled(std::string procedureName);
    std::unordered_map<std::string, std::unordered_set<std::string>> getAllCallStars();
    void clear();
};

#endif //SPA_CALLSTARTABLE_H
