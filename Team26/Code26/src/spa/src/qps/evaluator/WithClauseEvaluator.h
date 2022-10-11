#ifndef SPA_WITHCLAUSEEVALUATOR_H
#define SPA_WITHCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"
#include "../type/WithClause.h"
class WithClauseEvaluator : public ClauseEvaluator{
private:
    WithClause* withClause;
public:
    WithClauseEvaluator(Clause* clause): ClauseEvaluator(clause) {
        this->withClause = (WithClause*)clause;
    };

    void evaluate(ResultTable* resultTable);
};


#endif //SPA_WITHCLAUSEEVALUATOR_H
