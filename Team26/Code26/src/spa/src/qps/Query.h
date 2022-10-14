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
    std::unordered_map<std::string, Argument>* synonymMap;
    std::unordered_map<std::string, Argument>* candidateMap;
    QueryStatus status;

public:
    QPS::ResultTable* resultTable;
    std::vector<Clause*>* clauseList;

public:
    Query() {
        this->synonymMap = new std::unordered_map<std::string, Argument>();
        this->candidateMap = new std::unordered_map<std::string, Argument>();
        this->clauseList = new std::vector<Clause*>();
        this->resultTable = new QPS::ResultTable();
        this->status = VALID_QUERY;
    }

    ~Query() {
        delete this->synonymMap;
        delete this->candidateMap;
        delete this->clauseList;
        delete this->resultTable;
    }

    void addSynonym(Argument& synonym);

    void addCandidate(Argument& synonym);

    void addClause(Clause* clause);

    void validate();

    void setStatus(QueryStatus);

    QueryStatus getStatus();

    Argument::ArgumentType getSynonymType(const std::string&);

    std::unordered_map<std::string, Argument>& getSynonymMap();

    std::unordered_map<std::string, Argument>& getCandidateMap();
};


#endif //SPA_QUERY_H
