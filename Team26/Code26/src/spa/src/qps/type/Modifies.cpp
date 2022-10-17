#include "Modifies.h"

const std::unordered_set<Argument::ArgumentType> secondARGs = {
        Argument::VAR_SYNONYM,
        Argument::ACTUAL_NAME,
        Argument::WILDCARD,
};

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
        > Modifies::modifiesValidationTable {
        {
            Argument::ASSIGN_SYNONYM,
            secondARGs
        },
        {
            Argument::READ_SYNONYM,
            secondARGs
        },
        {
            Argument::IF_SYNONYM,
            secondARGs
        },
        {
            Argument::WHILE_SYNONYM,
            secondARGs
        },
        {
            Argument::CALL_SYNONYM,
            secondARGs
        },
        {
            Argument::PROCEDURE_SYNONYM,
            secondARGs
        },
        {
            Argument::NUMBER,   // Line number of statement
            secondARGs
        },
        {
            Argument::PROCEDURE_ACTUAL_NAME,  // Actual name of procedure, i.e. "prod1"
            secondARGs
        },
        {
            Argument::WILDCARD,
            secondARGs
        },
        {
            Argument::STMT_SYNONYM,
            secondARGs
        }
};

bool Modifies::isValid() {
    auto iter = Modifies::modifiesValidationTable.find(this->argument1.argumentType);
    if (iter != Modifies::modifiesValidationTable.end()) {
        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
            return true;
        }
    }
    return false;
}
