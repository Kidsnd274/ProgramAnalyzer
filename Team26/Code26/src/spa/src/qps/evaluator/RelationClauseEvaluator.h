#ifndef SPA_RELATIONCLAUSEEVALUATOR_H
#define SPA_RELATIONCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"
#include "../type/RelationClause.h"
class RelationClauseEvaluator: public ClauseEvaluator{
public:
    void evaluate(ResultTable* resultTable) {

    }
    RelationClauseEvaluator(Clause* clause): ClauseEvaluator(clause){};
};


#endif //SPA_RELATIONCLAUSEEVALUATOR_H
