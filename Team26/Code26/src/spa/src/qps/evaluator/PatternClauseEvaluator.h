#ifndef SPA_PATTERNCLAUSEEVALUATOR_H
#define SPA_PATTERNCLAUSEEVALUATOR_H

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include "ClauseEvaluator.h"
#include "../type/PatternClause.h"
#include "../../sp/SourceProcessor.h"

class PatternClauseEvaluator : public ClauseEvaluator{
private:
    PatternClause* patternClause;
public:
    void evaluate(ResultTable* resultTable);
    void evaluateContainer(ResultTable* resultTable);

    WildcardPosition getWildcardPosition();

    std::shared_ptr<TNode> getPatternNode(WildcardPosition pos);

    explicit PatternClauseEvaluator(Clause* clause): ClauseEvaluator(clause){
        this->patternClause = reinterpret_cast<PatternClause*>(clause);
    }
};

#endif  // SPA_PATTERNCLAUSEEVALUATOR_H
