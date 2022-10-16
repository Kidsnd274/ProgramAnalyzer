#include "Query.h"

void Query::addSynonym(Argument& synonym) {
    auto iter = this->synonymMap->find(synonym.argumentName);
    if (iter != this->synonymMap->end()) {
        setStatus(SYNTAX_ERROR);
    } else {
        this->synonymMap->insert(make_pair(synonym.argumentName, synonym));
    }
}

void Query::addCandidate(Argument& candidate) {
    this->candidateList->push_back(candidate);
}

void Query::addClause(Clause* clause) {
    this->clauseList->push_back(clause);
}

void Query::validate() {
    for (auto clause : *this->clauseList) {
        if (!clause->isValid()) {
            this->setStatus(SEMANTIC_ERROR);
        }
    }
}

void Query::setStatus(QueryStatus statusToUpdate) {
    switch (this->status) {
        case SYNTAX_ERROR: {
            return;
        }
        case SEMANTIC_ERROR: {
            if (statusToUpdate == SYNTAX_ERROR) {
                this->status = SYNTAX_ERROR;
            }
        }
        case VALID_QUERY: {
            this->status = statusToUpdate;
        }
    }
}

QueryStatus Query::getStatus() {
    return this->status;
}

Argument::ArgumentType Query::getSynonymType(const std::string& synonymName) {
    auto iter = this->synonymMap->find(synonymName);
    if (iter != this->synonymMap->end()) {
        return iter->second.argumentType;
    } else {
        return Argument::INVALID_ARGUMENT_TYPE;
    }
}

std::unordered_map<std::string, Argument>& Query::getSynonymMap() {
    return *this->synonymMap;
}

std::vector<Argument>& Query::getCandidateList() {
    return *this->candidateList;
}
