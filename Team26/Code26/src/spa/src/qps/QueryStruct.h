#ifndef QUERYSTRUCT_H
#define QUERYSTRUCT_H

#include "QueryProcessorTypes.h"
#include "ResultTable.h"
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <iostream>
#include <set>


/*
 * The data structure to represent the input query string.
 * After parsing, all information about the query will be stored in this QueryStruct data structure.
 */
namespace QPS {
    enum QueryStatus {
        EVALUATION_NOT_STARTED,
        EVALUATION_COMPLETED,
        EVALUATION_ERROR,
        VALID_QUERY,
        SYNTAX_ERROR,
        SEMANTIC_ERROR
    };

    class QueryStruct {
    private:
        DECLARED_SYNONYM_MAP declaredSynonymMap;
        SUCH_THAT_LIST suchThatList;
        PATTERN_LIST patternList;
        CANDIDATE_LIST candidateList;
        WITH_LIST   withList;

    public:
        QueryStatus queryStatus;
        ResultTable resultTable;
        unordered_set<std::string> usedSynonymList;

    public:
        QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap, SUCH_THAT_LIST &suchThatList, PATTERN_LIST &patternList, CANDIDATE_LIST &candidateList,
                    WITH_LIST &withList);


        QueryStruct();

        DECLARED_SYNONYM_MAP getDeclaredSynonymMap();

        SUCH_THAT_LIST getSuchThatList();

        PATTERN_LIST getPatternList();

        CANDIDATE_LIST getCandidateList();

        WITH_LIST getWithList();


        void addCandidateList(CandidateType typeOfCandidate, std::string s,
                              EntityType entityType) {
            EntityStruct entityStruct = {entityType, s};
            CandidateStruct candidateStruct = {typeOfCandidate, entityStruct};
            this->candidateList.push_back(candidateStruct);
        }

        void addCandidateListBoolean() {
            CandidateStruct candidateStruct = {BOOLEAN, {}};
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

        void addSynonym(EntityType, const std::string& nameOfEntity);

        void addSuchThatClause(const RelationStruct& relationToAdd);

        void addPatternClause(const PatternStruct& patternToAdd);

        void addCandidate(const CandidateStruct&);

        void addWithClause(const WithStruct& withStruct);

        void addUsedSynonym(const std::string&);

        void generateUsedSynonymList();
        /**
         * Checks whether the given synonym is used in query
         * as candidate or argument.
         *
         * @param nameOfSynonym A string, the name of synonym.
         * @return bool.
         */
        bool isSynonymUsed(const std::string& nameOfSynonym);
    };
}
#endif // QUERYSTRUCT_H