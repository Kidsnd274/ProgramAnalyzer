#include "ClauseAssigner.h"

void ClauseAssigner::assignClause(QPS::ResultTable *resultTable, Clause *clause) {

    if (clauseMap.find(typeid(*clause).name()) != clauseMap.end()) {
        switch (clauseMap.find(typeid(*clause).name())->second) {
            case (Pattern): {
                PatternClauseEvaluator evaluator = PatternClauseEvaluator(clause);
                evaluator.evaluate(resultTable);
                break;
            }
            case (Relation): {
                RelationClauseEvaluator evaluator = RelationClauseEvaluator(clause);
                evaluator.evaluate(resultTable);
                break;
            }
            case (With): {
                WithClauseEvaluator evaluator = WithClauseEvaluator(clause);
                evaluator.evaluate(resultTable);
                break;
            }
            default: {
                RelationClauseEvaluator evaluator = RelationClauseEvaluator(clause);
                evaluator.evaluate(resultTable);
                break;
            }
        }
        return;
    }
    RelationClauseEvaluator evaluator = RelationClauseEvaluator(clause);
    evaluator.evaluate(resultTable);
}