#ifndef SPA_PATTERNCLAUSEEVALUATOR_H
#define SPA_PATTERNCLAUSEEVALUATOR_H
#include "ClauseEvaluator.h"
#include "../type/PatternClause.h"
#include "../../sp/SourceProcessor.h"

class PatternClauseEvaluator : public ClauseEvaluator{
private:
    PatternClause* patternClause;
public:
    void evaluate(ResultTable* resultTable);

    WildcardPosition getWildcardPosition();

    shared_ptr<TNode> getPatternNode(WildcardPosition pos);

    PatternClauseEvaluator(Clause* clause): ClauseEvaluator(clause){
        this->patternClause = (PatternClause*) clause;
    };
};


#endif //SPA_PATTERNCLAUSEEVALUATOR_H
