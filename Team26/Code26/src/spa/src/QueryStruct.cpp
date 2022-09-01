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

int main() {
    return 0;
}