#include "Affects.h"

// S1 (Major): DRY - class structure is the same as AffectsStar.cpp -> perhaps generalise them into one single class
const std::unordered_set<Argument::ArgumentType> secondARGs = {
        Argument::STMT_SYNONYM,
        Argument::NUMBER,
        Argument::WILDCARD,
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
