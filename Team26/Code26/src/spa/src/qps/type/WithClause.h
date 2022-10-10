#ifndef SPA_WITHCLAUSE_H
#define SPA_WITHCLAUSE_H

#include "Argument.h"
#include "Clause.h"

enum AttributeType {
    procName,
    varName,
    constValue,
    stmtLineNumber
};

class WithClause {
protected:
    struct WithClauseArgument {
        Argument::ArgumentType argumentType;

    };
};


#endif //SPA_WITHCLAUSE_H
