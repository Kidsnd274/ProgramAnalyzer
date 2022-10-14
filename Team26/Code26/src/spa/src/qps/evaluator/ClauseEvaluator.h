#ifndef SPA_CLAUSEEVALUATOR_H
#define SPA_CLAUSEEVALUATOR_H

#include "../ResultTable.h"
#include "../type/Clause.h"
#include "../QPS_PKB_Interface.h"

class ClauseEvaluator {
private:
    Clause* clause;
public:
    virtual void evaluate(QPS::ResultTable* resultTable);
    ClauseEvaluator(Clause* clause);
};


#endif //SPA_CLAUSEEVALUATOR_H
