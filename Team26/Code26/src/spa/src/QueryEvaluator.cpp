#include "QueryProcessorTypes.h"
#include "QueryStruct.h"
#include "QueryEvaluator.h"

void BasicQueryEvaluator::evaluateQuery(QueryStruct query) {
    if (query.queryStatus == QueryStruct::EVALUATION_COMPLETED
    || query.queryStatus == QueryStruct::EVALUATION_ERROR) {
        return;
    }
    QueryProcessorTypes::DECLARED_SYNONYM_MAP::iterator iter;
    for (iter = query.declaredSynonymMap.begin(); iter != query.declaredSynonymMap.end(); iter++) {
        QueryProcessorTypes::EntityStruct entityStruct = {
                iter->second,
                iter->first
        };
        std::vector<std::string> entities = PKB.getAllEntities(entityStruct);

    }
}