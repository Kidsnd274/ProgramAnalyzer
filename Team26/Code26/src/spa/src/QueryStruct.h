#ifndef QUERYSTRUCT_H
#define QUERYSTRUCT_H

#include "QueryProcessorTypes.h"
#include "ResultTable.h"
#include<string>
#include<vector>
#include<map>

/*
 * The data structure to represent the input query string.
 * After parsing, all information about the query will be stored in this QueryStruct data structure.
 */
class QueryStruct {
public:
    static enum QueryStatus {
        EVALUATION_NOT_STARTED,
        EVALUATION_COMPLETED,
        EVALUATION_ERROR
    };

public:
    QueryProcessorTypes::DECLARED_SYNONYM_MAP declaredSynonymMap;
    QueryProcessorTypes::SUCH_THAT_LIST suchThatList;
    QueryProcessorTypes::PATTERN_LIST patternList;
    QueryProcessorTypes::CANDIDATE_LIST candidateList;
    QueryStatus queryStatus;
    pql::ResultTable resultTable;

public:
    QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP &declaredSynonymMap,
                QueryProcessorTypes::SUCH_THAT_LIST &suchThatList,
                QueryProcessorTypes::PATTERN_LIST &patternList,
                QueryProcessorTypes::CANDIDATE_LIST &candidateList);

    QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP &declaredSynonymMap,
                QueryProcessorTypes::SUCH_THAT_LIST &suchThatList,
                QueryProcessorTypes::CANDIDATE_LIST &candidateList);

    QueryStruct(QueryProcessorTypes::DECLARED_SYNONYM_MAP &declaredSynonymMap,
                QueryProcessorTypes::PATTERN_LIST &patternList,
                QueryProcessorTypes::CANDIDATE_LIST &candidateList);

    QueryStruct();

    QueryProcessorTypes::DECLARED_SYNONYM_MAP getDeclaredSynonymMap();

    QueryProcessorTypes::SUCH_THAT_LIST getSuchThatList();

    QueryProcessorTypes::PATTERN_LIST getPatternList();

    QueryProcessorTypes::CANDIDATE_LIST getCandidateList();

    void addSynonym(QueryProcessorTypes::EntityType, std::string nameOfEntity);

    void addSuchThatClause(QueryProcessorTypes::RelationStruct relationToAdd);

    void addPatternClause(QueryProcessorTypes::PatternStruct patternToAdd);

    void addCandidate(QueryProcessorTypes::CandidateStruct);
};
#endif // QUERYSTRUCT_H