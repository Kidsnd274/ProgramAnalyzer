#include "Query.h"

void Query::addSynonym(Argument synonym) {
    auto iter = this->synonymMap->find(synonym.argumentName);
    if (iter != this->synonymMap->end()) {
        setStatus(SYNTAX_ERROR);
    } else {
        this->synonymMap->insert(make_pair(synonym.argumentName, synonym));
    }
}

void Query::addCandidate(Argument candidate) {
    auto iter = this->candidateMap->find(candidate.argumentName);
    if (iter != this->candidateMap->end()) {
        setStatus(SYNTAX_ERROR);
    } else {
        this->candidateMap->insert(make_pair(candidate.argumentName, candidate));
    }
}

void Query::addClause(Clause clause) {
    this->clauseList->push_back(clause);
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