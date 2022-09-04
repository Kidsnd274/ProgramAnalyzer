#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "StatementNode.h"

class ProcedureNode {
private:
    std::string procedureName;
    std::vector<std::shared_ptr<StatementNode>> statementList;

public:
    ProcedureNode(std::string procedureName, std::vector<std::shared_ptr<StatementNode>> statementList) {
        this->procedureName = std::move(procedureName);
        this->statementList = std::move(statementList);
    }

    std::string getProcedureName();
    std::vector<std::shared_ptr<StatementNode>> getStatementList();

    static std::shared_ptr<ProcedureNode> createProcedureNode(std::string procedureName,
                                                              std::vector<std::shared_ptr<StatementNode>> statementList);
};
