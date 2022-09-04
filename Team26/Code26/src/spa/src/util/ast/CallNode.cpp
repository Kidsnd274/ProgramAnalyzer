#include "CallNode.h"

std::string CallNode::getProcedureName() {
    return procedureName;
}

std::shared_ptr<CallNode> CallNode::createCallNode(int statementNumber, std::string procedureName) {
    return std::make_shared<CallNode>(statementNumber, procedureName);
}
