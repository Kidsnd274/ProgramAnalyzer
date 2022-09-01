#include "ProcedureNode.h"

std::string ProcedureNode::getProcedureName() {
    return procedureName;
}

std::vector<std::shared_ptr<StatementNode>> ProcedureNode::getStatementList() {
    return statementList;
}
