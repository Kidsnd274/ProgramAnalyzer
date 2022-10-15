#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H

#include "Query.h"

class QueryEvaluator {
public:
    static void evaluate(Query* query);
    static void getAllEntity(Argument argument, QPS::ResultTable* resultTable);
};


#endif //SPA_QUERYEVALUATOR_H
