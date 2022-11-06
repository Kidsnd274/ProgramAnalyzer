#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "ResultTable.h"
#include "type/Clause.h"
#include "type/WithClause.h"

enum QueryStatus {
    VALID_QUERY,
    SYNTAX_ERROR,
    SEMANTIC_ERROR
};

class Query {
private:
    std::unordered_map<std::string, Argument>* synonymMap;
    std::vector<ArgAttrStruct>* candidateList;
    QueryStatus status;

public:
    QPS::ResultTable* resultTable;
    std::vector<Clause*>* clauseList;

public:
    Query() {
        this->synonymMap = new std::unordered_map<std::string, Argument>();
        this->candidateList = new std::vector<ArgAttrStruct>;
        this->clauseList = new std::vector<Clause*>();
        this->resultTable = new QPS::ResultTable();
        this->status = VALID_QUERY;
    }

    void addSynonym(Argument& synonym);

    void addCandidate(ArgAttrStruct& candidate);

    void addClause(Clause* clause);

    void validate();

    void setStatus(QueryStatus);

    QueryStatus getStatus();

    Argument::ArgumentType getSynonymType(const std::string&);

    std::unordered_map<std::string, Argument>& getSynonymMap();

    std::vector<ArgAttrStruct>& getCandidateList();

    bool isBooleanQuery();

    std::unordered_set<std::string> getCandidates();
};


#endif //SPA_QUERY_H
