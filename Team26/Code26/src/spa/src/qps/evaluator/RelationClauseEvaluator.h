#ifndef SPA_RELATIONCLAUSEEVALUATOR_H
#define SPA_RELATIONCLAUSEEVALUATOR_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "ClauseEvaluator.h"
#include "../type/RelationClause.h"
#include "../QPS_Interface.h"

class RelationClauseEvaluator: public ClauseEvaluator{
private:
    RelationClause* relationClause;
    void evaluateAffects(QPS::ResultTable *resultTable);
    void evaluateAffectsT(QPS::ResultTable *resultTable);
    void evaluateFollowsT(QPS::ResultTable *resultTable);
    void evaluateNext(QPS::ResultTable *resultTable);
    void evaluateNextT(QPS::ResultTable *resultTable);

    /**
     * Handles whether to call evaluateUsesP or evaluateUsesS.
     * @param resultTable the result table used to store the result.
     */
    void evaluateUse(QPS::ResultTable *resultTable);

    /**
     * Handles whether to call modifiesP or modifiesS.
     * @param resultTable the result table used to store the result.
     */
    void evaluateModify(QPS::ResultTable *resultTable);
    /**
     *  Used by Uses_P and Modifies_P to filter out relationships.
     * @param map map retrieved from PKB.
     * @param resultTable the result table used to store the result.
     */
    void filterRelations(std::unordered_map<std::string, std::vector<std::string>> map, QPS::ResultTable *resultTable);

    /**
     * Used by Parent and Parent_T to filter out relationships.
     * @param map map retrieved from PKB.
     * @param resultTable the result table used to store the result.
     */
    void filterRelations(std::unordered_map<int, std::vector<int>> map, QPS::ResultTable *resultTable);

    /**
     * Used by Modifies and Uses to filter out relationships.
     * @param map map retrieved from PKB.
     * @param resultTable the result table used to store the result.
     */
    void filterRelations(std::unordered_map<int, std::vector<std::string>> map, QPS::ResultTable *resultTable);

    void filterRelations(std::unordered_map<int, int> map, QPS::ResultTable* resultTable);

    bool existInStringVector(std::string s, std::vector<std::string> v);
    bool existInIntVector(int s, std::vector<int> v);

    bool validateAffectsParameter(QPS::ResultTable* resultTable);

    QPS::ResultTable* filterTable(std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> *result);

public:
    void evaluate(QPS::ResultTable* resultTable);
    explicit RelationClauseEvaluator(Clause* clause): ClauseEvaluator(clause){
        this->relationClause = reinterpret_cast<RelationClause*>(clause);
    }
};

#endif  // SPA_RELATIONCLAUSEEVALUATOR_H
