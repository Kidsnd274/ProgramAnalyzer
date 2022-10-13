#ifndef SPA_RELATIONCLAUSEEVALUATOR_H
#define SPA_RELATIONCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"
#include "../type/RelationClause.h"
std::unordered_map<std::string, ::RelationType> evaluatorRelationMap = {

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
    void filterRelations(unordered_map<string, vector<string>> map, QPS::ResultTable *resultTable);
    void filterRelations(unordered_map<int, vector<int>> map, QPS::ResultTable *resultTable);
    void filterRelations(unordered_map<int, vector<string>> map, QPS::ResultTable *resultTable);
    void filterRelations(unordered_map<int, int> map, QPS::ResultTable *resultTable);
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
