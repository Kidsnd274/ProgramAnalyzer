#ifndef SPA_USES_H
#define SPA_USES_H

#include "RelationClause.h"

class Uses : public RelationClause {
protected:
    const static std::unordered_map<
            Argument::ArgumentType,
            std::unordered_set<Argument::ArgumentType>
            > usesValidationTable;

public:
    Uses(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
    }

    bool isValid() override;
};

#endif //SPA_USES_H
