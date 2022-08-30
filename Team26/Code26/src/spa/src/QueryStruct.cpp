#include "QueryProcessorTypes.h"
#include "QueryStruct.h"
#include<string>
#include<map>
#include<vector>

QueryStruct::QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                         SUCH_THAT_LIST &suchThatList,
                         PATTERN_LIST &patternList,
                         CANDIDATE_LIST &candidateList) {
    this->declaredSynonymMap = declaredSynonymMap;
    this->suchThatList = suchThatList;
    this->patternList = patternList;
    this->candidateList = candidateList;
}

QueryStruct::QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                         SUCH_THAT_LIST &suchThatList,
                         CANDIDATE_LIST &candidateList) {
    this->declaredSynonymMap = declaredSynonymMap;
    this->suchThatList = suchThatList;
    this->candidateList = candidateList;
}

QueryStruct::QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                         PATTERN_LIST &patternList,
                         CANDIDATE_LIST &candidateList) {
    this->declaredSynonymMap = declaredSynonymMap;
    this->patternList = patternList;
    this->candidateList = candidateList;
}
