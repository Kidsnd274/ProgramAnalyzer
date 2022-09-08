#include "QueryProcessorTypes.h"

namespace QPS {
    bool isEntity(const std::string& value) {
        if (QPS::entityMap.find(value) == QPS::entityMap.end()) {
            return false;
        } else {
            return true;
        }
    }

    bool isRelation(const std::string& value) {
        if (QPS::relationMap.find(value) == QPS::relationMap.end()) {
            return false;
        } else {
            return true;
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

    std::string ARGToString (ArgumentType argumentType) {
        switch (argumentType) {

            case STMT_SYNONYM:{
                return "STMT_SYNONYM";
            }
            case VAR_SYNONYM:{
                return "VAR_SYNONYM";
            }
            case PROCEDURE_SYNONYM:{
                return "PROCEDURE_SYNONYM";
            }
            case CONST_SYNONYM:{
                return "CONST_SYNONYM";
            }
            case NAME_OF_ENTITY:{
                return "NAME_OF_ENTITY";
            }
            case NUMBER:{
                return "NUMBER";
            }
            case WILDCARD:{
                return "WILDCARD";
            }
            case INVALID_ARGUMENT_TYPE:{
                return "INVALID_ARGUMENT_TYPE";
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
                return "uses";
            }
            case MODIFIES_S:{
                return "modifies";
            }
            case INVALID_RELATION_TYPE:{
                return "Invalid";
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