#ifndef SPA_WITHCLAUSE_H
#define SPA_WITHCLAUSE_H

#include "Argument.h"
#include "Clause.h"

enum AttributeType {
    PROC_NAME,
    VAR_NAME,
    CONST_VALUE,
    STMT_LINE_NUMBER,
    ATTR_VALUE
};

class WithClause : public Clause {
protected:
    struct WithClauseArgument {
        Argument argument;
        AttributeType attributeType;
    } arg1, arg2;

    WithClause(WithClauseArgument arg1, WithClauseArgument arg2) {
        this->arg1 = arg1;
        this->arg2 = arg2;
    }

    bool isValid() override;
};

#endif //SPA_WITHCLAUSE_H
