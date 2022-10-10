#include "ClauseAssigner.h"

void ClauseAssigner::assignClause(QPS::ResultTable *resultTable, Clause *clause) {
    ClauseEvaluator evaluator = ClauseEvaluator(clause);
    switch (clauseMap.find(typeid(clause).name())->second) {
        case (Pattern): {
            evaluator = PatternClauseEvaluator(clause);
            break;
        }
        case (Relation): {
            evaluator = RelationClauseEvaluator(clause);
            break;
        }
        case (With): {
            evaluator = WithClauseEvaluator(clause);
            break;
        }
        default: {
            break;
        }
    }
    evaluator.evaluate(resultTable);
}