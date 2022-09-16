//
// Created by QMS on 30/8/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include "NodeTable.h"

using namespace std;

void NodeTable::insertNode(shared_ptr<AssignNode> n) {
    this->nodeList.push_back(n);
}

vector<shared_ptr<AssignNode>> NodeTable::getAllNodes() {
    vector<shared_ptr<AssignNode>> result;
    for (auto& n: this->nodeList) {
        result.push_back(n);
    }
    return result;
}
