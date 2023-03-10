#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H

#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "Query.h"

struct ClauseStruct {
    Clause* clause;
    QPS::ResultTable* resultTable;
    int groupNumber;
};

class QueryEvaluator {
public:
    static void evaluate(Query* query);
    static void getAllEntity(Argument argument, QPS::ResultTable* resultTable);
    static void changeToAttrName(Query* query, QPS::ResultTable* resultTable);
    static std::string getAttrName(std::string value, ArgAttrStruct candidate);

    // For optimization
    static void groupClauses(int n, ClauseStruct* clauseStruct);
    static int calcHeuristic(Clause& clause);
    static int numOfSynonyms(Clause& clause);
    static std::unordered_map<std::string, int> countSynonym(Query* query);
    static void removeSynonym(Clause& clause, std::unordered_map<std::string, int>* synonymCount,
                              QPS::ResultTable* resultTable);
};

class UnionFindDisjointSet {
private:
    int numOfElements;
    int numOfGroups;
    int* parent;
    int* rank;

public:
    explicit UnionFindDisjointSet(int numOfElements) {
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
#endif  // SPA_QUERYEVALUATOR_H
