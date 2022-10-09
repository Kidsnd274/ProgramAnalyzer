#include "Uses.h"

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
        > Uses::usesValidationTable {
        {
            Argument::ASSIGN_SYNONYM,
            {
                Argument::VAR_SYNONYM,
                Argument::ACTUAL_NAME
            }
        },
        {
            Argument::PRINT_SYNONYM,
            {
                Argument::VAR_SYNONYM,
                Argument::ACTUAL_NAME
            }
        },
        {
            Argument::IF_SYNONYM,
            {
                Argument::VAR_SYNONYM,
                Argument::ACTUAL_NAME
            }
        },
        {
            Argument::WHILE_SYNONYM,
            {
                Argument::VAR_SYNONYM,
                Argument::ACTUAL_NAME
            }
        },
        {
            Argument::CALL_SYNONYM,
            {
                Argument::VAR_SYNONYM,
                Argument::ACTUAL_NAME
            }
        },
        {
            Argument::PROCEDURE_SYNONYM,
            {
                Argument::VAR_SYNONYM,
                Argument::ACTUAL_NAME
            }
        },
        {
            Argument::NUMBER, // Line number of statement
            {
                Argument::VAR_SYNONYM,
                Argument::ACTUAL_NAME
            }
        },
        {
            Argument::ACTUAL_NAME,    // Actual name of procedure, i.e. "prod1"
            {
                Argument::VAR_SYNONYM,
                Argument::ACTUAL_NAME
            }
        }
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
