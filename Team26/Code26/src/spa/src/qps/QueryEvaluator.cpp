#include "QueryEvaluator.h"
#include "evaluator/ClauseAssigner.h"

void QueryEvaluator::evaluate(Query* query) {
    if (query->getStatus() != VALID_QUERY) {
        return;
    }

    ResultTable* resultOfEvaluation = new ResultTable();
    ClauseAssigner* clauseAssigner = new ClauseAssigner();

    // Relation clause and Pattern clause
    for (auto iter = query->clauseList->begin(); iter != query->clauseList->end(); iter++) {
        if (typeid(*iter) == typeid(WithClause)) {
            continue;
        }
        ResultTable* resultTable = new ResultTable();
        clauseAssigner->assignClause(resultTable, *iter);
        resultOfEvaluation = ResultTable::mergeTable(resultOfEvaluation, resultTable);
//        resultOfEvaluation->mergeTable(*resultTable);
    }

    // With clause
    for (auto iter = query->clauseList->begin(); iter != query->clauseList->end(); iter++) {
        if (typeid(*iter) != typeid(WithClause)) {
            continue;
        }
        clauseAssigner->assignClause(resultOfEvaluation, *iter);
    }

    // Merge with synonyms to be selected
    for (auto s: query->getCandidateList()) {
        if (!resultOfEvaluation->isSynonymPresent(s.argumentName)) {
            getAllEntity(s, resultOfEvaluation);
        }
    }


    query->resultTable = resultOfEvaluation;
}

void QueryEvaluator::getAllEntity(Argument argument, QPS::ResultTable *resultTable) {
    vector<string> synonym = {argument.argumentName};
    unordered_set<vector<string>, StringVectorHash> results;
    vector<string> entities = QPS_PKB_Interface::getAllEntity(&argument);
    for (auto e: entities) {
        results.insert({e});
    }
    ResultTable* entityTable = new ResultTable(synonym, results);
    resultTable->mergeTable(*entityTable);
}
