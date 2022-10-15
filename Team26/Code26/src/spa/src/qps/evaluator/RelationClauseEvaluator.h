#ifndef SPA_RELATIONCLAUSEEVALUATOR_H
#define SPA_RELATIONCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"
#include "../type/RelationClause.h"
#include "../QPS_PKB_Interface.h"


class RelationClauseEvaluator: public ClauseEvaluator{
public:
    const static std::unordered_map<std::string, ::RelationType> evaluatorRelationMap;

private:
    RelationClause* relationClause;
    void evaluateCalls(QPS::ResultTable *resultTable);
    void evaluateCallsT(QPS::ResultTable *resultTable);
    void evaluateAffects(QPS::ResultTable *resultTable);
    void evaluateAffectsT(QPS::ResultTable *resultTable);
    void evaluateFollows(QPS::ResultTable *resultTable);
    void evaluateFollowsT(QPS::ResultTable *resultTable);
    void evaluateModifiesS(QPS::ResultTable *resultTable);
    void evaluateModifiesP(QPS::ResultTable *resultTable);
    void evaluateNext(QPS::ResultTable *resultTable);
    void evaluateNextT(QPS::ResultTable *resultTable);
    void evaluateParent(QPS::ResultTable *resultTable);
    void evaluateParentT(QPS::ResultTable *resultTable);
    void evaluateUsesP(QPS::ResultTable *resultTable);
    void evaluateUsesS(QPS::ResultTable *resultTable);

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

    bool existInStringVector(std::string s, std::vector<std::string> v);
    bool existInIntVector(int s, std::vector<int> v);

    QPS::ResultTable* filterTable(std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> *result);
public:
    void evaluate(QPS::ResultTable* resultTable);
    RelationClauseEvaluator(Clause* clause): ClauseEvaluator(clause){
        this->relationClause = (RelationClause*)clause;
    };
};


#endif //SPA_RELATIONCLAUSEEVALUATOR_H
