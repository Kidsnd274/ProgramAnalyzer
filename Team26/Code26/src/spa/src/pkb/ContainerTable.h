//
// Created by 黄鱼鱼鱼 on 2022/10/17.
//

#ifndef SPA_CONTAINERTABLE_H
#define SPA_CONTAINERTABLE_H
#include <stdio.h>
#include <string>
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


#endif //SPA_CONTAINERTABLE_H
