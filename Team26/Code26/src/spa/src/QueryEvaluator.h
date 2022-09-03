#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include "QueryProcessorTypes.h"
#include "QueryStruct.h"
namespace QPS {
    class BasicQueryEvaluator {
    public:
        void evaluateQuery(QueryStruct);
    };
}

#endif // QUERYEVALUATOR_H