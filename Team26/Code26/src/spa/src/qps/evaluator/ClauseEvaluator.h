#ifndef SPA_CLAUSEEVALUATOR_H
#define SPA_CLAUSEEVALUATOR_H

#include "../ResultTable.h"
#include "../type/Clause.h"

class ClauseEvaluator {
private:
    Clause* clause;
public:
    virtual void evaluate(ResultTable* resultTable);
    ClauseEvaluator(Clause* clause);
};


#endif //SPA_CLAUSEEVALUATOR_H
