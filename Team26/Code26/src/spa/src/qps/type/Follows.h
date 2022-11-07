#ifndef SPA_FOLLOWS_H
#define SPA_FOLLOWS_H

#include "RelationClause.h"
#include <unordered_map>
#include <unordered_set>

class Follows : public RelationClause {
protected:
    static const std::unordered_set<Argument::ArgumentType> stmtSet;
    static const std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
            > followsValidationTable;

public:
    Follows(Argument arg1, Argument arg2, RelationType relationType) : RelationClause(arg1, arg2, relationType) {
        this->relationType = relationType;
    }

    bool isValid() override;
};

#endif  // SPA_FOLLOWS_H
