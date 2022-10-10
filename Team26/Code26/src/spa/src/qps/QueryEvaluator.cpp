#include "QueryEvaluator.h"
#include "evaluator/ClauseAssigner.h"

void QueryEvaluator::evaluate(Query query) {
    if (query.getStatus() != VALID_QUERY) {
        return;
    }

    ResultTable* resultOfEvaluation = new ResultTable();
    ClauseAssigner* clauseAssigner = new ClauseAssigner();
    for (auto iter = query.clauseList->begin(); iter != query.clauseList->end(); iter++) {
        ResultTable* resultTable = new ResultTable();
        clauseAssigner->assignClause(resultTable, &*iter);
        resultOfEvaluation->mergeTable(*resultTable);
    }

    query.resultTable = resultOfEvaluation;
}
