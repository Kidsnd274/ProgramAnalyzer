#include "QueryEvaluator.h"
#include "evaluator/ClauseAssigner.h"

void QueryEvaluator::evaluate(Query* query) {
    if (query->getStatus() != VALID_QUERY) {
        return;
    }

    ResultTable* resultOfEvaluation = new ResultTable();
    ClauseAssigner* clauseAssigner = new ClauseAssigner();

    // Evaluate the clauses
    for (auto iter = query->clauseList->begin(); iter != query->clauseList->end(); iter++) {
        ResultTable* resultTable = new ResultTable();
        clauseAssigner->assignClause(resultTable, *iter);
        resultOfEvaluation = ResultTable::mergeTable(resultOfEvaluation, resultTable);
    }

    query->resultTable = resultOfEvaluation;
}

void QueryEvaluator::getAllEntity(Argument argument, QPS::ResultTable *resultTable) {
    vector<string> synonym = {argument.argumentName};
    unordered_set<vector<string>, StringVectorHash> results;
    vector<string> entities = QPS_Interface::getAllEntity(&argument);
    for (auto e: entities) {
        results.insert({e});
    }
    ResultTable* entityTable = new ResultTable(synonym, results);
    resultTable->mergeTable(*entityTable);
}

void QueryEvaluator::groupClauses(std::vector<Clause*>* clauseList) {

}