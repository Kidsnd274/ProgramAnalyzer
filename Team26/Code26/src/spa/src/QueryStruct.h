#ifndef QUERYSTRUCT_H
#define QUERYSTRUCT_H

#include "QueryProcessorTypes.h"
#include<string>

/*
 * The data structure to represent the input query string.
 * After parsing, all information about the query will be stored in this QueryStruct data structure.
 */
class QueryStruct {
private:
    DECLARED_SYNONYM_MAP declaredSynonymMap;
    SUCH_THAT_LIST suchThatList;
    PATTERN_LIST patternList;
    CANDIDATE_LIST candidateList;

    QueryStruct(DECLARED_SYNONYM_MAP& declaredSynonymMap,
                SUCH_THAT_LIST& suchThatList,
                PATTERN_LIST& patternList,
                CANDIDATE_LIST& candidateList);

    QueryStruct(DECLARED_SYNONYM_MAP& declaredSynonymMap,
                SUCH_THAT_LIST& suchThatList,
                CANDIDATE_LIST& candidateList);

    QueryStruct(DECLARED_SYNONYM_MAP& declaredSynonymMap,
                PATTERN_LIST& patternList,
                CANDIDATE_LIST& candidateList);
};

#endif