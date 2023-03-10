#ifndef SPA_CLAUSEASSIGNER_H
#define SPA_CLAUSEASSIGNER_H

#include <map>
#include <string>
#include "RelationClauseEvaluator.h"
#include "PatternClauseEvaluator.h"
#include "WithClauseEvaluator.h"
#include "../ResultTable.h"
#include "../type/Clause.h"
#include "../QPS_Interface.h"

enum ClauseType {
    Pattern,
    With,
    Relation
};

const std::map<std::string, ClauseType> clauseMap = {
        {typeid(PatternClause).name(), Pattern},
        {typeid(WithClause).name(), With},
        {typeid(RelationClause).name(), Relation},
};

class ClauseAssigner {
public:
    void assignClause(ResultTable* resultTable, Clause* clause);
};

#endif  // SPA_CLAUSEASSIGNER_H
