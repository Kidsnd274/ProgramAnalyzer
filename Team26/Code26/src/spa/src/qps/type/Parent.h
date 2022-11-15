#ifndef SPA_PARENT_H
#define SPA_PARENT_H

#include "RelationClause.h"
#include <unordered_set>
#include <unordered_map>

// S1 (Major): DRY - Class structure and methods are similar to Next.h, Affects.h and Follows.h in type folder
class Parent : public RelationClause {
protected:
    static const std::unordered_set<Argument::ArgumentType> stmtSet;
    static const std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
            > parentValidationTable;

public:
    Parent(Argument arg1, Argument arg2, RelationType relationType) : RelationClause(arg1, arg2, relationType) {
        this->relationType = relationType;
    }

    bool isValid() override;
};

#endif  // SPA_PARENT_H
