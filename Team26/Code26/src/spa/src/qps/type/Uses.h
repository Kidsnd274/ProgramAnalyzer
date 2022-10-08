#ifndef SPA_USES_H
#define SPA_USES_H

#include "RelationClause.h"

class Uses : RelationClause {
protected:
    const static std::unordered_map<ArgumentType, std::unordered_set<ArgumentType>> validationTable;

public:
    Uses(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
    }
};

#endif //SPA_USES_H
