#include "QueryProcessorTypes.h"
namespace QueryProcessorTypes {
    bool isEntity(const std::string& value) {
        if (QueryProcessorTypes::entityMap.find(value) == QueryProcessorTypes::entityMap.end()) {
            return false;
        } else {
            return true;
        }
    }

    bool isRelation(const std::string& value) {
        if (QueryProcessorTypes::relationMap.find(value) == QueryProcessorTypes::relationMap.end()) {
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
            case QueryProcessorTypes::STATEMENT: {
                return "stmt";
            }
            case QueryProcessorTypes::READ: {
                return "read";
            }
            case QueryProcessorTypes::PRINT: {
                return "print";
            }
            case QueryProcessorTypes::CALL: {
                return "call";
            }
            case QueryProcessorTypes::WHILE: {
                return "while";
            }
            case QueryProcessorTypes::IF: {
                return "if";
            }
            case QueryProcessorTypes::ASSIGN: {
                return "assign";
            }
            case QueryProcessorTypes::VARIABLE: {
                return "variable";
            }

            case QueryProcessorTypes::CONSTANT: {
                return "constant";
            }
            case QueryProcessorTypes::PROCEDURE: {
                return "procedure";
            }
            case QueryProcessorTypes::INVALID_ENTITY_TYPE:
                return "invalid";

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

        }
    }
}