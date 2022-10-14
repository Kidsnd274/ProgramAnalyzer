#ifndef SPA_RELATIONCLAUSEEVALUATOR_H
#define SPA_RELATIONCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"
#include "../type/RelationClause.h"
std::unordered_map<std::string, ::RelationType> evaluatorRelationMap = {
        {"Follows", ::RelationType::FOLLOWS},    // Follows(stmtRef, stmtRef)
        {"FollowStar", ::RelationType::FOLLOWS_T},  // Follows*(stmtRef, stmtRef)
        {"Parent", ::RelationType::PARENT}, // Parent(stmtRef, stmtRef)
        {"ParentStar", ::RelationType::PARENT_T},   // Parent*(stmtRef, stmtRef)
        {"Uses", ::RelationType::USES_S},
        {"Modifies", ::RelationType::MODIFIES_S},
        {"Calls", ::RelationType::CALLS},
        {"CallsStar", ::RelationType::CALLS_T},
        {"Next", ::RelationType::NEXT},
        {"NextStar", ::RelationType::NEXT_T},
        {"Affects", ::RelationType::AFFECTS},
        {"AffectsStar", ::RelationType::AFFECTS_T},
};

class RelationClauseEvaluator: public ClauseEvaluator{
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
    void filterRelations(unordered_map<string, vector<string>> map, QPS::ResultTable *resultTable);

    /**
     * Used by Parent and Parent_T to filter out relationships.
     * @param map map retrieved from PKB.
     * @param resultTable the result table used to store the result.
     */
    void filterRelations(unordered_map<int, vector<int>> map, QPS::ResultTable *resultTable);

    /**
     * Used by Modifies and Uses to filter out relationships.
     * @param map map retrieved from PKB.
     * @param resultTable the result table used to store the result.
     */
    void filterRelations(unordered_map<int, vector<string>> map, QPS::ResultTable *resultTable);

    bool existInStringVector(string s, vector<string> v);
    bool existInIntVector(int s, vector<int> v);

    ResultTable* filterTable(unordered_set<vector<string>, StringVectorHash> *result);
public:
    void evaluate(ResultTable* resultTable);
    RelationClauseEvaluator(Clause* clause): ClauseEvaluator(clause){
        this->relationClause = (RelationClause*)clause;
    };
};


#endif //SPA_RELATIONCLAUSEEVALUATOR_H
