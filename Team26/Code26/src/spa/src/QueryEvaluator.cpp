#include "QueryProcessorTypes.h"
#include "QueryStruct.h"
#include "QueryEvaluator.h"

namespace QPS {
    void BasicQueryEvaluator::evaluateQuery(QueryStruct query) {
        if (query.queryStatus == QPS::EVALUATION_COMPLETED
            || query.queryStatus == QPS::EVALUATION_ERROR) {
            return;
        }
        QPS::DECLARED_SYNONYM_MAP::iterator iter;
        for (iter = query.getDeclaredSynonymMap().begin(); iter != query.getDeclaredSynonymMap().end(); iter++) {
            QPS::EntityStruct entityStruct = {
                    iter->second,
                    iter->first
            };
            std::vector<std::string> entities = PKB.getAllEntities(entityStruct); // TODO: Add method to PKB-QPS API.
            query.resultTable.AddColumnAndMerge(iter->first, entities);
            query.resultTable.filterRows(query.getSuchThatList());
        }
    }
}