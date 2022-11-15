#include "Affects.h"

// S1 (Major): DRY - Class structure and methods are similar to Next.cpp, Parent.cpp and Follow.cpp in type folder
const std::unordered_set<Argument::ArgumentType> secondARGs = {
        Argument::STMT_SYNONYM,
        Argument::ASSIGN_SYNONYM,
        Argument::NUMBER,
        Argument::WILDCARD,
        Argument::IF_SYNONYM,
        Argument::WHILE_SYNONYM,
        Argument::READ_SYNONYM,
        Argument::PRINT_SYNONYM,
        Argument::CALL_SYNONYM,
};

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
> Affects::affectsValidationTable {
        {
                Argument::WILDCARD,
                secondARGs
        },
        {
                Argument::NUMBER,
                secondARGs
        },
        {
                Argument::STMT_SYNONYM,
                secondARGs
        },
        {
                Argument::ASSIGN_SYNONYM,
                secondARGs
        },
        {Argument::IF_SYNONYM, secondARGs},
        {Argument::WHILE_SYNONYM, secondARGs},
        {Argument::READ_SYNONYM, secondARGs},
        {Argument::PRINT_SYNONYM, secondARGs},
        {Argument::CALL_SYNONYM, secondARGs},
};

bool Affects::isValid() {
    auto iter = Affects::affectsValidationTable.find(this->argument1.argumentType);
    if (iter != Affects::affectsValidationTable.end()) {
        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
            return true;
        }
    }
    return false;
}
