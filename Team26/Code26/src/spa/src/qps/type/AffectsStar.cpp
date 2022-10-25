#include "AffectsStar.h"

// S1 (Major): DRY - class structure is the same as Affects.cpp -> perhaps generalise them into one single class
const std::unordered_set<Argument::ArgumentType> secondARGs = {
        Argument::STMT_SYNONYM,
        Argument::NUMBER,
        Argument::WILDCARD,
};

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
> AffectsStar::affectStarValidationTable {
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

bool AffectsStar::isValid() {
    auto iter = AffectsStar::affectStarValidationTable.find(this->argument1.argumentType);
    if (iter != AffectsStar::affectStarValidationTable.end()) {
        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
            return true;
        }
    }
    return false;
}