#ifndef QUERYPROCESSORTYPES_H
#define QUERYPROCESSORTYPES_H

#include<string>
#include<unordered_map>
#include<vector>
#include<map>

namespace QPS {





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
        INVALID_PATTERN_TYPE,
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