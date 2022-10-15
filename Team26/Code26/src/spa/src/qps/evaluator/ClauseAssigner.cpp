#include "ClauseAssigner.h"

void ClauseAssigner::assignClause(QPS::ResultTable *resultTable, Clause *clause) {
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
            break;
        }
    }
}