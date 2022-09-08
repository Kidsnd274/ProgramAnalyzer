#include "QueryPreprocessor.h"
#include "QueryManager.h"

namespace QPS {
    std::pair<int, bool> parseDeclaration(std::vector<QPS::Token> &tokens,
                                          int pos,
                                          EntityType entityType,
                                          Container &container);

    std::pair<int, bool> parseSelect(std::vector<QPS::Token> &tokens, int pos, Container &container);
    std::pair<int, bool> parseRelationStmtStmt(std::vector<QPS::Token> &tokens, int pos, RelationType relationType, Container &container);

    void parseToken(std::vector<QPS::Token> &tokens, Container& container) {
        int tokenPos = 0;
        container.setStatus(START_PARSE_DECLARATION);
        while (tokenPos < tokens.size()) {
            QPS::Token curr = tokens[tokenPos];
            std::pair<EntityType, bool> entityMappingResult = mapEntity(curr);
            std::pair<RelationType, bool> relationMappingResult = mapRelation(tokens, tokenPos);
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
                // Valid relation
                if (container.getStatus() != FINISH_PARSE_SUCH) {
                    // Invalid query that doesn't have such that
                } else {
                    switch (relationMappingResult.first) {
                        case FOLLOWS: {
                            tokenPos++;
                            std::pair<int, bool> result = parseRelationStmtStmt(tokens, tokenPos,
                                                                                FOLLOWS, container);
                            if (result.second) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                tokenPos--;
                            }
                            break;
                        }
                        case FOLLOWS_T: {
                            tokenPos += 2;
                            std::pair<int, bool> result = parseRelationStmtStmt(tokens, tokenPos,
                                                                                FOLLOWS_T, container);
                            if (result.second) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                tokenPos--;
                            }
                            break;
                        }
                        case PARENT: {
                            tokenPos++;
                            std::pair<int, bool> result = parseRelationStmtStmt(tokens, tokenPos,
                                                                                PARENT, container);
                            if (result.second) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                tokenPos--;
                            }
                            break;
                        }
                        case PARENT_T: {
                            tokenPos += 2;
                            std::pair<int, bool> result = parseRelationStmtStmt(tokens, tokenPos,
                                                                                PARENT_T, container);
                            if (result.second) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                tokenPos--;
                            }
                            break;
                        }
                        case USES:
                        case MODIFIES:
                        case INVALID_RELATION_TYPE:
                        {
                            std::cout << "invalid relation" << std::endl;
                            return ;
                        }
                    }
                }

            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "Select") {
                container.setStatus(START_PARSE_SELECT);
                std::pair<int, bool> result = parseSelect(tokens, tokenPos, container);
                if (result.second) {
                    tokenPos = result.first - 1;
                }
                container.setStatus(FINISH_PARSE_SELECT);
            }  else if (curr.tokenType == QPS::NAME && curr.nameValue == "such") {
                container.setStatus(START_PARSE_SUCH);
                std::cout << "parse such" << std::endl;
            }  else if (curr.tokenType == QPS::NAME && curr.nameValue == "that" && container.getStatus() == START_PARSE_SUCH) {
                container.setStatus(FINISH_PARSE_SUCH);
                std::cout << "parse that" << std::endl;
            } else {
                // Invalid entity

            }
            tokenPos++;
        }

        std::cout << "Finish parsing" << std::endl;
        std::cout << "Declaration:" << std::endl;
        for (auto& it: container.getDeclarationMap()) {
            std::cout << it.first << " : " << entityToString(it.second)  << std::endl;
        }
        std::cout << "Candidate:" << std::endl;
        for (QPS::CandidateStruct candidateStruct : container.getCandidateList()) {
            std::cout << QPS::candidateToString(candidateStruct.typeOfCandidate) + ": " + candidateStruct.entityOfCandidate.nameOfEntity  << std::endl;
        }
        std::cout << "Relation:" << std::endl;
        SUCH_THAT_LIST  suchThatList = container.getSuchThatList();
        for (RelationStruct relationStruct: suchThatList) {
            std::cout << QPS::relationToString(relationStruct.typeOfRelation) + ": " + relationStruct.arg1.nameOfArgument + " - "+ QPS::ARGToString(relationStruct.arg1.typeOfArgument)
                    + "  " + relationStruct.arg2.nameOfArgument + " - " + QPS::ARGToString(relationStruct.arg2.typeOfArgument)<< std::endl;
        }
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
            } else if (curr.tokenType == QPS::NAME && curr.nameValue != "such") {
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
            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "such"){
                return {pos, true};
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

    std::pair<int, bool> parseRelationStmtStmt(std::vector<QPS::Token> &tokens,
                                               int pos, RelationType relationType,
                                               Container &container) {
        std::cout << "parse stmt" << std::endl;
        std::pair<ArgumentStruct,bool> ARG1, ARG2;

        if (pos < tokens.size() && tokens[pos].tokenType == LPAREN) {
            pos++;
            std::cout << "parse (" << std::endl;
        } else {
            return {pos, false};
        }

        if (pos < tokens.size() && (tokens[pos].tokenType == NAME || tokens[pos].tokenType == INTEGER)) {
            ARG1 = convertStringToARG(tokens[pos], container);
            std::cout << "parse first arg" << std::endl;
            pos++;
        } else {
            return {pos, false};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == COMMA) {
            pos++;
            std::cout << "parse comma" << std::endl;
        } else {
            return {pos, false};
        }

        if (pos < tokens.size() && (tokens[pos].tokenType == NAME || tokens[pos].tokenType == INTEGER)) {
            ARG2 = convertStringToARG(tokens[pos], container);
            std::cout << "parse second arg" << std::endl;
            pos++;
        } else {
            return {pos, false};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == RPAREN) {
            pos++;
            std::cout << "parse )" << std::endl;
        } else {
            return {pos, false};
        }
        if (ARG1.second && ARG2.second) {
            container.addSuchThatClause(relationType, ARG1.first, ARG2.first);
            std::cout << "parse stmt finish" << std::endl;
            return {pos, true};
        } else {
            return {pos, false};
        }
    }

    std::pair<ArgumentStruct, bool> convertStringToARG (Token &token, Container &container) {
        if (token.tokenType == INTEGER) {
            return {{NUMBER, token.nameValue}, true};
        } else if (token.tokenType == NAME) {
            DECLARED_SYNONYM_MAP declarationMap = container.getDeclarationMap();
            auto iterator = declarationMap.find(token.nameValue);
            if (iterator == declarationMap.end()) {
                return {{}, false};
            } else {
                EntityType entityType = iterator->second;
                switch (entityType) {
                    case STATEMENT:
                    case READ:
                    case PRINT:
                    case CALL:
                    case WHILE:
                    case IF:
                    case ASSIGN:{
                        return {{STMT_SYNONYM, token.nameValue}, true};
                    }
                    case PROCEDURE: {
                        return {{PROCEDURE_SYNONYM, token.nameValue}, true};
                    }
                    case VARIABLE:{
                        return {{VAR_SYNONYM, token.nameValue}, true};
                    }
                    case CONSTANT:{
                        return {{CONST_SYNONYM, token.nameValue}, true};
                    }
                    case INVALID_ENTITY_TYPE:{
                        return {{INVALID_ARGUMENT_TYPE, token.nameValue}, true};
                    }
                }
            }
        } else if (token.tokenType == UNDERSCORE) {
            return {{WILDCARD, "_"}, true};
        } else {
            return {{}, false};
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

    std::pair<RelationType, bool> mapRelation(std::vector<QPS::Token> &tokens, int pos) {
        if (tokens[pos].tokenType != QPS::NAME) {
            return {INVALID_RELATION_TYPE, false};
        }
        if (relationMap.find(tokens[pos].nameValue) == relationMap.end()) {
            // not found
            return {INVALID_RELATION_TYPE, false};
        } else {
            // found
            if (tokens[pos].nameValue == "Follows" && tokens[pos+1].tokenType == STAR) {
                return {FOLLOWS_T, true};
            }
            if (tokens[pos].nameValue == "Parent" && tokens[pos+1].tokenType == STAR) {
                return {PARENT_T, true};
            }
            return {relationMap.at(tokens[pos].nameValue), true};
        }
    }


}



