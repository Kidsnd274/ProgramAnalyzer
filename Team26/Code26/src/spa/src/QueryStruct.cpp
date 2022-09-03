#include "QueryStruct.h"

namespace QPS {
    QueryStruct::QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                             SUCH_THAT_LIST &suchThatList,
                             PATTERN_LIST &patternList,
                             CANDIDATE_LIST &candidateList) :
            declaredSynonymMap(declaredSynonymMap),
            suchThatList(suchThatList),
            patternList(patternList),
            candidateList(candidateList) {}

    QueryStruct::QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                             SUCH_THAT_LIST &suchThatList,
                             CANDIDATE_LIST &candidateList) :
            declaredSynonymMap(declaredSynonymMap),
            suchThatList(suchThatList),
            candidateList(candidateList) {}

    QueryStruct::QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                             PATTERN_LIST &patternList,
                             CANDIDATE_LIST &candidateList) :
            declaredSynonymMap(declaredSynonymMap),
            patternList(patternList),
            candidateList(candidateList) {}

    QueryStruct::QueryStruct() {
        this->declaredSynonymMap = DECLARED_SYNONYM_MAP();
        this->suchThatList = SUCH_THAT_LIST();
        this->patternList = PATTERN_LIST();
        this->candidateList = CANDIDATE_LIST();
    }

    DECLARED_SYNONYM_MAP QueryStruct::getDeclaredSynonymMap() {
        return this->declaredSynonymMap;
    }

    SUCH_THAT_LIST QueryStruct::getSuchThatList() {
        return this->suchThatList;
    }

    PATTERN_LIST QueryStruct::getPatternList() {
        return this->patternList;
    }

    CANDIDATE_LIST QueryStruct::getCandidateList() {
        return this->candidateList;
    }

    void QueryStruct::addSynonym(EntityType entityType, std::string nameOfEntity) {
        if (this->declaredSynonymMap.find(nameOfEntity) != this->declaredSynonymMap.end()) {
            if (this->declaredSynonymMap.find(nameOfEntity)->second != entityType) {
                this->queryStatus = EVALUATION_ERROR;
                throw std::invalid_argument("QueryStruct::addSynonym: Synonym "
                                            + nameOfEntity
                                            + "already exists and the type is different.");
            }
        } else {
            this->declaredSynonymMap.insert(std::make_pair(nameOfEntity, entityType));
        }
    }

    void QueryStruct::addSuchThatClause(RelationStruct relationToAdd) {
        this->suchThatList.emplace_back(relationToAdd);
    }

    void QueryStruct::addPatternClause(PatternStruct patternToAdd) {
        this->patternList.emplace_back(patternToAdd);
    }

    void QueryStruct::addCandidate(CandidateStruct candidateToAdd) {
        this->candidateList.emplace_back(candidateToAdd);
    }
}

int main() {
    return 0;
}