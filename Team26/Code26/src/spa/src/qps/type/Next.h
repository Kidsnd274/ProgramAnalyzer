#ifndef SPA_NEXT_H
#define SPA_NEXT_H

#include "RelationClause.h"
#include <unordered_map>
#include <unordered_set>

class Next : public RelationClause {
protected:
    static const std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
    > nextValidationTable;

public:
    Next(Argument arg1, Argument arg2, RelationType relationType) : RelationClause(arg1, arg2, relationType) {
        this->relationType = relationType;
    }

    bool isValid() override;
};


#endif  // SPA_NEXT_H
