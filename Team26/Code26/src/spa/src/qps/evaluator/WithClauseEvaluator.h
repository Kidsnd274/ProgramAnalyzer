#ifndef SPA_WITHCLAUSEEVALUATOR_H
#define SPA_WITHCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"
#include "../type/WithClause.h"
class WithClauseEvaluator : public ClauseEvaluator{
public:
    void evaluate(ResultTable* resultTable) {

    }
    WithClauseEvaluator(Clause* clause): ClauseEvaluator(clause){};
};


#endif //SPA_WITHCLAUSEEVALUATOR_H
