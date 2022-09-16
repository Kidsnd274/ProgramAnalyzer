//
// Created by 黄鱼鱼鱼 on 2022/9/15.
//

#ifndef SPA_NODETABLE_H
#define SPA_NODETABLE_H
#include "../util/ast/AssignNode.h"
using namespace std;
class NodeTable {
private:
    vector<shared_ptr<AssignNode>> nodeList;

public:
    void insertNode(shared_ptr<AssignNode> n);
    vector<shared_ptr<AssignNode>> getAllNodes();
};


#endif //SPA_NODETABLE_H
