#ifndef SPA_CALLS_H
#define SPA_CALLS_H


#include "RelationClause.h"

class Calls : public RelationClause {
protected:
const static std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
> callsValidationTable;

public:
    Calls(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
    }

    bool isValid() override;
};


#endif //SPA_CALLS_H
