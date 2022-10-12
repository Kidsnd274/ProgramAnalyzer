#include "QueryEvaluator.h"
#include "evaluator/ClauseAssigner.h"

void QueryEvaluator::evaluate(Query query) {
    if (query.getStatus() != VALID_QUERY) {
        return;
    }

    ResultTable* resultOfEvaluation = new ResultTable();
    ClauseAssigner* clauseAssigner = new ClauseAssigner();

    // Relation clause and Pattern clause
    for (auto iter = query.clauseList->begin(); iter != query.clauseList->end(); iter++) {
        if (typeid(*iter) == typeid(WithClause)) {
            continue;
        }
        ResultTable* resultTable = new ResultTable();
        clauseAssigner->assignClause(resultTable, *iter);
        resultOfEvaluation->mergeTable(*resultTable);
    }

    // With clause
    for (auto iter = query.clauseList->begin(); iter != query.clauseList->end(); iter++) {
        if (typeid(*iter) != typeid(WithClause)) {
            continue;
        }
        clauseAssigner->assignClause(resultOfEvaluation, *iter);
    }
    query.resultTable = resultOfEvaluation;
}
