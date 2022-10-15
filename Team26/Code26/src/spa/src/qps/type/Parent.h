#ifndef SPA_PARENT_H
#define SPA_PARENT_H

#include "RelationClause.h"

class Parent : public RelationClause {
protected:
    const static std::unordered_set<Argument::ArgumentType> stmtSet;
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
            > parentValidationTable;

public:
    Parent(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
        this->relationType = PARENT;
    }

    virtual bool isValid() override;
};

#endif //SPA_PARENT_H
