#include "Next.h"

const std::unordered_set<Argument::ArgumentType> secondARGs = {
        Argument::STMT_SYNONYM,
        Argument::NUMBER,
        Argument::WILDCARD,
};

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
> Next::nextValidationTable {
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
bool Next::isValid() {
    auto iter = Next::nextValidationTable.find(this->argument1.argumentType);
    if (iter != Next::nextValidationTable.end()) {
        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
            return true;
        }
    }
    return false;
}
