#include "WithClause.h"

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<AttributeType>
    > WithClause::withClauseValidationTableArg1{
        {
            Argument::IF_SYNONYM,
            {
                STMT_LINE_NUMBER
            }
        },
        {
            Argument::WHILE_SYNONYM,
            {
                STMT_LINE_NUMBER
            }
        },
        {
            Argument::READ_SYNONYM,
            {
                STMT_LINE_NUMBER,
                WITH_VAR_NAME
            }
        },
        {
            Argument::PRINT_SYNONYM,
            {
                STMT_LINE_NUMBER,
                WITH_VAR_NAME
            }
        },
        {
            Argument::CALL_SYNONYM,
            {
                STMT_LINE_NUMBER,
                PROC_NAME
            }
        },
        {
            Argument::ASSIGN_SYNONYM,
            {
                STMT_LINE_NUMBER,
            }
        },
        {
            Argument::STMT_SYNONYM,
            {
                STMT_LINE_NUMBER
            }
        },
        {
            Argument::VAR_SYNONYM,
            {
                WITH_VAR_NAME
            }
        },
        {
            Argument::PROCEDURE_SYNONYM,
            {
                PROC_NAME,
                STMT_LINE_NUMBER
            }
        },
        {
            Argument::CONST_SYNONYM,
            {
                WITH_CONST_VALUE
            }
        },
        {
                Argument::ACTUAL_NAME,
                {
                        INAPPLICABLE
                }
        },
        {
                Argument::NUMBER,
                {
                        INAPPLICABLE
                }
        }
};

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<AttributeType>
    > WithClause::withClauseValidationTableArg2{
        {
            Argument::IF_SYNONYM,
            {
                    STMT_LINE_NUMBER
            }
        },
        {
            Argument::WHILE_SYNONYM,
            {
                    STMT_LINE_NUMBER
            }
        },
        {
            Argument::READ_SYNONYM,
            {
                    STMT_LINE_NUMBER,
                    WITH_VAR_NAME
            }
        },
        {
            Argument::PRINT_SYNONYM,
            {
                    STMT_LINE_NUMBER,
                    WITH_VAR_NAME
            }
        },
        {
            Argument::CALL_SYNONYM,
            {
                    STMT_LINE_NUMBER,
                    PROC_NAME
            }
        },
        {
            Argument::ASSIGN_SYNONYM,
            {
                    STMT_LINE_NUMBER,
            }
        },
        {
            Argument::STMT_SYNONYM,
            {
                    STMT_LINE_NUMBER
            }
        },
        {
            Argument::VAR_SYNONYM,
            {
                    WITH_VAR_NAME
            }
        },
        {
            Argument::PROCEDURE_SYNONYM,
            {
                    PROC_NAME,
                    STMT_LINE_NUMBER
            }
        },
        {
            Argument::CONST_SYNONYM,
            {
                    WITH_CONST_VALUE
            }
        },
        {
            Argument::ACTUAL_NAME,
            {
                INAPPLICABLE
            }
        },
        {
            Argument::NUMBER,
            {
                INAPPLICABLE
            }
        }
};

bool WithClause::isValid() {
    auto iter1 = WithClause::withClauseValidationTableArg1
            .find(this->arg1.argument.argumentType);
    if (iter1 == WithClause::withClauseValidationTableArg1.end()) {
        return false;
    }
    auto iter2 = WithClause::withClauseValidationTableArg2
            .find(this->arg2.argument.argumentType);
    if (iter2 == WithClause::withClauseValidationTableArg2.end()) {
        return false;
    }
    auto iter3 = iter1->second.find(this->arg1.attributeType);
    if (iter3 == iter1->second.end()) {
        return false;
    }
    auto iter4 = iter2->second.find(this->arg2.attributeType);
    if (iter4 == iter2->second.end()) {
        return false;
    }
    return true;
}