#ifndef QUERYPROCESSORTYPES_H
#define QUERYPROCESSORTYPES_H

#include<string>
#include<unordered_map>
#include<vector>
#include <map>

namespace QueryProcessorTypes {
/*
 * Enum of the Design Entities in Program Query Language.
 */
    enum EntityType {
        STATEMENT,
        READ,
        PRINT,
        CALL,
        WHILE,
        IF,
        ASSIGN,
        VARIABLE,
        CONSTANT,
        PROCEDURE,
        INVALID_ENTITY_TYPE
    };

    std::map<std::string, EntityType> entityMap = {{"stmt",      STATEMENT},
                                                   {"read",      READ},
                                                   {"print",     PRINT},
                                                   {"call",      CALL},
                                                   {"while",     WHILE},
                                                   {"if",        IF},
                                                   {"assign",    ASSIGN},
                                                   {"variable",  VARIABLE},
                                                   {"constant",  CONSTANT},
                                                   {"procedure", PROCEDURE},
                                                   {"",          INVALID_ENTITY_TYPE}};

    bool isEntity(const std::string&);


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
        INVALID_RELATION_TYPE
    };

    std::map<std::string, RelationType> relationMap = {{"Follows",  FOLLOWS},
                                                       {"Follows*", FOLLOWS_T},
                                                       {"Parent",   PARENT},
                                                       {"Parent*",  PARENT_T},
                                                       {"Uses",     USES_S},
                                                       {"Modifies", MODIFIES_S},
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
        EMPTY_RESULT,   // No entities matching the query. Return empty result.
        SYNTACTICALLY_INVALID_QUERY // Return empty result.
    };

/*
 * Enum of Argument Types in Relation or Pattern.
 */
    enum ArgumentType {
        STMT_SYNONYM,
        VAR_SYNONYM,
        PROCEDURE_SYNONYM,
        CONST_SYNONYM,
        NAME_OF_ENTITY,
        NUMBER,
        WILDCARD,
        INVALID_ARGUMENT_TYPE
    };

/*
 * The structure to represent a certain relation.
 */
    struct RelationStruct {
        RelationType typeOfRelation;
        ArgumentType arg1;
        ArgumentType arg2;
    };


/*
 * The structure to represent a certain pattern.
 */
    struct PatternStruct {
        PatternType typeOfPattern;
        ArgumentType arg1;
        ArgumentType arg2;
    };

/*
 * The structure to represent a certain candidate.
 */
    struct CandidateStruct {
        CandidateType typeOfCandidate;
        std::string resultString;
    };

    typedef std::unordered_map<std::string, EntityType> DECLARED_SYNONYM_MAP;
    typedef std::vector<RelationStruct> SUCH_THAT_LIST;
    typedef std::vector<PatternStruct> PATTERN_LIST;
    typedef std::vector<CandidateStruct> CANDIDATE_LIST;

    CandidateType mapEntityToCandidate(EntityType entityType);
    std::string entityToString(EntityType entityType);
    std::string candidateToString(CandidateType candidateType);


}
#endif // QUERYPROCESSORTYPES_H