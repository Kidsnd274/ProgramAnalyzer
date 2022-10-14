#ifndef SPA_NEXTSTAR_H
#define SPA_NEXTSTAR_H


#include "RelationClause.h"

class NextStar : public RelationClause {
protected:
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
    > nextStarValidationTable;

public:
    NextStar(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
    }

    bool isValid() override;
};

#endif //SPA_NEXTSTAR_H
