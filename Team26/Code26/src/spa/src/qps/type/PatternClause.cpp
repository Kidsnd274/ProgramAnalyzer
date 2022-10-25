#include "PatternClause.h"

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
    > PatternClause::patternClauseValidationTable {
        {
            Argument::ASSIGN_SYNONYM,
            {
                Argument::VAR_SYNONYM,
                Argument::ACTUAL_NAME,
                Argument::WILDCARD
            }
        },
        {
                Argument::IF_SYNONYM,
                {
                        Argument::VAR_SYNONYM,
                        Argument::ACTUAL_NAME,
                        Argument::WILDCARD
                },

        },
        {
                Argument::WHILE_SYNONYM,
                {
                        Argument::VAR_SYNONYM,
                        Argument::ACTUAL_NAME,
                        Argument::WILDCARD
                }
        }
};

bool PatternClause::isValid() {
    if (this->argument3.argumentType != Argument::EXPRESSION) {
        return false;
    }
    auto iter = PatternClause::patternClauseValidationTable.find(this->argument1.argumentType);
    if (iter != PatternClause::patternClauseValidationTable.end()) {
        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
            return true;
        }
    }
    return false;
}

Argument PatternClause::getFirstArgument() {
    return this->argument1;
}

Argument PatternClause::getSecondArgument() {
    return this->argument2;
}
