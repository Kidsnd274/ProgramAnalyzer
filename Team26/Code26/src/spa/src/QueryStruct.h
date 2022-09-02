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
    QueryProcessorTypes::DECLARED_SYNONYM_MAP declaredSynonymMap;
    QueryProcessorTypes::SUCH_THAT_LIST suchThatList;
    QueryProcessorTypes::PATTERN_LIST patternList;
    QueryProcessorTypes::CANDIDATE_LIST candidateList;


public:
    QueryStruct() = default;
    QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP& declaredSynonymMap,
                QueryProcessorTypes::SUCH_THAT_LIST& suchThatList,
                QueryProcessorTypes::PATTERN_LIST& patternList,
                QueryProcessorTypes::CANDIDATE_LIST& candidateList);

    QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP& declaredSynonymMap,
                QueryProcessorTypes::SUCH_THAT_LIST& suchThatList,
                QueryProcessorTypes::CANDIDATE_LIST& candidateList);

    QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP& declaredSynonymMap,
                QueryProcessorTypes::PATTERN_LIST& patternList,
                QueryProcessorTypes::CANDIDATE_LIST& candidateList);

    QueryProcessorTypes::DECLARED_SYNONYM_MAP getDeclaredSynonymMap();
    QueryProcessorTypes::SUCH_THAT_LIST getSuchThatList();
    QueryProcessorTypes::PATTERN_LIST getPatternList();
    QueryProcessorTypes::CANDIDATE_LIST getCandidateList();

    void addSuchThatClause(QueryProcessorTypes::RelationStruct relationToAdd);
    void addPatternClause(QueryProcessorTypes::PatternStruct patternToAdd);
};

#endif // QUERYSTRUCT_H