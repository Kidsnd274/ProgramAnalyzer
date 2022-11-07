#ifndef SPA_CLAUSEEVALUATOR_H
#define SPA_CLAUSEEVALUATOR_H

#include "../ResultTable.h"
#include "../type/Clause.h"
#include "../QPS_Interface.h"

class ClauseEvaluator {
private:
    Clause* clause;

public:
    virtual void evaluate(QPS::ResultTable* resultTable);
    explicit ClauseEvaluator(Clause* clause);
};

#endif  // SPA_CLAUSEEVALUATOR_H
