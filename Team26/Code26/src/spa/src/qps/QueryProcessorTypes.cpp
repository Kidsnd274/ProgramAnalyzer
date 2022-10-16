#include "QueryProcessorTypes.h"
#include "qps/type/RelationClause.h"

namespace QPS {


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
            case CALLS_T:{
                return "calls_p";
            }
            case NEXT:{
                return "next";
            }
            case NEXT_T:{
                return "next_p";
            }
            case AFFECTS:{
                return "affects";
            }
            case AFFECTS_T:{
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