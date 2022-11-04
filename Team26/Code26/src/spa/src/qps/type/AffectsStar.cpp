#include "AffectsStar.h"

const std::unordered_set<Argument::ArgumentType> secondARGs = {
        Argument::STMT_SYNONYM,
        Argument::NUMBER,
        Argument::WILDCARD,
        Argument::ASSIGN_SYNONYM
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
        {
                Argument::ASSIGN_SYNONYM,
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