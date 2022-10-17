#ifndef SPA_NEXT_H
#define SPA_NEXT_H

#include "RelationClause.h"

class Next : public RelationClause {
protected:
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
    > nextValidationTable;

public:
    Next(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
        relationType = NEXT;
    }

    bool isValid() override;
};


#endif //SPA_NEXT_H