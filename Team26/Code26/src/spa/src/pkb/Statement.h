//
// Created by QMS on 4/9/2022.
//

#ifndef SPA_STATEMENT_H
#define SPA_STATEMENT_H

#include <stdio.h>
#include <string>
#include <memory>
#include "util/ast/TNode.h"

using namespace std;

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
    int lineNumber;
    int statementListNumber;
    shared_ptr<TNode> rootNode;
};

#endif //SPA_STATEMENT_H
