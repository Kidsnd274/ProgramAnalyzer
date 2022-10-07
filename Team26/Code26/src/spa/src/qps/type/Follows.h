#ifndef SPA_FOLLOWS_H
#define SPA_FOLLOWS_H

#include "RelationClause.h"

class Follows : RelationClause {
protected:
    const static std::unordered_map<ArgumentType, std::unordered_set<ArgumentType>> validationTable;

    Follows(Argument arg1, Argument arg2) : RelationClause(arg1, arg2) {
    }
};


#endif //SPA_FOLLOWS_H
