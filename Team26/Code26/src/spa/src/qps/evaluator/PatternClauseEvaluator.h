#ifndef SPA_PATTERNCLAUSEEVALUATOR_H
#define SPA_PATTERNCLAUSEEVALUATOR_H
#include "ClauseEvaluator.h"
#include "../type/PatternClause.h"

class PatternClauseEvaluator : public ClauseEvaluator{
public:

    void evaluate(ResultTable* resultTable) {

    }
    PatternClauseEvaluator(Clause* clause): ClauseEvaluator(clause){};
};


#endif //SPA_PATTERNCLAUSEEVALUATOR_H
