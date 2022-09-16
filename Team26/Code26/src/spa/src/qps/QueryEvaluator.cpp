#include "QueryProcessorTypes.h"
#include "QueryStruct.h"
#include "QueryEvaluator.h"
#include "QueryManager.h"
#include <iostream>

namespace QPS {
    void BasicQueryEvaluator::evaluateQuery(QueryStruct& query) {
        query.generateUsedSynonymList();
        if (query.queryStatus == QPS::SYNTAX_ERROR || query.queryStatus == QPS::SEMANTIC_ERROR) {
            return;
        }
        for (auto iter : query.getDeclaredSynonymMap()) {
            if (!query.isSynonymUsed(iter.first)) {
                continue;
            }
            QPS::EntityStruct entityStruct = {
                    iter.second,
                    iter.first
            };
            std::vector<std::string> entities = QueryManager::getAllEntitiesFromPKB(entityStruct.typeOfEntity);
            std::cout << entities.size() << std::endl;
            query.resultTable.addColumnAndMerge(entityStruct.nameOfEntity, entities);
//            query.resultTable.deleteDuplicateRows({}); //duplicate if values are the same for all synonyms
            query.resultTable.filterRowsBySuchThatList(query.getSuchThatList());
            query.resultTable.filterRowsByPatternList(query.getPatternList());
            query.queryStatus = QPS::EVALUATION_COMPLETED;
        }
        query.resultTable.printTable();
    }
}