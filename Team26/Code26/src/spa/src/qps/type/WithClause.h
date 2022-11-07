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
struct ArgAttrStruct {
    Argument argument;
    AttributeType attributeType;
};

class WithClause : public Clause {
protected:
    static const std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<AttributeType>
        > withClauseValidationTableArg2;

public:
    ArgAttrStruct arg1, arg2;

public:
    WithClause(ArgAttrStruct arg1, ArgAttrStruct arg2) {
        this->arg1 = arg1;
        this->arg2 = arg2;
    }

    bool isValid() override;

    Argument getFirstArgument() override;
    Argument getSecondArgument() override;

    static const std::unordered_map<
         Argument::ArgumentType,
         std::unordered_set<AttributeType>
         > withClauseValidationTableArg1;
};

#endif  // SPA_WITHCLAUSE_H
