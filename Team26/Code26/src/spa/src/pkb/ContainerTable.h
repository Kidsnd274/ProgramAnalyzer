#ifndef SPA_CONTAINERTABLE_H
#define SPA_CONTAINERTABLE_H

#include <vector>
#include <unordered_map>
#include <string>
#include "util/ast/TNode.h"

class ContainerTable {
private:
    std::unordered_map<int, std::vector<std::string>> condVars;

public:
    std::vector<std::string> getVarNames(int stmtNumber);
    void addCondVar(int stmtNumber, std::string varName);
    void clear();
};


#endif  // SPA_CONTAINERTABLE_H
