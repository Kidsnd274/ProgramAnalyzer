#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include "QueryProcessorTypes.h"
#include "QueryStruct.h"
#include "pkb/PKBInterface.h"

namespace QPS {
    class BasicQueryEvaluator {
    public:
        static void evaluateQuery(QueryStruct& query, PKBInterface *pkb);
    };
}

#endif // QUERYEVALUATOR_H