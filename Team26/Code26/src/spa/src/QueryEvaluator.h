#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include "QueryProcessorTypes.h"
#include "QueryStruct.h"

class BasicQueryEvaluator {
public:
    void evaluateQuery(QueryStruct::QueryStruct);
};
#endif // QUERYEVALUATOR_H