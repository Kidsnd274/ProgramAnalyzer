#ifndef SPA_WITHCLAUSEEVALUATOR_H
#define SPA_WITHCLAUSEEVALUATOR_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "ClauseEvaluator.h"
#include "../type/WithClause.h"

class WithClauseEvaluator : public ClauseEvaluator{
private:
    WithClause* withClause;
public:
    explicit WithClauseEvaluator(Clause* clause): ClauseEvaluator(clause) {
        this->withClause = reinterpret_cast<WithClause*>(clause);
    }

    void evaluate(QPS::ResultTable* resultTable) override;
};


#endif  // SPA_WITHCLAUSEEVALUATOR_H
