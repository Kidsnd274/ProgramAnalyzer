#include "CallsStar.h"


const std::unordered_set<Argument::ArgumentType> secondARGs = {
        Argument::PROCEDURE_SYNONYM,
        Argument::PROCEDURE_ACTUAL_NAME,
        Argument::WILDCARD,
};

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
> CallsStar::callStarValidationTable {
        {
                Argument::WILDCARD,
                secondARGs
        },
        {
                Argument::PROCEDURE_ACTUAL_NAME,
                secondARGs
        },
        {
                Argument::PROCEDURE_SYNONYM,
                secondARGs
        },

};

bool CallsStar::isValid() {
    auto iter = CallsStar::callStarValidationTable.find(this->argument1.argumentType);
    if (iter != CallsStar::callStarValidationTable.end()) {
        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
            return true;
        }
    }
    return false;
}
