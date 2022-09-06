#include "QueryPreprocessor.h"
#include "QueryManager.h"

namespace QPS {
    std::pair<int, bool> parseDeclaration(std::vector<QPS::Token> &tokens,
                                          int pos,
                                          EntityType entityType,
                                          Container &container);

    std::pair<int, bool> parseSelect(std::vector<QPS::Token> &tokens, int pos, Container &container);

    void parseToken(std::vector<QPS::Token> &tokens, Container& container) {
        int tokenPos = 0;
        container.setStatus(START_PARSE_DECLARATION);
        while (tokenPos < tokens.size()) {
            QPS::Token curr = tokens[tokenPos];
            std::pair<EntityType, bool> entityMappingResult = mapEntity(curr);
            std::pair<RelationType, bool> relationMappingResult = mapRelation(curr);
            if (entityMappingResult.second) {
                // Valid entity
                switch (entityMappingResult.first) {
                    case STATEMENT: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, STATEMENT,
                                                                       container);

                        if (result.second) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            tokenPos--;
                        }
                        break;
                    }
                    case READ: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, READ,
                                                                       container);

                        if (result.second) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            tokenPos--;
                        }
                        break;
                    }
                    case PRINT: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, PRINT,
                                                                       container);

                        if (result.second) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            tokenPos--;
                        }
                        break;
                    }
                    case CALL: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, CALL,
                                                                       container);

                        if (result.second) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            tokenPos--;
                        }
                        break;
                    }
                    case WHILE: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, WHILE,
                                                                       container);

                        if (result.second) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            tokenPos--;
                        }
                        break;
                    }
                    case IF: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, IF,
                                                                       container);

                        if (result.second) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            tokenPos--;
                        }
                        break;
                    }
                    case ASSIGN: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, ASSIGN,
                                                                       container);

                        if (result.second) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            tokenPos--;
                        }
                        break;
                    }
                    case VARIABLE: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, VARIABLE,
                                                                       container);

                        if (result.second) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            tokenPos--;
                        }
                        break;
                    }
                    case CONSTANT:{
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, CONSTANT,
                                                                       container);

                        if (result.second) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            tokenPos--;
                        }
                        break;
                    }

                    case PROCEDURE: {
                        tokenPos++;
                        std::pair<int, bool> result = parseDeclaration(tokens, tokenPos, PROCEDURE,
                                                                       container);

                        if (result.second) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            tokenPos--;
                        }
                        break;
                    }
                    case INVALID_ENTITY_TYPE: {
                        std::cout << "invalid entity" << std::endl;
                        return ;
                    }
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
                    {
                        std::cout << "invalid relation" << std::endl;
                        return ;
                    }
                }

            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "Select") {
                container.setStatus(START_PARSE_SELECT);
                std::pair<int, bool> result = parseSelect(tokens, tokenPos, container);
                if (result.second) {
                    tokenPos = result.first - 1;
                }
                container.setStatus(FINISH_PARSE_SELECT);
            }  else {
                // Invalid entity

            }
            tokenPos++;
        }

//        std::cout << "Finish parsing" << std::endl;
//        std::cout << "Declaration:" << std::endl;
//        for (auto& it: container.getDeclarationMap()) {
//            std::cout << it.first << " : " << entityToString(it.second)  << std::endl;
//        }
//        std::cout << "Candidate:" << std::endl;
//        for (QPS::CandidateStruct candidateStruct : container.getCandidateList()) {
//            std::cout << QPS::candidateToString(candidateStruct.typeOfCandidate) + ": " + candidateStruct.entityOfCandidate.nameOfEntity  << std::endl;
//        }
    }


    std::pair<int, bool> parseDeclaration(std::vector<QPS::Token> &tokens,
                                          int pos,
                                          EntityType entityType,
                                          Container &container) {
        std::vector<std::string> entityNames;
//        std::cout << "parse declaration: " << tokens[pos].nameValue << std::endl;
        while (pos < tokens.size() && tokens[pos].tokenType != QPS::SEMICOLON) {
            QPS::Token curr = tokens[pos];
            if (curr.tokenType == QPS::COMMA) {
//                std::cout << "comma" <<std::endl;
            } else if (curr.tokenType == QPS::NAME) {
//                std::cout << "parse declaration: name" << std::endl;
                container.addDeclaration(entityType, curr.nameValue);
            } else {
                return {pos, false};
            }
            pos++;
        }

        if (pos >= tokens.size()) {
            return {-1, false};
        } else {
            return {pos, true};
        }

    }

    std::pair<int, bool> parseSelect(std::vector<QPS::Token> &tokens, int pos, Container &container) {
        while (pos < tokens.size() && !QPS::isSuchThat(tokens[pos])) {
            QPS::Token curr = tokens[pos];
            if (curr.tokenType == QPS::NAME && curr.nameValue == "Select") {
                pos++;
            } else if (curr.tokenType == QPS::NAME && curr.nameValue != "Select") {
//                std::cout << "select: " << curr.nameValue << std::endl;
                EntityType entityType = container.getQueryStruct().getDeclaration(curr.nameValue);
                if (entityType != INVALID_ENTITY_TYPE) {
                    container.addCandidateList(entityType, curr.nameValue);
                    pos++;
                } else {
                    return {pos, false};
                }

            } else if (curr.tokenType == QPS::COMMA){
                pos++;
            } else {
                return {pos, false};
            }

        }
        if (pos <= tokens.size()) {
            return {pos, true};
        } else {
            return {-1, false};
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



