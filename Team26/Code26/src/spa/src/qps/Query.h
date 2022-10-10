#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "ResultTable.h"
#include "type/Clause.h"

enum QueryStatus {
    VALID_QUERY,
    SYNTAX_ERROR,
    SEMANTIC_ERROR
};

class Query {
private:
    unordered_map<std::string, Argument>* synonymMap;
    unordered_map<std::string, Argument>* candidateMap;
    std::vector<Clause>* clauseList;
    QueryStatus status;

public:
    Query() {
        this->synonymMap = new unordered_map<std::string, Argument>();
        this->candidateMap = new unordered_map<std::string, Argument>();
    }

    void addSynonym(Argument synonym);

    void addCandidate(Argument synonym);

    void addClause(Clause clause);

    void validate();

    void setStatus(QueryStatus);

    QueryStatus getStatus();
};


#endif //SPA_QUERY_H
