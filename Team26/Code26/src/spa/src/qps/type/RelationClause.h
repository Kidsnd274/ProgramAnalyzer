#ifndef SPA_RELATIONCLAUSE_H
#define SPA_RELATIONCLAUSE_H

#include "Argument.h"

enum RelationType {
    FOLLOWS,    // Follows(stmtRef, stmtRef)
    FOLLOWS_T,  // Follows*(stmtRef, stmtRef)
    PARENT, // Parent(stmtRef, stmtRef)
    PARENT_T,   // Parent*(stmtRef, stmtRef)
    USES_S,
    MODIFIES_S,
    USES_P,
    MODIFIES_P,
    CALLS,
    CALLS_P,
    NEXT,
    NEXT_P,
    AFFECTS,
    AFFECTS_P,
    INVALID_RELATION_TYPE
};

class RelationClause {
private:
    Argument argument1;
    Argument argument2;

public:
    RelationClause(Argument arg1, Argument arg2) :
        argument1(Argument("", INVALID_ARGUMENT_TYPE)),
        argument2(Argument("", INVALID_ARGUMENT_TYPE))
    {
        this->argument1 = arg1;
        this->argument2 = arg2;
    }

    Argument getFirstArgument();

    Argument getSecondArgument();

    void setFirstArgument(Argument argument);

    void setSecondArgument(Argument argument);

    virtual bool isValid();
};


#endif //SPA_RELATIONCLAUSE_H
