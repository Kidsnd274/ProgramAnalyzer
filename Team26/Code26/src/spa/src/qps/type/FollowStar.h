#ifndef SPA_FOLLOWSTAR_H
#define SPA_FOLLOWSTAR_H

#include "RelationClause.h"

class FollowStar : public RelationClause {
protected:
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
    > followStarValidationTable;

    static const std::unordered_set<Argument::ArgumentType> stmtSet;

public:
    FollowStar(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
    }

    bool isValid() override;
};

#endif //SPA_FOLLOWSTAR_H
