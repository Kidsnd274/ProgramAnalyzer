#include "Uses.h"

// S1 (Major): DRY - class structure is the same as Modifies.cpp -> perhaps generalise them into one single class

const std::unordered_set<Argument::ArgumentType> secondARGs = {
        Argument::VAR_SYNONYM,
        Argument::ACTUAL_NAME,
        Argument::WILDCARD,
};

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
        > Uses::usesValidationTable {
        {
            Argument::ASSIGN_SYNONYM,
            secondARGs
        },
        {
            Argument::PRINT_SYNONYM,
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
            Argument::NUMBER, // Line number of statement
            secondARGs
        },
        {
            Argument::PROCEDURE_ACTUAL_NAME,    // Actual name of procedure, i.e. "prod1"
            secondARGs
        },
        {
            Argument::WILDCARD,
            secondARGs
        },
        {
            Argument::STMT_SYNONYM,
            secondARGs
        },
};

bool Uses::isValid() {
    auto iter = Uses::usesValidationTable.find(this->argument1.argumentType);
    if (iter != Uses::usesValidationTable.end()) {
        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
            return true;
        }
    }
    return false;
}
