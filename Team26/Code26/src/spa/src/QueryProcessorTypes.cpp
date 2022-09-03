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