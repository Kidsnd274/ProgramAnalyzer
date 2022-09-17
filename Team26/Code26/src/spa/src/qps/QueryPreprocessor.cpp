#include "QueryPreprocessor.h"
#include "QueryManager.h"

namespace QPS {
    std::pair<int, Exception> parseDeclaration(std::vector<QPS::Token> &tokens,
                                          int pos,
                                          EntityType entityType,
                                          Container &container);

    std::pair<int, Exception> parseSelect(std::vector<QPS::Token> &tokens, int pos, Container &container);
    std::pair<int, Exception> parsePattern(std::vector<QPS::Token> &tokens, int pos, Container &container);
    std::pair<int, Exception> parseRelationStmtStmt(std::vector<QPS::Token> &tokens, int pos, RelationType relationType, Container &container);
    std::pair<int, Exception> parseRelationStmtEnt(std::vector<QPS::Token> &tokens,
                                                   int pos, RelationType relationType,
                                                   Container &container);

    Exception parseToken(std::vector<QPS::Token> &tokens, Container& container) {
        int tokenPos = 0;
        container.setStatus(START_PARSE_DECLARATION);
        if (tokens[tokens.size() - 1].tokenType == SEMICOLON) {
            return INVALID_SELECT;
        }
        while (tokenPos < tokens.size()) {
            QPS::Token curr = tokens[tokenPos];
//            std::cout << curr.nameValue << std::endl;
            std::pair<EntityType, bool> entityMappingResult = mapEntity(curr);
            std::pair<RelationType, bool> relationMappingResult = mapRelation(tokens, tokenPos);
            if (entityMappingResult.second) {
                // Valid entity
                if (container.getStatus() != START_PARSE_DECLARATION) {
                    // Invalid status for parsing declaration
                    return INVALID_DECLARATION;
                } else {
                    switch (entityMappingResult.first) {
                        case STATEMENT: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, STATEMENT,
                                                                                container);

                            if (result.second == VALID) {
                                tokenPos = result.first;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case READ: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, READ,
                                                                                container);

                            if (result.second == VALID) {
                                tokenPos = result.first;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case PRINT: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, PRINT,
                                                                                container);

                            if (result.second == VALID) {
                                tokenPos = result.first;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case CALL: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, CALL,
                                                                                container);

                            if (result.second == VALID) {
                                tokenPos = result.first;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case WHILE: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, WHILE,
                                                                                container);

                            if (result.second == VALID) {
                                tokenPos = result.first;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case IF: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, IF,
                                                                                container);

                            if (result.second == VALID) {
                                tokenPos = result.first;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case ASSIGN: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, ASSIGN,
                                                                                container);

                            if (result.second == VALID) {
                                tokenPos = result.first;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case VARIABLE: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, VARIABLE,
                                                                                container);

                            if (result.second == VALID) {
                                tokenPos = result.first;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case CONSTANT:{
                            tokenPos++;
                            std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, CONSTANT,
                                                                                container);

                            if (result.second == VALID) {
                                tokenPos = result.first;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }

                        case PROCEDURE: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, PROCEDURE,
                                                                                container);

                            if (result.second == VALID) {
                                tokenPos = result.first;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case INVALID_ENTITY_TYPE: {
                            return INVALID_ENTITY;
                        }
                    }
                }
            } else if (relationMappingResult.second) {
                // Valid relation
                if (container.getStatus() != START_PARSE_SUCH_CLAUSE) {
                    // Invalid query that doesn't have such that
                    return INVALID_RELATION_SYNTAX;
                } else {
                    switch (relationMappingResult.first) {
                        case FOLLOWS: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,
                                                                                FOLLOWS, container);
                            if (result.second == VALID) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case FOLLOWS_T: {
                            tokenPos += 2;
                            std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,
                                                                                FOLLOWS_T, container);
                            if (result.second == VALID) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case PARENT: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,
                                                                                PARENT, container);
                            if (result.second == VALID) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case PARENT_T: {
                            tokenPos += 2;
                            std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,
                                                                                PARENT_T, container);
                            if (result.second == VALID) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case USES_S: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseRelationStmtEnt(tokens, tokenPos,
                                                                                USES_S, container);
                            if (result.second == VALID) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case MODIFIES_S:{
                            tokenPos++;
                            std::pair<int, Exception> result = parseRelationStmtEnt(tokens, tokenPos,
                                                                               MODIFIES_S, container);
                            if (result.second == VALID) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case USES_P: {
                            tokenPos++;
                            std::pair<int, Exception> result = parseRelationStmtEnt(tokens, tokenPos,
                                                                               USES_P, container);
                            if (result.second == VALID) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case MODIFIES_P:{
                            tokenPos++;
                            std::pair<int, Exception> result = parseRelationStmtEnt(tokens, tokenPos,
                                                                              MODIFIES_P, container);
                            if (result.second == VALID) {
                                tokenPos = result.first - 1;
                            } else {
                                // Invalid query
                                return result.second;
                            }
                            break;
                        }
                        case INVALID_RELATION_TYPE:
                        {
                            return INVALID_RELATION;
                        }
                    }
                }

            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "Select") {
                container.setStatus(START_PARSE_SELECT);
                std::pair<int, Exception> result = parseSelect(tokens, tokenPos, container);
                if (result.second == VALID) {
                    tokenPos = result.first - 1;
                } else {
                    return result.second;
                }
                container.setStatus(FINISH_PARSE_SELECT);
            }  else if (curr.tokenType == QPS::NAME && curr.nameValue == "such" && (container.getStatus() == FINISH_PARSE_PATTERN_CLAUSE || container.getStatus() == FINISH_PARSE_SELECT)) {
                container.setStatus(START_PARSE_SUCH);
            }  else if (curr.tokenType == QPS::NAME && curr.nameValue == "that" && container.getStatus() == START_PARSE_SUCH) {
                container.setStatus(FINISH_PARSE_SUCH);
                container.setStatus(START_PARSE_SUCH_CLAUSE);
            } else if (container.getStatus() == START_PARSE_SUCH && (curr.tokenType != QPS::NAME || curr.nameValue != "that")) {
                return INVALID_SUCH_THAT;
            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "pattern" && (container.getStatus() == FINISH_PARSE_SUCH_CLAUSE || container.getStatus() == FINISH_PARSE_SELECT)) {
                tokenPos++;
                std::pair<int, Exception> result = parsePattern(tokens, tokenPos, container);
                if (result.second != VALID) {
                    return result.second;
                } else {
                    container.setStatus(FINISH_PARSE_PATTERN_CLAUSE);
                    tokenPos = result.first - 1;
                }
            } else {
               return UNMATCHED_QUERY_TYPE;
            }
            tokenPos++;
        }

        std::cout << "Finish parsing" << std::endl;

        return VALID;
    }

