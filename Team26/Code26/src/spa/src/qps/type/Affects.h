#ifndef SPA_AFFECTS_H
#define SPA_AFFECTS_H


#include "RelationClause.h"

class Affects : public RelationClause {
protected:
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
    > affectsValidationTable;

public:
    Affects(Argument arg1, Argument arg2, RelationType relationType) : RelationClause(arg1, arg2, relationType) {
        this->relationType = relationType;
    }

    bool isValid() override;
};



#endif //SPA_AFFECTS_H
