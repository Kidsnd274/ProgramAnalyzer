#ifndef SPA_CONTAINERTABLE_H
#define SPA_CONTAINERTABLE_H
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "util/ast/TNode.h"

class ContainerTable {
private:
    std::unordered_map<int, std::unordered_set<std::string>> condVars;
public:
    std::unordered_set<std::string> getVarNames(int stmtNumber);
    void addCondVar(int stmtNumber, std::string varName);
    void clear();
};


#endif  // SPA_CONTAINERTABLE_H
