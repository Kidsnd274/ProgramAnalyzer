#ifndef SPA_AFFECTSSTAR_H
#define SPA_AFFECTSSTAR_H

#include "RelationClause.h"

class AffectsStar : public RelationClause {
protected:
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
    > affectStarValidationTable;

public:
    AffectsStar(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
        relationType = AFFECTS_T;
    }

    bool isValid() override;
};


#endif //SPA_AFFECTSSTAR_H
