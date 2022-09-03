#include "QueryPreprocessor.h"


namespace QPS {
    std::pair<EntityType, bool> mapEntity(QPS::Token token);
    std::pair<RelationType, bool> mapRelation(QPS::Token token);
    class Container {
    private:
        std::vector<QPS::Token> tokens;
        QueryStruct queryStruct;

    public:
        Container() = default;
        explicit Container(std::vector<QPS::Token>& tokens) {
            DECLARED_SYNONYM_MAP declaredSynonymMap;
            SUCH_THAT_LIST suchThatList;
            CANDIDATE_LIST candidateList;
            PATTERN_LIST patternList;
            this->tokens = tokens;
            this->queryStruct = QueryStruct(declaredSynonymMap, suchThatList, patternList, candidateList);
        }

        void addDeclaration(EntityType entityType, std::string s) {
            queryStruct.addDeclaredSynonymMap(entityType, s);
        }

        void addCandidateList(EntityType entityType, std::string s) {
            CandidateType candidateType = mapEntityToCandidate(entityType);
            queryStruct.addCandidateList(candidateType, std::move(s), entityType);
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



    std::pair<int, bool> parseDeclaration(std::vector<QPS::Token> &tokens,
                                          int pos,
                                          EntityType entityType,
                                          Container container);

    std::pair<int, bool> parseSelect(std::vector<QPS::Token> &tokens, int pos, Container container);

    void parseToken(std::vector<QPS::Token> &tokens) {
        Container container = Container(tokens);
        int tokenPos = 0;
        while (!tokens.empty()) {
            QPS::Token curr = tokens[tokenPos];
            std::pair<EntityType, bool> entityMappingResult = mapEntity(curr);
            std::pair<RelationType, bool> relationMappingResult = mapRelation(curr);
            if (entityMappingResult.second) {
                // Valid entity
                switch (entityMappingResult.first) {
                    case STATEMENT:
                    case READ:
                    case PRINT:
                    case CALL:
                    case WHILE:
                    case IF:
                    case ASSIGN:
                    case VARIABLE: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, VARIABLE,
                                                                       container);
                        if (result.second) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                        }
                    }
                    case CONSTANT:
                    case PROCEDURE:
                    case INVALID_ENTITY_TYPE:
                        return ;
                }
            } else if (relationMappingResult.second) {
                // Valid entity
                switch (relationMappingResult.first) {
                    case FOLLOWS:
                    case FOLLOWS_T:
                    case PARENT:
                    case PARENT_T:
                    case USES_S:
                    case MODIFIES_S:
                    case INVALID_RELATION_TYPE:
                        return;
                }

            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "Select") {
                std::pair<int, bool> result = parseSelect(tokens, tokenPos, container);
            } else {
                // Invalid entity

            }
            tokenPos++;
        }
        std::cout << "Finish parsing";
        for (auto& it: container.getDeclarationMap()) {
            // Do stuff
            std::cout << it.first + " : " + entityToString(it.second);
        }


        for (QueryProcessorTypes::CandidateStruct candidateStruct : container.getCandidateList()) {
            std::cout << QueryProcessorTypes::candidateToString(candidateStruct.typeOfCandidate) + ": " + candidateStruct.entityOfCandidate.nameOfEntity;
        }
    }


    std::pair<int, bool> parseDeclaration(std::vector<QPS::Token> &tokens,
                                          int pos,
                                          EntityType entityType,
                                          Container container) {
        std::vector<std::string> entityNames;
        while (!isEntity(tokens[pos].nameValue)) {
            QPS::Token curr = tokens[pos];
            if (curr.tokenType == QPS::WHITESPACE) {
                pos++;
                continue;
            }
            if (curr.tokenType == QPS::NAME) {
                container.addDeclaration(entityType, curr.nameValue);
                pos++;
                continue;
            } else {
                return {pos, false};
            }

        }
    }

    std::pair<int, bool> parseSelect(std::vector<QPS::Token> &tokens, int pos, Container container) {
        while (!QPS::isSuchThat(tokens[pos])) {
            QPS::Token curr = tokens[pos];
            if (curr.tokenType == QPS::WHITESPACE) {
                pos++;
                continue;
            }
            if (curr.tokenType == QPS::NAME) {
                EntityType entityType = container.getQueryStruct().getDeclaration(curr.nameValue);
                container.addCandidateList(entityType, curr.nameValue);
                pos++;
                continue;
            } else {
                return {pos, false};
            }

        }
    }


    std::pair<EntityType, bool> mapEntity(QPS::Token token) {
        if (token.tokenType != QPS::NAME) {
            return {INVALID_ENTITY_TYPE, false};
        }
        if (entityMap.find(token.nameValue) == entityMap.end()) {
            // not found
            return {INVALID_ENTITY_TYPE, false};
        } else {
            // found
            return {entityMap.at(token.nameValue), true};
        }
    }

    std::pair<RelationType, bool> mapRelation(QPS::Token token) {
        if (token.tokenType != QPS::NAME) {
            return {INVALID_RELATION_TYPE, false};
        }
        if (relationMap.find(token.nameValue) == relationMap.end()) {
            // not found
            return {INVALID_RELATION_TYPE, false};
        } else {
            // found
            return {relationMap.at(token.nameValue), true};
        }
    }


}



