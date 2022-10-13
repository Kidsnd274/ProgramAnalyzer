#ifndef SPA_CLAUSEASSIGNER_H
#define SPA_CLAUSEASSIGNER_H
#include "RelationClauseEvaluator.h"
#include "PatternClauseEvaluator.h"
#include "WithClauseEvaluator.h"
#include "../ResultTable.h"
#include "../type/Clause.h"
#include "../QPS_PKB_Interface.h"

enum ClauseType {
    Pattern,
    With,
    Relation
};
const std::map<std::string, ClauseType> clauseMap = {
        {"PatternClause", Pattern},
        {"WithClause", With},
        {"RelationClause", Relation},
};
class ClauseAssigner {
public:
    void assignClause(ResultTable* resultTable, Clause* clause);
};


#endif //SPA_CLAUSEASSIGNER_H
