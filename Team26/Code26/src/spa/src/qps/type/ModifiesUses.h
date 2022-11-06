#ifndef SPA_MODIFIES_H
#define SPA_MODIFIES_H

#include "RelationClause.h"

class ModifiesUses : public RelationClause {
protected:
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
    > modifiesValidationTable;

public:
    ModifiesUses(Argument arg1, Argument arg2, RelationType relationType) : RelationClause(arg1, arg2, relationType) {
        this->relationType = relationType;
    }

    bool isValid() override;
};


#endif //SPA_MODIFIES_H
