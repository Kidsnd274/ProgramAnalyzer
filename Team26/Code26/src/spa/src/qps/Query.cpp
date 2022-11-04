#include "Query.h"

void Query::addSynonym(Argument& synonym) {
    auto iter = this->synonymMap->find(synonym.argumentName);
    if (iter != this->synonymMap->end()) {
        setStatus(SYNTAX_ERROR);
    } else {
        this->synonymMap->insert(make_pair(synonym.argumentName, synonym));
    }
}

void Query::addCandidate(Query::CandidateStruct &candidate) {
    this->candidateList->push_back(candidate);
}

void Query::addClause(Clause* clause) {
    this->clauseList->push_back(clause);
}

void Query::validate() {
    for (auto clause : *this->clauseList) {
        if (!clause->isValid()) {
            if (typeid(*clause) == typeid(WithClause)) {
                this->setStatus(SYNTAX_ERROR);
            } else {
                this->setStatus(SEMANTIC_ERROR);
            }
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

std::vector<Query::CandidateStruct>& Query::getCandidateList() {
    return *this->candidateList;
}

bool Query::isBooleanQuery() {
    if (this->candidateList->size() == 1) {
        CandidateStruct candidate = this->candidateList->at(0);
        if (candidate.argument.argumentType == Argument::BOOLEAN_ARG) {
            return true;
        }
    }
    return false;
}

std::unordered_set<std::string> Query::getCandidates() {
    std::unordered_set<std::string> candidates;
    for (auto c: *this->candidateList) {
        if (Argument::isSynonym(c.argument.argumentType)) {
            candidates.insert(c.argument.argumentName);
        }
    }
    return candidates;
}