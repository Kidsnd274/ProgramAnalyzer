
#ifndef SPA_CALLSSTAR_H
#define SPA_CALLSSTAR_H

#include "RelationClause.h"

class CallsStar : public RelationClause {
protected:
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
    > modifiesValidationTable;

public:
    CallsStar(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
    }

    bool isValid() override;
};


#endif //SPA_CALLSSTAR_H
