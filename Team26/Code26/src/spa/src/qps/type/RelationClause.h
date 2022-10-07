#ifndef SPA_RELATIONCLAUSE_H
#define SPA_RELATIONCLAUSE_H

#include <unordered_map>
#include <unordered_set>
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

int intArray[30];

class RelationClause {
private:
    Argument argument1;
    Argument argument2;
protected:
    const static std::unordered_map<ArgumentType, std::unordered_set<ArgumentType>> validationTable;

public:
    RelationClause(Argument& arg1, Argument& arg2) :
            argument1(Argument("", INVALID_ARGUMENT_TYPE)),
            argument2(Argument("", INVALID_ARGUMENT_TYPE)) {
        this->argument1 = arg1;
        this->argument2 = arg2;
    }

    RelationClause(RelationClause& relationClause) :
            argument1(Argument("", INVALID_ARGUMENT_TYPE)),
            argument2(Argument("", INVALID_ARGUMENT_TYPE)) {
        this->argument1 = relationClause.argument1;
        this->argument2 = relationClause.argument2;
    }

    Argument getFirstArgument();

    Argument getSecondArgument();

    void setFirstArgument(const Argument& argument);

    void setSecondArgument(const Argument& argument);

    virtual bool isValid();
};

#endif //SPA_RELATIONCLAUSE_H
