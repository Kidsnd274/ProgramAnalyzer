//
// Created by 黄鱼鱼鱼 on 2022/10/17.
//

#ifndef SPA_CONTAINERTABLE_H
#define SPA_CONTAINERTABLE_H
#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "util/ast/TNode.h"

class ContainerTable {
private:
    std::unordered_map<int, std::shared_ptr<TNode>> containerList;
public:
    void insertCondition(int stmtLineNumber, std::shared_ptr<TNode> conditionNode);
    std::shared_ptr<TNode> getConditionByStmtNumber(int stmtNumber);
    std::string getVarName(std::shared_ptr<TNode> conditionPointer);
};


#endif //SPA_CONTAINERTABLE_H
