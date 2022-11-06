#ifndef SPA_WITHCLAUSE_H
#define SPA_WITHCLAUSE_H

#include <unordered_map>
#include <unordered_set>
#include "Argument.h"
#include "Clause.h"

enum AttributeType {
    PROC_NAME,
    WITH_VAR_NAME,
    WITH_CONST_VALUE,
    STMT_LINE_NUMBER,
    INAPPLICABLE,
    INVALID_ATTR_TYPE
};

class WithClause : public Clause {
protected:

    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<AttributeType>
        > withClauseValidationTableArg2;

public:
    /**
     * e.g. a1.varName = "x"
     *  arg1:
     *      argument.argumentType = ASSIGN_SYNONYM,
     *      argument.argumentName = "a1",
     *      attributeType = VAR_NAME,
     *  arg2:
     *      argument.argumentType = ACTUAL_NAME,
     *      argument.argumentName = "x",
     *      attributeType = INAPPLICABLE,
     *
     */
    struct WithClauseArgument {
        Argument argument;
        AttributeType attributeType;
    } arg1, arg2;

    WithClause(WithClauseArgument arg1, WithClauseArgument arg2) {
        this->arg1 = arg1;
        this->arg2 = arg2;
    }

    bool isValid() override;

    Argument getFirstArgument() override;
    Argument getSecondArgument() override;

    const static std::unordered_map<
         Argument::ArgumentType,
         std::unordered_set<AttributeType>
         > withClauseValidationTableArg1;
};

#endif //SPA_WITHCLAUSE_H
