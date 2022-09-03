#include <map>
#include <utility>
#include <iostream>
#include "Tokenizer.h"
#include "QueryProcessorTypes.h"
#include "QueryPreprocessor.h"
#include "QueryStruct.h"

namespace QueryPreprocessor{

    class Container {
    private:
        std::vector<Tokenization::Token> tokens;
        QueryStruct queryStruct;



    public:
        Container() = default;
        explicit Container(std::vector<Tokenization::Token>& tokens) {
            QueryProcessorTypes::DECLARED_SYNONYM_MAP declaredSynonymMap;
            QueryProcessorTypes::SUCH_THAT_LIST suchThatList;
            QueryProcessorTypes::CANDIDATE_LIST candidateList;
            QueryProcessorTypes::PATTERN_LIST patternList;
            this->tokens = tokens;
            this->queryStruct = QueryStruct(declaredSynonymMap, suchThatList, patternList, candidateList);
        }

        void addDeclaration(QueryProcessorTypes::EntityType entityType, std::string s) {
            queryStruct.addDeclaredSynonymMap(entityType, s);
        }

        void addCandidateList(QueryProcessorTypes::EntityType entityType, std::string s) {
            QueryProcessorTypes::CandidateType candidateType = QueryProcessorTypes::mapEntityToCandidate(entityType);
            queryStruct.addCandidateList(candidateType, std::move(s), entityType);
        }

        QueryProcessorTypes::DECLARED_SYNONYM_MAP getDeclarationMap() {
            return this->queryStruct.getDeclaredSynonymMap();
        }

        QueryProcessorTypes::CANDIDATE_LIST  getCandidateList(){
            return this->queryStruct.getCandidateList();
        }

        QueryStruct getQueryStruct() {
            return this->queryStruct;
        }
    };



    std::pair<int, bool> parseDeclaration(std::vector<Tokenization::Token> &tokens,
                                          int pos,
                                          QueryProcessorTypes::EntityType entityType,
                                          Container container);

    std::pair<int, bool> parseSelect(std::vector<Tokenization::Token> &tokens, int pos, Container container);

    void parseToken(std::vector<Tokenization::Token> &tokens) {
        Container container = Container(tokens);
        int tokenPos = 0;
        while (!tokens.empty()) {
            Tokenization::Token curr = tokens[tokenPos];
            std::pair<QueryProcessorTypes::EntityType, bool> entityMappingResult = mapEntity(curr);
            std::pair<QueryProcessorTypes::RelationType, bool> relationMappingResult = mapRelation(curr);
            if (entityMappingResult.second) {
                // Valid entity
                switch (entityMappingResult.first) {
                    case QueryProcessorTypes::STATEMENT:
                    case QueryProcessorTypes::READ:
                    case QueryProcessorTypes::PRINT:
                    case QueryProcessorTypes::CALL:
                    case QueryProcessorTypes::WHILE:
                    case QueryProcessorTypes::IF:
                    case QueryProcessorTypes::ASSIGN:
                    case QueryProcessorTypes::VARIABLE: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, QueryProcessorTypes::VARIABLE,
                                                                       container);
                        if (result.second) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                        }
                    }
                    case QueryProcessorTypes::CONSTANT:
                    case QueryProcessorTypes::PROCEDURE:
                    case QueryProcessorTypes::INVALID_ENTITY_TYPE:
                        return ;
                }
            } else if (relationMappingResult.second) {
                // Valid entity
                switch (relationMappingResult.first) {
                    case QueryProcessorTypes::FOLLOWS:
                    case QueryProcessorTypes::FOLLOWS_T:
                    case QueryProcessorTypes::PARENT:
                    case QueryProcessorTypes::PARENT_T:
                    case QueryProcessorTypes::USES_S:
                    case QueryProcessorTypes::MODIFIES_S:
                    case QueryProcessorTypes::INVALID_RELATION_TYPE:
                        return;
                }

            } else if (curr.tokenType == Tokenization::NAME && curr.nameValue == "Select") {
                std::pair<int, bool> result = parseSelect(tokens, tokenPos, container);
            } else {
                // Invalid entity

            }
            tokenPos++;
        }
        std::cout << "Finish parsing";
        for (auto& it: container.getDeclarationMap()) {
            // Do stuff
            std::cout << it.first + " : " + QueryProcessorTypes::entityToString(it.second);
        }

        for (QueryProcessorTypes::CandidateStruct candidateStruct : container.getCandidateList()) {
            std::cout << QueryProcessorTypes::candidateToString(candidateStruct.typeOfCandidate) + ": " + candidateStruct.entityOfCandidate.nameOfEntity;
        }
    }


    std::pair<int, bool> parseDeclaration(std::vector<Tokenization::Token> &tokens,
                                          int pos,
                                          QueryProcessorTypes::EntityType entityType,
                                          Container container) {
        std::vector<std::string> entityNames;
        while (!QueryProcessorTypes::isEntity(tokens[pos].nameValue)) {
            Tokenization::Token curr = tokens[pos];
            if (curr.tokenType == Tokenization::WHITESPACE) {
                pos++;
                continue;
            }
            if (curr.tokenType == Tokenization::NAME) {
                container.addDeclaration(entityType, curr.nameValue);
                pos++;
                continue;
            } else {
                return {pos, false};
            }

        }
    }

    std::pair<int, bool> parseSelect(std::vector<Tokenization::Token> &tokens, int pos, Container container) {
        while (!Tokenization::isSuchThat(tokens[pos])) {
            Tokenization::Token curr = tokens[pos];
            if (curr.tokenType == Tokenization::WHITESPACE) {
                pos++;
                continue;
            }
            if (curr.tokenType == Tokenization::NAME) {
                QueryProcessorTypes::EntityType entityType = container.getQueryStruct().getDeclaration(curr.nameValue);
                container.addCandidateList(entityType, curr.nameValue);
                pos++;
                continue;
            } else {
                return {pos, false};
            }

        }
    }


    std::pair<QueryProcessorTypes::EntityType, bool> mapEntity(Tokenization::Token token) {
        if (token.tokenType != Tokenization::NAME) {
            return {QueryProcessorTypes::INVALID_ENTITY_TYPE, false};
        }
        if (QueryProcessorTypes::entityMap.find(token.nameValue) == QueryProcessorTypes::entityMap.end()) {
            // not found
            return {QueryProcessorTypes::INVALID_ENTITY_TYPE, false};
        } else {
            // found
            return {QueryProcessorTypes::entityMap.at(token.nameValue), true};
        }
    }

    std::pair<QueryProcessorTypes::RelationType, bool> mapRelation(Tokenization::Token token) {
        if (token.tokenType != Tokenization::NAME) {
            return {QueryProcessorTypes::INVALID_RELATION_TYPE, false};
        }
        if (QueryProcessorTypes::relationMap.find(token.nameValue) == QueryProcessorTypes::relationMap.end()) {
            // not found
            return {QueryProcessorTypes::INVALID_RELATION_TYPE, false};
        } else {
            // found
            return {QueryProcessorTypes::relationMap.at(token.nameValue), true};
        }
    }


}



