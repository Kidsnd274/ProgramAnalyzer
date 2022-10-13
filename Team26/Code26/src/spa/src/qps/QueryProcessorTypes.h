#ifndef QUERYPROCESSORTYPES_H
#define QUERYPROCESSORTYPES_H

#include<string>
#include<unordered_map>
#include<vector>
#include<map>

namespace QPS {

/*
 * Enum of the Relation Types in Program Query Language.
 */
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

    const std::map<std::string, RelationType> relationMap = {{"Follows",  FOLLOWS},
                                                       {"Follows*", FOLLOWS_T},
                                                       {"Parent",   PARENT},
                                                       {"Parent*",  PARENT_T},
                                                       {"Uses",     USES_S},
                                                       {"Modifies", MODIFIES_S},
                                                       {"Calls", CALLS},
                                                       {"Calls*", CALLS_P},
                                                       {"Next", NEXT},
                                                       {"Next*", NEXT_P},
                                                       {"Affects", AFFECTS},
                                                       {"Affects*", AFFECTS_P},
                                                       {"",         INVALID_RELATION_TYPE}};

    bool isRelation(std::string);

/*
 * Enum of the Pattern Types in Program Query Language.
 */
    enum PatternType {
        ASSIGN_PATTERN, // pattern syn_assign(entRef, expression_spec)
        INVALID_PATTERN_TYPE
    };

    /*
     * Enum of the Evaluation Result Candidate Types
     */
    enum CandidateType {
        STMT_NO,    // Select stmt | read | print | call | while | if | assign
        VAR_NAME,
        PROCEDURE_NAME,
        CONST_VALUE,
        BOOLEAN,    // Select Boolean
        EMPTY_RESULT,   // No entities matching the query. Return empty result.
        SYNTACTICALLY_INVALID_QUERY // Return empty result.
    };

    enum Exception {
        INVALID_ENTITY,
        INVALID_RELATION_SYNTAX,
        INVALID_SELECT,
        INVALID_SUCH_THAT,
        INVALID_PATTERN_NAME,
        INVALID_PATTERN_SYNTAX,
        INVALID_WITH_MISSING_DOT,
        INVALID_WITH_SYNTAX,
        INVALID_WITH_FIELD,
        INVALID_WITH_TYPE_EXCEPTION,
        UNDECLARED_ENTITY_PATTERN,
        UNDECLARED_ENTITY_WITH,
        UNDECLARED_ENTITY_SUCH_THAT,
        UNDECLARED_SELECT_ENTITY,
        UNMATCHED_QUERY_TYPE,
        INVALID_RELATION,
        INVALID_RELATION_CONTENT,
        INVALID_PATTERN_CONTENT,
        INVALID_DECLARATION,
        INVALID_MULTIPLE_CLAUSE,
        VALID
    };


    enum ExpressionMatchingType {
        EXACT_MATCHING,
        PARTIAL_MATCHING,
        WILDCARD_MATCHING
    };




}
#endif // QUERYPROCESSOPES_H