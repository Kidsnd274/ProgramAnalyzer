#ifndef QUERYSTRUCT_H
#define QUERYSTRUCT_H

#include "QueryProcessorTypes.h"
#include "ResultTable.h"
#include<string>
#include <utility>
#include<vector>
#include<map>
#include <iostream>


/*
 * The data structure to represent the input query string.
 * After parsing, all information about the query will be stored in this QueryStruct data structure.
 */
namespace QPS {
    enum QueryStatus {
        EVALUATION_NOT_STARTED,
        EVALUATION_COMPLETED,
        EVALUATION_ERROR
    };

    class QueryStruct {
    private:
        DECLARED_SYNONYM_MAP declaredSynonymMap;
        SUCH_THAT_LIST suchThatList;
        PATTERN_LIST patternList;
        CANDIDATE_LIST candidateList;

    public:
        QueryStatus queryStatus;
        ResultTable resultTable;

    public:
        QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                    SUCH_THAT_LIST &suchThatList,
                    PATTERN_LIST &patternList,
                    CANDIDATE_LIST &candidateList);

        QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                    SUCH_THAT_LIST &suchThatList,
                    CANDIDATE_LIST &candidateList);

        QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                    PATTERN_LIST &patternList,
                    CANDIDATE_LIST &candidateList);

        QueryStruct();

        DECLARED_SYNONYM_MAP getDeclaredSynonymMap();

        SUCH_THAT_LIST getSuchThatList();

        PATTERN_LIST getPatternList();

        CANDIDATE_LIST getCandidateList();


        void addCandidateList(CandidateType typeOfCandidate, std::string s,
                              EntityType entityType) {
            EntityStruct entityStruct = {entityType, s};
            CandidateStruct candidateStruct = {typeOfCandidate, entityStruct};
            this->candidateList.push_back(candidateStruct);
        }

        EntityType getDeclaration(std::string s) {
            if (this->declaredSynonymMap.find(s) == this->declaredSynonymMap.end()) {
                // not found
                return INVALID_ENTITY_TYPE;
            } else {
                // found
                auto entityType = this->declaredSynonymMap.find(s);
                return entityType->second;
            }
        }

        void addSynonym(EntityType, std::string nameOfEntity);

        void addSuchThatClause(RelationStruct relationToAdd);

        void addPatternClause(PatternStruct patternToAdd);

        void addCandidate(CandidateStruct);
    };
}
#endif // QUERYSTRUCT_H