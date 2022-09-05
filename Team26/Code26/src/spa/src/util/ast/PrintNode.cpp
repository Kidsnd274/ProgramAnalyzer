#include "PrintNode.h"

std::string PrintNode::getVariableName() {
    return variableName;
}

std::shared_ptr<PrintNode> PrintNode::createPrintNode(int statementNumber, std::string variableName) {
    return std::make_shared<PrintNode>(statementNumber, variableName);
}
