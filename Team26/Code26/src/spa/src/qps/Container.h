#ifndef SPA_CONTAINER_H
#define SPA_CONTAINER_H

#include "Tokenizer.h"
#include "QueryStruct.h"
#include <list>
#include <vector>
#include <string>

namespace QPS {
    enum Status{
        INITIALIZED,
        START_PARSE_DECLARATION,
        FINISH_PARSE_DECLARATION,
        START_PARSE_SELECT,
        FINISH_PARSE_SELECT,
        START_PARSE_SUCH,
        FINISH_PARSE_SUCH,
        START_PARSE_SUCH_CLAUSE,
        FINISH_PARSE_SUCH_CLAUSE,
        START_PARSE_PATTERN_CLAUSE,
        FINISH_PARSE_PATTERN_CLAUSE
    };

    class Container {
    private:
        std::vector<QPS::Token> tokens;
        QueryStruct queryStruct;
        Status status;

    public:
        Container() = default;

        explicit Container(std::vector<QPS::Token> &tokens) {
            DECLARED_SYNONYM_MAP declaredSynonymMap;
            SUCH_THAT_LIST suchThatList;
            CANDIDATE_LIST candidateList;
            PATTERN_LIST patternList;
            this->tokens = tokens;
            this->queryStruct = QueryStruct(declaredSynonymMap, suchThatList, patternList, candidateList);
            this->status = INITIALIZED;
        }

        Status getStatus() {
            return this->status;
        }

        void setStatus(Status status1) {
            this->status = status1;
        }

        void addDeclaration(EntityType entityType, std::string s) {
            this->queryStruct.addSynonym(entityType, s);
        }

        void addCandidateList(EntityType entityType, std::string s) {
            CandidateType candidateType = mapEntityToCandidate(entityType);
            this->queryStruct.addCandidateList(candidateType, std::move(s), entityType);
        }

        void addSuchThatClause(RelationType relationType, ArgumentStruct ARG1, ArgumentStruct ARG2) {
            RelationStruct relationStruct = {relationType, std::move(ARG1), std::move(ARG2)};
            this->queryStruct.addSuchThatClause(relationStruct);
        }

        void
        addPatternClause(PatternType typeOfPattern, std::string assign_syn, ArgumentStruct arg1, ArgumentStruct arg2) {
            PatternStruct patternStruct = {typeOfPattern, std::move(assign_syn), std::move(arg1), std::move(arg2)};
            this->queryStruct.addPatternClause(patternStruct);
        }

        DECLARED_SYNONYM_MAP getDeclarationMap() {
            return this->queryStruct.getDeclaredSynonymMap();
        }

        CANDIDATE_LIST getCandidateList() {
            return this->queryStruct.getCandidateList();
        }

        SUCH_THAT_LIST getSuchThatList() {
            return this->queryStruct.getSuchThatList();
        }

        PATTERN_LIST getPatternList() {
            return this->queryStruct.getPatternList();
        }

        QueryStruct getQueryStruct() {
            return this->queryStruct;
        }
    };
}


#endif //SPA_CONTAINER_H
