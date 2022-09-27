#ifndef QUERYPROCESSORTYPES_H
#define QUERYPROCESSORTYPES_H

#include<string>
#include<unordered_map>
#include<vector>
#include<map>

namespace QPS {
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

    const std::map<std::string, EntityType> entityMap = {{"stmt",      STATEMENT},
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
        UNDECLARED_ENTITY_PATTERN,
        UNDECLARED_ENTITY_SUCH_THAT,
        UNDECLARED_SELECT_ENTITY,
        UNMATCHED_QUERY_TYPE,
        INVALID_RELATION,
        INVALID_RELATION_CONTENT,
        INVALID_PATTERN_CONTENT,
        INVALID_DECLARATION,
        VALID
    };


    /*
     * Enum of Argument Types in Relation or Pattern.
     */
    enum ArgumentType {
        IF_SYNONYM,
        WHILE_SYNONYM,
        READ_SYNONYM,
        PRINT_SYNONYM,
        CALL_SYNONYM,
        ASSIGN_SYNONYM,
        STMT_SYNONYM,
        VAR_SYNONYM,
        PROCEDURE_SYNONYM,
        CONST_SYNONYM,
        ACTUAL_NAME,
        NUMBER,
        WILDCARD,
        EXPRESSION,
        INVALID_ARGUMENT_TYPE,
        PROCEDURE_ACTUAL_NAME
    };


    enum ExpressionMatchingType {
        EXACT_MATCHING,
        PARTIAL_MATCHING,
        WILDCARD_MATCHING
    };

    /*
     * The structure to represent an entity.
     */
    struct EntityStruct {
        EntityType typeOfEntity;
        std::string nameOfEntity;
    };

    struct ArgumentStruct {
        ArgumentType typeOfArgument;
        std::string nameOfArgument;
    };
    /*
     * The structure to represent a certain relation.
     */
    struct RelationStruct {
        RelationType typeOfRelation;
        ArgumentStruct arg1;
        ArgumentStruct arg2;
    };


    /*
     * The structure to represent a certain pattern.
     */
    struct PatternStruct {
        PatternType typeOfPattern;
        std::string assign_syn;
        ArgumentStruct arg1;
        ArgumentStruct arg2;
    };

    /*
     * The structure to represent a certain candidate.
     */
    struct CandidateStruct {
        CandidateType typeOfCandidate;
        EntityStruct entityOfCandidate;
    };

    typedef std::unordered_map<std::string, EntityType> DECLARED_SYNONYM_MAP;
    typedef std::vector<RelationStruct> SUCH_THAT_LIST;
    typedef std::vector<PatternStruct> PATTERN_LIST;
    typedef std::vector<CandidateStruct> CANDIDATE_LIST;

    CandidateType mapEntityToCandidate(EntityType entityType);
    bool isArgumentTypeSynonym(QPS::ArgumentType argumentType);
    std::string entityToString(EntityType entityType);
    std::string candidateToString(CandidateType candidateType);
    std::string relationToString (RelationType relationType);
    std::string ARGToString (ArgumentType argumentType);
    std::string exceptionToStringQPS(Exception e);

}
#endif // QUERYPROCESSORTYPES_H