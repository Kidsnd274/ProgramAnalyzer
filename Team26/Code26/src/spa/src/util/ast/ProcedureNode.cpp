#include "ProcedureNode.h"

std::string ProcedureNode::getProcedureName() {
    return procedureName;
}

std::vector<std::shared_ptr<StatementNode>> ProcedureNode::getStatementList() {
    return statementList;
}

std::shared_ptr<ProcedureNode> ProcedureNode::createProcedureNode(std::string procedureName,
                                                                  std::vector<std::shared_ptr<StatementNode>> statementList) {
    return std::make_shared<ProcedureNode>(procedureName, statementList);
}
