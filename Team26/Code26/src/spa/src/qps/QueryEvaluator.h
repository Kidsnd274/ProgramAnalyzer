#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H

#include "Query.h"

class QueryEvaluator {
public:
    static void evaluate(Query* query);
    static void getAllEntity(Argument argument, QPS::ResultTable* resultTable);
    static void changeToAttrName(Query* query, QPS::ResultTable* resultTable);
    static std::string getAttrName(std::string value, Query::CandidateStruct candidate);

    // For optimization
    static std::vector<Clause*>* groupClauses(std::vector<Clause*>* clauseList);
    static int calcHeuristic(Clause& clause);
    static int numOfSynonyms(Clause& clause);
};

class UnionFindDisjointSet {
private:
    int numOfElements;
    int numOfGroups;
    int* parent;
    int* rank;

public:
    UnionFindDisjointSet(int numOfElements) {
        this->numOfElements = numOfElements;
        this->parent = new int[numOfElements];
        this->rank = new int[numOfElements];
    }

    ~UnionFindDisjointSet() {
        delete[] this->parent;
        delete[] this->rank;
    }

    void initialize() {
        this->numOfGroups = -1;
        for (int i = 0; i < this->numOfElements; i++) {
            this->parent[i] = i;
            this->rank[i] = 0;
        }
    }

    int find(int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }

    void merge(int u, int v) {
        int fu = find(u);
        int fv = find(v);
        if (rank[fu] < rank[fv]) {
            parent[fu] = fv;
            return;
        }
        if (rank[fu] > rank[fv]) {
            parent[fv] = fu;
            return;
        }
        parent[fv] = fu;
        rank[fu] += 1;
    }

    int getNumberOfGroups() {
        if (this->numOfGroups != -1) {
            return this->numOfGroups;
        }
        this->numOfGroups = 0;
        for (int i = 0; i < this->numOfElements; i++) {
            if (parent[i] == i) {
                this->numOfGroups += 1;
            }
        }
        return this->numOfGroups;
    }
};
#endif //SPA_QUERYEVALUATOR_H
