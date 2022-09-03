#include "QueryProcessorTypes.h"
#include "QueryStruct.h"
#include<string>
#include<map>
#include<vector>

QueryStruct::QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP &declaredSynonymMap,
                         QueryProcessorTypes::SUCH_THAT_LIST &suchThatList,
                         QueryProcessorTypes::PATTERN_LIST &patternList,
                         QueryProcessorTypes::CANDIDATE_LIST &candidateList) :
        declaredSynonymMap(declaredSynonymMap),
        suchThatList(suchThatList),
        patternList(patternList),
        candidateList(candidateList) {}

QueryStruct::QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP &declaredSynonymMap,
                         QueryProcessorTypes::SUCH_THAT_LIST &suchThatList,
                         QueryProcessorTypes::CANDIDATE_LIST &candidateList) :
        declaredSynonymMap(declaredSynonymMap),
        suchThatList(suchThatList),
        candidateList(candidateList) {}

QueryStruct::QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP &declaredSynonymMap,
                         QueryProcessorTypes::PATTERN_LIST &patternList,
                         QueryProcessorTypes::CANDIDATE_LIST &candidateList) :
        declaredSynonymMap(declaredSynonymMap),
        patternList(patternList),
        candidateList(candidateList) {}

QueryStruct::QueryStruct() {
    this->declaredSynonymMap = QueryProcessorTypes::DECLARED_SYNONYM_MAP();
    this->suchThatList = QueryProcessorTypes::SUCH_THAT_LIST();
    this->patternList = QueryProcessorTypes::PATTERN_LIST();
    this->candidateList = QueryProcessorTypes::CANDIDATE_LIST();
}

QueryProcessorTypes::DECLARED_SYNONYM_MAP QueryStruct::getDeclaredSynonymMap() {
    return this->declaredSynonymMap;
}

QueryProcessorTypes::SUCH_THAT_LIST QueryStruct::getSuchThatList() {
    return this->suchThatList;
}

QueryProcessorTypes::PATTERN_LIST QueryStruct::getPatternList() {
    return this->patternList;
}

QueryProcessorTypes::CANDIDATE_LIST QueryStruct::getCandidateList() {
    return this->candidateList;
}

void QueryStruct::addSynonym(QueryProcessorTypes::EntityType entityType, std::string nameOfEntity) {
    if (this->declaredSynonymMap.find(nameOfEntity) != this->declaredSynonymMap.end()) {
        if (this->declaredSynonymMap.find(nameOfEntity)->second != entityType) {
            this->queryStatus = QueryStruct::EVALUATION_ERROR;
            throw std::invalid_argument("QueryStruct::addSynonym: Synonym "
            + nameOfEntity
            + "already exists and the type is different.");
        }
    } else {
        this->declaredSynonymMap.insert(std::make_pair(nameOfEntity, entityType));
    }
}

void QueryStruct::addSuchThatClause(QueryProcessorTypes::RelationStruct relationToAdd) {
    this->suchThatList.emplace_back(relationToAdd);
}

void QueryStruct::addPatternClause(QueryProcessorTypes::PatternStruct patternToAdd) {
    this->patternList.emplace_back(patternToAdd);
}

void QueryStruct::addCandidate(QueryProcessorTypes::CandidateStruct candidateToAdd) {
    this->candidateList.emplace_back(candidateToAdd);
}

//int main() {
//    return 0;
//}