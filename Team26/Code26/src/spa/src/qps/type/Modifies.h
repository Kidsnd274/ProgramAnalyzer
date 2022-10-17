#ifndef SPA_MODIFIES_H
#define SPA_MODIFIES_H

#include "RelationClause.h"

class Modifies : public RelationClause {
protected:
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
            > modifiesValidationTable;

public:
    Modifies(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
        relationType = MODIFIES_S;
    }

    bool isValid() override;
};


#endif //SPA_MODIFIES_H
