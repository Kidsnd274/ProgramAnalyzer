#include "Follows.h"

const std::unordered_set<Argument::ArgumentType> Follows::stmtSet {
    Argument::STMT_SYNONYM,
    Argument::IF_SYNONYM,
    Argument::WHILE_SYNONYM,
    Argument::READ_SYNONYM,
    Argument::PRINT_SYNONYM,
    Argument::CALL_SYNONYM,
    Argument::ASSIGN_SYNONYM,
    Argument::NUMBER
};

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
        > Follows::followsValidationTable {
        {Argument::STMT_SYNONYM, stmtSet},
        {Argument::IF_SYNONYM, stmtSet},
        {Argument::WHILE_SYNONYM, stmtSet},
        {Argument::READ_SYNONYM, stmtSet},
        {Argument::PRINT_SYNONYM, stmtSet},
        {Argument::CALL_SYNONYM, stmtSet},
        {Argument::ASSIGN_SYNONYM, stmtSet},
        {Argument::NUMBER, stmtSet}
};

bool Follows::isValid() {
    auto iter = Follows::followsValidationTable.find(this->argument1.argumentType);
    if (iter != Follows::followsValidationTable.end()) {
        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
            return true;
        }
    }
    return false;
}
