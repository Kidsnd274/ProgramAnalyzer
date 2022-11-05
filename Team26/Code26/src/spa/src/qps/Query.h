#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include <typeinfo>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "ResultTable.h"
#include "type/Clause.h"
#include "type/WithClause.h"

enum QueryStatus {
    VALID_QUERY,
    SYNTAX_ERROR,
    SEMANTIC_ERROR
};

class Query {
public:
    struct CandidateStruct {
        Argument argument;
        AttributeType attributeType;
    };

private:
    std::unordered_map<std::string, Argument>* synonymMap;
    std::vector<CandidateStruct>* candidateList;
    QueryStatus status;

public:
    QPS::ResultTable* resultTable;
    std::vector<Clause*>* clauseList;

public:
    Query() {
        this->synonymMap = new std::unordered_map<std::string, Argument>();
        this->candidateList = new std::vector<CandidateStruct>;
        this->clauseList = new std::vector<Clause*>();
        this->resultTable = new QPS::ResultTable();
        this->status = VALID_QUERY;
    }

    void addSynonym(Argument& synonym);

    void addCandidate(CandidateStruct& candidate);

    void addClause(Clause* clause);

    void validate();

    void setStatus(QueryStatus);

    QueryStatus getStatus();

    Argument::ArgumentType getSynonymType(const std::string&);

    std::unordered_map<std::string, Argument>& getSynonymMap();

    std::vector<CandidateStruct>& getCandidateList();

    bool isBooleanQuery();

    std::unordered_set<std::string> getCandidates();
};


#endif //SPA_QUERY_H
