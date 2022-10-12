#include "WithClause.h"

const std::unordered_map<
        Argument::ArgumentType,
        AttributeType
    > WithClause::withClauseValidationTableArg1{
        {Argument::IF_SYNONYM, STMT_LINE_NUMBER},
        {Argument::WHILE_SYNONYM, STMT_LINE_NUMBER},
        {Argument::READ_SYNONYM, STMT_LINE_NUMBER},
        {Argument::PRINT_SYNONYM, STMT_LINE_NUMBER},
        {Argument::CALL_SYNONYM, STMT_LINE_NUMBER},
        {Argument::ASSIGN_SYNONYM, STMT_LINE_NUMBER},
        {Argument::STMT_SYNONYM, STMT_LINE_NUMBER},
        {Argument::VAR_SYNONYM, VAR_NAME},
        {Argument::PROCEDURE_SYNONYM, PROC_NAME},
        {Argument::CONST_SYNONYM, CONST_VALUE},
};

const std::unordered_map<
        Argument::ArgumentType,
        AttributeType
    > WithClause::withClauseValidationTableArg2 {
        {Argument::IF_SYNONYM, STMT_LINE_NUMBER},
        {Argument::WHILE_SYNONYM, STMT_LINE_NUMBER},
        {Argument::READ_SYNONYM, STMT_LINE_NUMBER},
        {Argument::PRINT_SYNONYM, STMT_LINE_NUMBER},
        {Argument::CALL_SYNONYM, STMT_LINE_NUMBER},
        {Argument::ASSIGN_SYNONYM, STMT_LINE_NUMBER},
        {Argument::STMT_SYNONYM, STMT_LINE_NUMBER},
        {Argument::VAR_SYNONYM, VAR_NAME},
        {Argument::PROCEDURE_SYNONYM, PROC_NAME},
        {Argument::CONST_SYNONYM, CONST_VALUE},
        {Argument::ACTUAL_NAME, INAPPLICABLE},
        {Argument::NUMBER, INAPPLICABLE}
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
    if (iter1->second != this->arg1.attributeType || iter2->second != this->arg2.attributeType) {
        return false;
    }
    return true;
}