    std::pair<int, Exception> parsePattern (std::vector<QPS::Token> &tokens,
                                       int pos,
                                       Container &container) {
        std::string assign_syn;
        std::string expression;
        if (pos < tokens.size() && tokens[pos].tokenType == NAME) {
            DECLARED_SYNONYM_MAP declarationMap = container.getDeclarationMap();
            auto iterator = declarationMap.find( tokens[pos].nameValue);
            if (iterator == declarationMap.end()) {
                return {pos, UNDECLARED_ENTITY_PATTERN};
            } else if (iterator->second != ASSIGN) {
                return {pos, INVALID_PATTERN_CONTENT};
            } else {
                assign_syn = iterator->first;
                pos++;
            }
        } else {
            return {pos, INVALID_PATTERN_CONTENT};
        }
        if (pos < tokens.size() && tokens[pos].tokenType == LPAREN) {
            pos++;
        } else {
            return {pos, INVALID_PATTERN_SYNTAX};
        }

        std::pair<ArgumentStruct,bool> ARG1, ARG2;
        if (pos < tokens.size() && (tokens[pos].tokenType == NAME)) {
            ARG1 = convertStringToARG(tokens[pos], container);
            if (!ARG1.second || ARG1.first.typeOfArgument != VAR_SYNONYM) {
                return {pos, INVALID_PATTERN_CONTENT};
            }
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG1 = {{WILDCARD, "_"}, VALID};
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE) {
            pos++;
            std::string actualName;
            while (pos < tokens.size() && tokens[pos].tokenType != DOUBLE_QUOTE) {
                actualName += tokens[pos].nameValue;
                pos++;
            }
            ARG1 = {{ACTUAL_NAME, actualName}, VALID};
            pos++;
        } else {
            return {pos, INVALID_PATTERN_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == COMMA) {
            pos++;
        } else {
            return {pos, INVALID_PATTERN_SYNTAX};
        }

        if (tokens[pos].tokenType == NAME) {
            ARG2 = convertStringToARG(tokens[pos], container);
            if (ARG2.second && (ARG2.first.typeOfArgument == VAR_SYNONYM || ARG2.first.typeOfArgument == CONST_SYNONYM
            || ARG2.first.typeOfArgument == PROCEDURE_SYNONYM || ARG2.first.typeOfArgument == WHILE_SYNONYM
            || ARG2.first.typeOfArgument == IF_SYNONYM || ARG2.first.typeOfArgument == ASSIGN_SYNONYM
            || ARG2.first.typeOfArgument == STMT_SYNONYM || ARG2.first.typeOfArgument == PRINT_SYNONYM
            || ARG2.first.typeOfArgument == CALL_SYNONYM || ARG2.first.typeOfArgument == READ_SYNONYM)) {
                return {pos, INVALID_PATTERN_CONTENT};
            }
        }

        if (tokens[pos].tokenType == UNDERSCORE) {
            expression += "_";
            pos++;
        }
        if (tokens[pos].tokenType == DOUBLE_QUOTE) {
            pos++;
            while (pos < tokens.size() && tokens[pos].tokenType != DOUBLE_QUOTE) {
                if (tokens[pos].tokenType == UNDERSCORE) {
                    return {pos, INVALID_PATTERN_CONTENT};
                }
                expression += tokens[pos].nameValue;
                pos++;
            }

            if (pos < tokens.size()) {
                pos++;
            } else {
                return {pos, INVALID_PATTERN_CONTENT};
            }

            if (tokens[pos].tokenType == UNDERSCORE) {
                expression += "_";
                pos++;
            }
        }

        if (pos < tokens.size() && tokens[pos].tokenType == RPAREN) {
            pos++;
        } else {
            return {pos, INVALID_PATTERN_SYNTAX};
        }

        ArgumentStruct aStruct = {EXPRESSION, expression};
        container.addPatternClause(ASSIGN_PATTERN, assign_syn, ARG1.first, aStruct);
        return {pos, VALID};
    }

    std::pair<int, Exception> parseDeclaration(std::vector<QPS::Token> &tokens,
                                          int pos,
                                          EntityType entityType,
                                          Container &container) {
        std::vector<std::string> entityNames;
        while (pos < tokens.size() && tokens[pos].tokenType != QPS::SEMICOLON ) {
            QPS::Token curr = tokens[pos];
            if (curr.tokenType == QPS::COMMA) {
            } else if (curr.tokenType == QPS::NAME && !mapEntity(curr).second && curr.nameValue != "Select") {
                container.addDeclaration(entityType, curr.nameValue);
            } else {
                return {pos, INVALID_DECLARATION};
            }
            pos++;
        }

        if (pos >= tokens.size()) {
            return {-1, INVALID_DECLARATION};
        } else {
            return {pos, VALID};
        }

    }

    std::pair<int, Exception> parseSelect(std::vector<QPS::Token> &tokens, int pos, Container &container) {
        bool is_multiple_select = false;
        bool is_closed = false;
        while (pos < tokens.size() && !QPS::isSuchThat(tokens[pos])) {
            QPS::Token curr = tokens[pos];
            if (curr.tokenType == QPS::NAME && curr.nameValue == "Select") {
                pos++;
            } else if (curr.tokenType == QPS::NAME && curr.nameValue != "such" && curr.nameValue != "pattern") {
                EntityType entityType = container.getQueryStruct().getDeclaration(curr.nameValue);
                if (entityType != INVALID_ENTITY_TYPE) {
                    container.addCandidateList(entityType, curr.nameValue);
                    pos++;
                } else {
                    return {pos, UNDECLARED_ENTITY_SUCH_THAT};
                }

            } else if (curr.tokenType == QPS::COMMA){
                pos++;
            } else if (curr.tokenType == QPS::NAME && (curr.nameValue == "such" || curr.nameValue == "pattern")){
                return {pos, VALID};
            } else if (curr.tokenType == GT) {
                pos++;
                is_multiple_select = true;
            } else if (curr.tokenType == LT) {
                pos++;
                is_closed = true;
            } else {
                return {pos, INVALID_SELECT};
            }

        }
        if (pos <= tokens.size() && ((is_multiple_select && is_closed) || !is_multiple_select) ) {
            return {pos, VALID};
        } else {
            return {pos, INVALID_SELECT};
        }
    }


    std::pair<int, Exception> parseRelationStmtStmt(std::vector<QPS::Token> &tokens,
                                                    int pos, RelationType relationType,
                                                    Container &container) {
        std::pair<ArgumentStruct, Exception> ARG1, ARG2;

        if (pos < tokens.size() && tokens[pos].tokenType == LPAREN) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

        if (pos < tokens.size() && (tokens[pos].tokenType == NAME || (tokens[pos].tokenType == INTEGER && tokens[pos].nameValue != "0"))) {
            ARG1 = convertStringToStmtRef(tokens[pos], container);
            if (ARG1.second != VALID || ARG1.first.typeOfArgument == PROCEDURE_SYNONYM) {
                return {pos, INVALID_RELATION_CONTENT};
            }
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG1 = {{WILDCARD, "_"}, VALID};
            pos++;
        } else {
            return {pos, INVALID_RELATION_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == COMMA) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

       if (pos < tokens.size() && (tokens[pos].tokenType == NAME || tokens[pos].tokenType == INTEGER  && tokens[pos].nameValue != "0")) {
            ARG2 = convertStringToStmtRef(tokens[pos], container);
           if (ARG2.second != VALID || ARG2.first.typeOfArgument == PROCEDURE_SYNONYM) {
               return {pos, INVALID_RELATION_CONTENT};
           }
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
           return {pos, INVALID_RELATION_SYNTAX};
       }  else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG2 = {{WILDCARD, "_"}, VALID};
            pos++;
        } else {
            return {pos, INVALID_RELATION_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == RPAREN) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }
        if (ARG1.second == VALID && ARG2.second == VALID) {
            container.addSuchThatClause(relationType, ARG1.first, ARG2.first);
            container.setStatus(FINISH_PARSE_SUCH_CLAUSE);
            return {pos, VALID};
        } else {
            if (ARG1.second != VALID) {
                return {pos, ARG1.second};
            } else {
                return {pos, ARG2.second};
            }

        }
    }




    std::pair<int, Exception> parseRelationStmtEnt(std::vector<QPS::Token> &tokens,
                                               int pos, RelationType relationType,
                                               Container &container) {
        std::pair<ArgumentStruct, Exception> ARG1, ARG2;
        std::cout << "stmt ent" << std::endl;
        if (pos < tokens.size() && tokens[pos].tokenType == LPAREN) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

        if (pos < tokens.size() && (tokens[pos].tokenType == NAME || tokens[pos].tokenType == INTEGER  && tokens[pos].nameValue != "0")) {
            ARG1 = convertStringToStmtRef(tokens[pos], container);

            // ms1 doesn't require supporting procedure
            if (ARG1.second == INVALID_RELATION_CONTENT || ARG1.first.typeOfArgument == PROCEDURE_SYNONYM) {
                return {pos, INVALID_RELATION_CONTENT};
            }
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG1 = {{WILDCARD, "_"}, VALID};
        } else if (pos < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+2].tokenType == DOUBLE_QUOTE
                   && tokens[pos + 1].tokenType == NAME) {
            std::string actual_name = tokens[pos + 1].nameValue;
            ARG1 = {{PROCEDURE_ACTUAL_NAME, actual_name}, VALID};
            pos += 3;
        } else if (pos < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
            return {pos, INVALID_RELATION_SYNTAX};
        } else {
            return {pos, INVALID_RELATION_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == COMMA) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+2].tokenType == DOUBLE_QUOTE
            && tokens[pos + 1].tokenType == NAME) {
            std::string actual_name = tokens[pos + 1].nameValue;
            ARG2 = {{ACTUAL_NAME, actual_name}, VALID};
            pos += 3;
        } else if (pos < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
            return {pos, INVALID_RELATION_SYNTAX};
        } else if (pos < tokens.size() && (tokens[pos].tokenType == NAME)) {
            ARG2 = convertStringToEntRef(tokens[pos], container);
            if (ARG2.first.typeOfArgument == CONST_SYNONYM) {
                return {pos, INVALID_RELATION_CONTENT};
            }
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG2 = {{WILDCARD, "_"}, VALID};
            pos++;
        } else {
            return {pos, INVALID_RELATION_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == RPAREN) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }
        if (ARG1.second == VALID && ARG2.second == VALID) {
            container.setStatus(FINISH_PARSE_SUCH_CLAUSE);
            container.addSuchThatClause(relationType, ARG1.first, ARG2.first);
            return {pos, VALID};
        } else {
            if (ARG1.second != VALID) {
                return {pos, ARG1.second};
            } else {
                return {pos, ARG2.second};
            }

        }
    }


    std::pair<ArgumentStruct, Exception> convertStringToEntRef (Token &token, Container &container) {
        if (token.tokenType == INTEGER) {
            return {{ACTUAL_NAME, token.nameValue}, VALID};
        } else if (token.tokenType == NAME) {
            DECLARED_SYNONYM_MAP declarationMap = container.getDeclarationMap();
            auto iterator = declarationMap.find(token.nameValue);
            if (iterator == declarationMap.end()) {
                return {{}, UNDECLARED_ENTITY_SUCH_THAT};
            } else {
                EntityType entityType = iterator->second;
                switch (entityType) {
                    case VARIABLE: {
                        return {{VAR_SYNONYM, token.nameValue}, VALID};
                    }
                    case CONSTANT:{
                        return {{CONST_SYNONYM, token.nameValue}, VALID};
                    }
                    case PROCEDURE:
                    case STATEMENT:
                    case READ:
                    case PRINT:
                    case CALL:
                    case WHILE:
                    case IF:
                    case ASSIGN:
                    case INVALID_ENTITY_TYPE:{
                        return {{INVALID_ARGUMENT_TYPE, token.nameValue}, INVALID_RELATION_CONTENT};
                    }
                }
            }
        } else {
            return {{}, INVALID_RELATION_SYNTAX};
        }
    }

    std::pair<ArgumentStruct, Exception> convertStringToStmtRef (Token &token, Container &container) {
        if (token.tokenType == INTEGER) {
            return {{ACTUAL_NAME, token.nameValue}, VALID};
        } else if (token.tokenType == NAME) {
            DECLARED_SYNONYM_MAP declarationMap = container.getDeclarationMap();
            auto iterator = declarationMap.find(token.nameValue);
            if (iterator == declarationMap.end()) {
                return {{}, UNDECLARED_ENTITY_SUCH_THAT};
            } else {
                EntityType entityType = iterator->second;
                switch (entityType) {
                    case STATEMENT: {
                        return {{STMT_SYNONYM, token.nameValue}, VALID};
                    }
                    case READ: {
                        return {{READ_SYNONYM, token.nameValue}, VALID};
                    }
                    case PRINT: {
                        return {{PRINT_SYNONYM, token.nameValue}, VALID};
                    }
                    case CALL: {
                        return {{CALL_SYNONYM, token.nameValue}, VALID};
                    }
                    case WHILE:{
                        return {{WHILE_SYNONYM, token.nameValue}, VALID};
                    }
                    case IF:{
                        return {{IF_SYNONYM, token.nameValue}, VALID};
                    }
                    case PROCEDURE: {
                        return {{PROCEDURE_SYNONYM, token.nameValue}, VALID};
                    }
                    case ASSIGN:{
                        return {{ASSIGN_SYNONYM, token.nameValue}, VALID};
                    }
                    case VARIABLE:
                    case CONSTANT:
                    case INVALID_ENTITY_TYPE:{
                        return {{INVALID_ARGUMENT_TYPE, token.nameValue}, INVALID_RELATION_CONTENT};
                    }
                }
            }
        } else {
            return {{}, INVALID_RELATION_SYNTAX};
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



    std::pair<EntityType, bool> mapEntity(const QPS::Token& token) {
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



