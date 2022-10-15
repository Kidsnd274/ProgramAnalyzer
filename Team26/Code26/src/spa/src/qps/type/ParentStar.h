#ifndef SPA_PARENTSTAR_H
#define SPA_PARENTSTAR_H
#include "RelationClause.h"

class ParentStar : public RelationClause {
protected:
    const static std::unordered_map<
    Argument::ArgumentType,
    std::unordered_set<Argument::ArgumentType>
    > parentStarValidationTable;

    const static std::unordered_set<Argument::ArgumentType> stmtSet;

public:
    ParentStar(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
        relationType = PARENT_T;
    }

    virtual bool isValid() override;
};

#endif //SPA_PARENTSTAR_H
