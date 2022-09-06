#include "ReadNode.h"

std::string ReadNode::getVariableName() {
    return variableName;
}

std::shared_ptr<ReadNode> ReadNode::createReadNode(int statementNumber, std::string variableName) {
    return std::make_shared<ReadNode>(statementNumber, variableName);
}
