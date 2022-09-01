#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "StatementNode.h"

class ProcedureNode {
private:
    std::string procedureName;
    std::vector<std::shared_ptr<StatementNode>> stmtList;

public:
    ProcedureNode(std::string pN, std::vector<std::shared_ptr<StatementNode>> sl) {
        procedureName = std::move(pN);
        stmtList = std::move(sl);
    }

    std::string getProcedureName();
    std::vector<std::shared_ptr<StatementNode>> getStatementList();
};
