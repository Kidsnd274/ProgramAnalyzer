#ifndef SPA_STATEMENT_H
#define SPA_STATEMENT_H

#include <string>
#include <memory>
#include "util/Common.h"
#include "util/ast/TNode.h"

namespace StatementType {
    enum StmtType {
        READ,
        ASSIGN,
        WHILE,
        IF,
        PRINT,
        CALL
    };
}

class Statement {
public:
    StatementType::StmtType type;
    STMT_NUM lineNumber;
    STMT_NUM statementListNumber;
    std::shared_ptr<TNode> rootNode;
    std::string calleeProcName;
};

#endif  // SPA_STATEMENT_H
