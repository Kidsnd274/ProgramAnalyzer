//
// Created by 乐灏 Cheese on 2022/9/4.
//

#ifndef SPA_QUERYMANAGER_H
#define SPA_QUERYMANAGER_H

#include "Tokenizer.h"
#include "QueryStruct.h"

namespace QPS {
    enum Status{
        INITIALIZED,
        START_PARSE_DECLARATION,
        FINISH_PARSE_DECLARATION,
        START_PARSE_SELECT,
        FINISH_PARSE_SELECT
    };

    class Container {
    private:
        std::vector<QPS::Token> tokens;
        QueryStruct queryStruct;
        Status status;

    public:
        Container() = default;

        explicit Container(std::vector<QPS::Token>& tokens) {
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
            std::cout << "add declaration" << s << std::endl;
            this->queryStruct.addSynonym(entityType, s);
        }

        void addCandidateList(EntityType entityType, std::string s) {
            CandidateType candidateType = mapEntityToCandidate(entityType);
            this->queryStruct.addCandidateList(candidateType, std::move(s), entityType);
        }

        DECLARED_SYNONYM_MAP getDeclarationMap() {
            return this->queryStruct.getDeclaredSynonymMap();
        }

        CANDIDATE_LIST  getCandidateList(){
            return this->queryStruct.getCandidateList();
        }

        QueryStruct getQueryStruct() {
            return this->queryStruct;
        }
    };
}
#endif //SPA_QUERYMANAGER_H
