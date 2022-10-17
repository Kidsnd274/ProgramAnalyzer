#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H

#include "Query.h"

class QueryEvaluator {
public:
    static void evaluate(Query* query);
    static void getAllEntity(Argument argument, QPS::ResultTable* resultTable);
    static void changeToAttrName(Query* query, QPS::ResultTable* resultTable);
    static std::string getAttrName(std::string value, Query::CandidateStruct candidate);
};


#endif //SPA_QUERYEVALUATOR_H
