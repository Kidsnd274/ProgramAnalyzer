#include "QueryProcessorTypes.h"

namespace QPS {
    bool isArgumentTypeSynonym(QPS::ArgumentType argumentType) {
        switch (argumentType) {
            case IF_SYNONYM:
            case WHILE_SYNONYM:
            case READ_SYNONYM:
            case PRINT_SYNONYM:
            case CALL_SYNONYM:
            case ASSIGN_SYNONYM:
            case STMT_SYNONYM:
            case VAR_SYNONYM:
            case PROCEDURE_SYNONYM:
            case CONST_SYNONYM:
                return true;
            default:
                return false;
        }
    }

    CandidateType mapEntityToCandidate(EntityType entityType) {
        switch (entityType) {
            case VARIABLE:
                return VAR_NAME;
            case CONSTANT:
                return CONST_VALUE;
            case PROCEDURE:
                return PROCEDURE_NAME;
            case INVALID_ENTITY_TYPE:
                return SYNTACTICALLY_INVALID_QUERY;
            case STATEMENT:
            case READ:
            case PRINT:
            case CALL:
            case WHILE:
            case IF:
            case ASSIGN:
                return STMT_NO;
        }
    }

    std::string entityToString(EntityType entityType) {
        switch (entityType) {
            case QPS::STATEMENT: {
                return "stmt";
            }
            case QPS::READ: {
                return "read";
            }
            case QPS::PRINT: {
                return "print";
            }
            case QPS::CALL: {
                return "call";
            }
            case QPS::WHILE: {
                return "while";
            }
            case QPS::IF: {
                return "if";
            }
            case QPS::ASSIGN: {
                return "assign";
            }
            case QPS::VARIABLE: {
                return "variable";
            }

            case QPS::CONSTANT: {
                return "constant";
            }
            case QPS::PROCEDURE: {
                return "procedure";
            }
            case QPS::INVALID_ENTITY_TYPE:
                return "invalid";

        }
    }


    std::string exceptionToStringQPS(Exception e) {
        switch (e) {

            case INVALID_ENTITY:{
                return "INVALID_ENTITY";
            }
            case INVALID_RELATION_SYNTAX:{
                return "INVALID_RELATION_SYNTAX";
            }
            case INVALID_SELECT:{
                return "INVALID_SELECT";
            }
            case INVALID_SUCH_THAT:{
                return "INVALID_SUCH_THAT";
            }
            case INVALID_PATTERN_NAME:{
                return "INVALID_PATTERN_NAME";
            }
            case INVALID_PATTERN_SYNTAX:{
                return "INVALID_PATTERN_SYNTAX";
            }
            case UNDECLARED_ENTITY_PATTERN:{
                return "UNDECLARED_ENTITY_PATTERN";
            }
            case UNDECLARED_ENTITY_SUCH_THAT:{
                return "UNDECLARED_ENTITY_SUCH_THAT";
            }
            case UNMATCHED_QUERY_TYPE:{
                return "UNMATCHED_QUERY_TYPE";
            }
            case INVALID_RELATION:{
                return "INVALID_RELATION";
            }
            case INVALID_RELATION_CONTENT:{
                return "INVALID_RELATION_CONTENT";
            }
            case INVALID_PATTERN_CONTENT:{
                return "INVALID_PATTERN_CONTENT";
            }
            case INVALID_DECLARATION:{
                return "INVALID_DECLARATION";
            }
            case VALID:{
                return "VALID";
            }
            case UNDECLARED_SELECT_ENTITY:{
                return "UNDECLARED_SELECT_ENTITY";
            }
            case INVALID_MULTIPLE_CLAUSE:{
                return "INVALID_MULTIPLE_CLAUSE";
            }
            case INVALID_WITH_MISSING_DOT:{
                return "INVALID_WITH_MISSING_DOT";
            }
            case INVALID_WITH_SYNTAX:{
                return "INVALID_WITH_SYNTAX";
            }
            case INVALID_WITH_FIELD:{
                return "INVALID_WITH_FIELD";
            }
            case INVALID_WITH_TYPE_EXCEPTION:{
                return "INVALID_WITH_TYPE_EXCEPTION";
            }
            case UNDECLARED_ENTITY_WITH:{
                return "UNDECLARED_ENTITY_WITH";
            }
        }
    }

    std::string relationToString (RelationType relationType) {
        switch (relationType) {

            case FOLLOWS:{
                return "follows";
            }
            case FOLLOWS_T:{
                return "follows*";
            }
            case PARENT:{
                return "parent";
            }
            case PARENT_T:{
                return "parent*";
            }
            case USES_S:{
                return "uses_s";
            }
            case USES_P: {
                return "uses_p";
            }
            case MODIFIES_S:{
                return "modifies_s";
            }
            case MODIFIES_P: {
                return "modifies_p";
            }
            case INVALID_RELATION_TYPE:{
                return "Invalid";
            }
            case CALLS:{
                return "calls";
            }
            case CALLS_P:{
                return "calls_p";
            }
            case NEXT:{
                return "next";
            }
            case NEXT_P:{
                return "next_p";
            }
            case AFFECTS:{
                return "affects";
            }
            case AFFECTS_P:{
                return "affects_p";
            }
        }
    }
    std::string candidateToString(CandidateType candidateType) {
        switch (candidateType) {
            case STMT_NO: {
                return "stmt_no";
            }
            case VAR_NAME: {
                return "variable";
            }
            case CONST_VALUE: {
                return "constant";
            }
            case EMPTY_RESULT: {
                return "empty";
            }

            case SYNTACTICALLY_INVALID_QUERY: {
                return "invalid";
            }

            case PROCEDURE_NAME: {
                return "procedure";
            }

            case BOOLEAN: {
                return "bool";
            }
        }
    }
}