#ifndef SPA_MODIFIES_H
#define SPA_MODIFIES_H

#include "RelationClause.h"
#include <unordered_set>
#include <unordered_map>

class ModifiesUses : public RelationClause {
protected:
    static const std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
    > modifiesValidationTable;

public:
    ModifiesUses(Argument arg1, Argument arg2, RelationType relationType) : RelationClause(arg1, arg2, relationType) {
        this->relationType = relationType;
    }

    bool isValid() override;
};


#endif  // SPA_MODIFIES_H
