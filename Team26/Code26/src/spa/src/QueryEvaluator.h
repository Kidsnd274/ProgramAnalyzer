#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include "QueryProcessorTypes.h"
#include "QueryStruct.h"

namespace QPS {
    class BasicQueryEvaluator {
    public:
        void evaluateQuery(QueryStruct& query);
    };
}

#endif // QUERYEVALUATOR_H