#include <string>
#include "IStatementNode.h"

class ProcedureNode : public TNode {
private:
    std::string procedureName;
    std::vector<std::shared_ptr<IStatementNode>> stmtList;

public:
    ProcedureNode(int sN, std::string pN, std::vector<std::shared_ptr<IStatementNode>> sl) : TNode(sN) {
        procedureName = pN;
        stmtList = sl;
    }
};