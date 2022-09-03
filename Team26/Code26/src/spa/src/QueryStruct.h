#ifndef QUERYSTRUCT_H
#define QUERYSTRUCT_H

#include "QueryProcessorTypes.h"
#include<string>
#include <utility>
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

    QueryProcessorTypes::DECLARED_SYNONYM_MAP getDeclaredSynonymMap() {
        return declaredSynonymMap;
    }
    QueryProcessorTypes::SUCH_THAT_LIST getSuchThatList();
    QueryProcessorTypes::PATTERN_LIST getPatternList();
    QueryProcessorTypes::CANDIDATE_LIST getCandidateList() {
        return candidateList;
    }
    void addDeclaredSynonymMap(QueryProcessorTypes::EntityType entityType, const std::string& s) {
        this->declaredSynonymMap.insert({s, entityType});
    }
    void addCandidateList(QueryProcessorTypes::CandidateType typeOfCandidate, std::string s) {
        QueryProcessorTypes::CandidateStruct candidateStruct = {typeOfCandidate, std::move(s)};
        this->candidateList.push_back(candidateStruct);
    }

    QueryProcessorTypes::EntityType getDeclaration(std::string s) {
        auto entityType = this-> declaredSynonymMap.find(s);
        return entityType->second;
    }

    void addSuchThatClause(QueryProcessorTypes::RelationStruct relationToAdd);
    void addPatternClause(QueryProcessorTypes::PatternStruct patternToAdd);
};
#endif // QUERYSTRUCT_H