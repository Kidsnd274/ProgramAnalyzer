
#include "NextStar.h"


const std::unordered_set<Argument::ArgumentType> secondARGs = {
        Argument::STMT_SYNONYM,
        Argument::NUMBER,
        Argument::WILDCARD,
};

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
> NextStar::nextStarValidationTable {
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

bool NextStar::isValid() {
    auto iter = NextStar::nextStarValidationTable.find(this->argument1.argumentType);
    if (iter != NextStar::nextStarValidationTable.end()) {
        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
            return true;
        }
    }
    return false;
}