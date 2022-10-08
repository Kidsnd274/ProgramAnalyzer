#ifndef SPA_FOLLOWS_H
#define SPA_FOLLOWS_H

#include "RelationClause.h"

class Follows : public RelationClause {
protected:
    const static std::unordered_set<Argument::ArgumentType> stmtSet;
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
            > followsValidationTable;

public:
    Follows(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
    }

    bool isValid() override;
};

#endif //SPA_FOLLOWS_H
