#include "QueryProcessorTypes.h"
#include "QueryStruct.h"
#include<string>
#include<map>
#include<vector>

QueryStruct::QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP &declaredSynonymMap,
                         QueryProcessorTypes::SUCH_THAT_LIST &suchThatList,
                         QueryProcessorTypes::PATTERN_LIST &patternList,
                         QueryProcessorTypes::CANDIDATE_LIST &candidateList) {
    this->declaredSynonymMap = declaredSynonymMap;
    this->suchThatList = suchThatList;
    this->patternList = patternList;
    this->candidateList = candidateList;
}

QueryStruct::QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP &declaredSynonymMap,
                         QueryProcessorTypes::SUCH_THAT_LIST &suchThatList,
                         QueryProcessorTypes::CANDIDATE_LIST &candidateList) {
    this->declaredSynonymMap = declaredSynonymMap;
    this->suchThatList = suchThatList;
    this->candidateList = candidateList;
}

QueryStruct::QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP &declaredSynonymMap,
                         QueryProcessorTypes::PATTERN_LIST &patternList,
                         QueryProcessorTypes::CANDIDATE_LIST &candidateList) {
    this->declaredSynonymMap = declaredSynonymMap;
    this->patternList = patternList;
    this->candidateList = candidateList;
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

void QueryStruct::addSuchThatClause(QueryProcessorTypes::RelationStruct relationToAdd) {
    this->suchThatList.emplace_back(relationToAdd);
}

void QueryStruct::addPatternClause(QueryProcessorTypes::PatternStruct patternToAdd) {
    this->patternList.emplace_back(patternToAdd);
}


int main() {
    return 0;
}