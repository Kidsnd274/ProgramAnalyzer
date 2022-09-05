#include "QueryProcessorTypes.h"
#include "QueryStruct.h"
#include "QueryEvaluator.h"

namespace QPS {
    void BasicQueryEvaluator::evaluateQuery(QueryStruct& query) {
        if (query.queryStatus == QPS::EVALUATION_COMPLETED
            || query.queryStatus == QPS::EVALUATION_ERROR) {
            return;
        }
        for (auto iter : query.getDeclaredSynonymMap()) {
            QPS::EntityStruct entityStruct = {
                    iter.second,
                    iter.first
            };
            std::vector<std::string> entities = std::vector<std::string> {"a", "b", "c", "d"}; // for test only
//            std::vector<std::string> entities = PKB.getAllEntities(entityStruct.typeOfEntity); // TODO: Add method to PKB-QPS API.
            query.resultTable.addColumnAndMerge(entityStruct.nameOfEntity, entities);
            query.resultTable.filterRows(query.getSuchThatList());
        }
    }
}