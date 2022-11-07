#ifndef SPA_PATTERNCLAUSE_H
#define SPA_PATTERNCLAUSE_H

#include <unordered_set>
#include <unordered_map>
#include "Argument.h"
#include "Clause.h"

class PatternClause : public Clause {
protected:
    static const std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
            > patternClauseValidationTable;

public:
    Argument argument1;
    Argument argument2;
    Argument argument3;

public:
    PatternClause(Argument& arg1, Argument& arg2, Argument& arg3) :
            argument1(Argument("", Argument::INVALID_ARGUMENT_TYPE)),
            argument2(Argument("", Argument::INVALID_ARGUMENT_TYPE)),
            argument3(Argument("", Argument::INVALID_ARGUMENT_TYPE)) {
        this->argument1 = arg1;
        this->argument2 = arg2;
        this->argument3 = arg3;
    }

    bool isValid() override;

    Argument getFirstArgument() override;
    Argument getSecondArgument() override;
};


#endif  // SPA_PATTERNCLAUSE_H
