#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include "QueryStruct.h"

namespace QPS {
    class BasicQueryEvaluator {
    public:
        static void evaluateQuery(QueryStruct& query);
    };
}

#endif // QUERYEVALUATOR_H