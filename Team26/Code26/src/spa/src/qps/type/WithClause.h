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

class WithClause : public Clause {
protected:
    struct WithClauseArgument {
        Argument::ArgumentType argumentType;
        AttributeType attributeType;
        std::string attributeValue;
    } arg1, arg2;

    WithClause(WithClauseArgument arg1, WithClauseArgument arg2) {
        this->arg1 = arg1;
        this->arg2 = arg2;
    }

    bool isValid() override;
};

#endif //SPA_WITHCLAUSE_H
