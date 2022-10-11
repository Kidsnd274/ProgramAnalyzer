#include "QueryPreprocessor.h"
#include "QueryManager.h"

namespace QPS {
    std::pair<int, Exception> parseDeclaration(std::vector<QPS::Token> &tokens,
                                          int pos,
                                          Entity::EntityType entityType,
                                          Container &container);

    std::pair<int, Exception> parseSelect(std::vector<QPS::Token> &tokens, int pos, Container &container);
    std::pair<int, Exception> parsePattern(std::vector<QPS::Token> &tokens, int pos, Container &container);
    std::pair<int, Exception> parseRelationStmtStmt(std::vector<QPS::Token> &tokens, int pos, RelationType relationType, Container &container);
    std::pair<int, Exception> parseRelationStmtEnt(std::vector<QPS::Token> &tokens, int pos, RelationType relationType, Container &container);
    std::pair<int, Exception> parseRelationCalls(std::vector<QPS::Token> &tokens, int pos, RelationType relationType, Container &container);
    std::pair<int, Exception> parseWithClause(std::vector<QPS::Token> &tokens, int pos, Container &container);

    Exception parseToken(std::vector<QPS::Token> &tokens, Container& container) {
        int tokenPos = 0;
        container.setStatus(START_PARSE_DECLARATION);
        if (tokens[tokens.size() - 1].tokenType == SEMICOLON) {
            return INVALID_SELECT;
        }
        while (tokenPos < tokens.size()) {
            QPS::Token curr = tokens[tokenPos];
            std::pair<Entity::EntityType, bool> entityMappingResult = mapEntity(curr);
            std::pair<RelationType, bool> relationMappingResult = mapRelation(tokens, tokenPos);
            if (entityMappingResult.second && container.getStatus() == START_PARSE_DECLARATION) {
                // Valid entity
                switch (entityMappingResult.first) {
                    case Entity::STATEMENT: {
                        tokenPos++;
                        std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos,
                                                                            Entity::STATEMENT,
                                                                            container);

                        if (result.second == VALID) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case Entity::READ: {
                        tokenPos++;
                        std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, Entity::READ,container);

                        if (result.second == VALID) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case Entity::PRINT: {
                        tokenPos++;
                        std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, Entity::PRINT,container);

                        if (result.second == VALID) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case Entity::CALL: {
                        tokenPos++;
                        std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, Entity::CALL,container);

                        if (result.second == VALID) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case Entity::WHILE: {
                        tokenPos++;
                        std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, Entity::WHILE,container);

                        if (result.second == VALID) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case Entity::IF: {
                        tokenPos++;
                        std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, Entity::IF,container);

                        if (result.second == VALID) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case Entity::ASSIGN: {
                        tokenPos++;
                        std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos, Entity::ASSIGN,container);

                        if (result.second == VALID) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case Entity::VARIABLE: {
                        tokenPos++;
                        std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos,Entity::VARIABLE,container);

                        if (result.second == VALID) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case Entity::CONSTANT:{
                        tokenPos++;
                        std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos,Entity::CONSTANT,container);

                        if (result.second == VALID) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }

                    case Entity::PROCEDURE: {
                        tokenPos++;
                        std::pair<int, Exception> result = parseDeclaration(tokens, tokenPos,Entity::PROCEDURE,container);

                        if (result.second == VALID) {
                            tokenPos = result.first;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case Entity::INVALID_ENTITY_TYPE: {
                        return INVALID_ENTITY;
                    }
                }
            } else if (relationMappingResult.second && container.getStatus() == START_PARSE_SUCH_CLAUSE) {
                // Valid relation
                switch (relationMappingResult.first) {
                    case FOLLOWS: {
                        tokenPos++;
                        std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,FOLLOWS, container);
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
                        std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,FOLLOWS_T, container);
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
                        std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,PARENT, container);
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
                        std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,PARENT_T, container);
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
                        std::pair<int, Exception> result = parseRelationStmtEnt(tokens, tokenPos,USES_S, container);
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
                        std::pair<int, Exception> result = parseRelationStmtEnt(tokens, tokenPos,MODIFIES_S, container);
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
                        std::pair<int, Exception> result = parseRelationStmtEnt(tokens, tokenPos,USES_P, container);
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
                        std::pair<int, Exception> result = parseRelationStmtEnt(tokens, tokenPos,MODIFIES_P, container);
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
                    case CALLS:{
                        tokenPos++;
                        std::pair<int, Exception> result = parseRelationCalls(tokens, tokenPos,CALLS, container);
                        if (result.second == VALID) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case CALLS_P:{
                        tokenPos++;
                        std::pair<int, Exception> result = parseRelationCalls(tokens, tokenPos,CALLS_P, container);
                        if (result.second == VALID) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case NEXT:{
                        tokenPos++;
                        std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,NEXT, container);
                        if (result.second == VALID) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case NEXT_P:{
                        tokenPos++;
                        std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,NEXT_P, container);
                        if (result.second == VALID) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case AFFECTS:{
                        tokenPos++;
                        std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,AFFECTS, container);
                        if (result.second == VALID) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
                    }
                    case AFFECTS_P:{
                        tokenPos++;
                        std::pair<int, Exception> result = parseRelationStmtStmt(tokens, tokenPos,AFFECTS_P, container);
                        if (result.second == VALID) {
                            tokenPos = result.first - 1;
                        } else {
                            // Invalid query
                            return result.second;
                        }
                        break;
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
            }  else if (curr.tokenType == QPS::NAME && curr.nameValue == "such" &&
                    (container.getStatus() == FINISH_PARSE_PATTERN_CLAUSE
                    || container.getStatus() == FINISH_PARSE_SELECT
                    || container.getStatus() == FINISH_PARSE_SUCH_CLAUSE
                    || container.getStatus() == FINISH_PARSE_WITH_CLAUSE)) {
                container.setStatus(START_PARSE_SUCH);
            }  else if (curr.tokenType == QPS::NAME && curr.nameValue == "that" && container.getStatus() == START_PARSE_SUCH) {
                container.setStatus(FINISH_PARSE_SUCH);
                container.setStatus(START_PARSE_SUCH_CLAUSE);
            } else if (container.getStatus() == START_PARSE_SUCH && (curr.tokenType != QPS::NAME || curr.nameValue != "that")) {
                return INVALID_SUCH_THAT;
            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "pattern" &&
                    (container.getStatus() == FINISH_PARSE_SUCH_CLAUSE
                    || container.getStatus() == FINISH_PARSE_SELECT
                    || container.getStatus() == START_PARSE_PATTERN_CLAUSE
                    || container.getStatus() == FINISH_PARSE_WITH_CLAUSE)) {
                tokenPos++;
                std::pair<int, Exception> result = parsePattern(tokens, tokenPos, container);
                if (result.second != VALID) {
                    return result.second;
                } else {
                    container.setStatus(FINISH_PARSE_PATTERN_CLAUSE);
                    tokenPos = result.first - 1;
                }
            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "and"
                        && container.getStatus() == FINISH_PARSE_SUCH_CLAUSE ) {
                Token next = tokens[tokenPos + 1];
                if (next.tokenType == NAME && next.nameValue != "pattern" && next.nameValue != "such") {
                    container.setStatus(START_PARSE_SUCH_CLAUSE);
                } else {
                    return INVALID_MULTIPLE_CLAUSE;
                }
            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "and"
                        && container.getStatus() == FINISH_PARSE_PATTERN_CLAUSE ) {
                Token next = tokens[tokenPos + 1];
                if (next.tokenType == NAME && next.nameValue == "pattern") {
                    container.setStatus(START_PARSE_PATTERN_CLAUSE);
                } else {
                    return INVALID_MULTIPLE_CLAUSE;
                }
            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "with"
                            && (container.getStatus() == FINISH_PARSE_SELECT
                                || container.getStatus() == FINISH_PARSE_PATTERN_CLAUSE
                                || container.getStatus() == FINISH_PARSE_SUCH_CLAUSE) ) {
                container.setStatus(START_PARSE_WITH_CLAUSE);
                tokenPos++;
                std::pair<int, Exception> result = parseWithClause(tokens, tokenPos, container);
                if (result.second != VALID) {
                    return result.second;
                } else {
                    container.setStatus(FINISH_PARSE_WITH_CLAUSE);
                    tokenPos = result.first - 1;
                }
            } else {
               return UNMATCHED_QUERY_TYPE;
            }
            tokenPos++;
        }

        return VALID;
    }

    std::pair<int, Exception> parseWithClause(std::vector<QPS::Token> &tokens, int pos, Container &container) {
        WithStruct withStruct;
        if (pos < tokens.size() && tokens[pos].tokenType == NAME) {
            DECLARED_SYNONYM_MAP declarationMap = container.getDeclarationMap();
            auto iterator = declarationMap.find( tokens[pos].nameValue);
            if (iterator == declarationMap.end()) {
                return {pos, UNDECLARED_ENTITY_WITH};
            } else {
                withStruct.first_entity = iterator -> second;
                withStruct.first_name = iterator->first;
                pos++;
            }
        } else {
            return {pos, INVALID_WITH_SYNTAX};
        }

        if (pos < tokens.size() && tokens[pos].tokenType != DOT) {
            return {pos, INVALID_WITH_MISSING_DOT};
        }

        pos++;

        if (pos < tokens.size() && tokens[pos].tokenType == NAME) {
            std::pair<WithFieldType, Exception> fields = convertStringToWithType(tokens[pos]);
            if (fields.second != VALID) {
                return {pos, INVALID_WITH_FIELD};
            } else {
                withStruct.first_field_type = fields.first;
                // handle stmt#
                if (withStruct.first_field_type == STMT_INTEGER && tokens[pos + 1].tokenType == HASHTAG) {
                    pos++;
                } else if (withStruct.first_field_type == STMT_INTEGER) {
                    return {pos, INVALID_WITH_SYNTAX};
                }
                pos++;
            }
        }

        if (pos < tokens.size() && tokens[pos].tokenType != SINGLE_EQ) {
            return {pos, INVALID_WITH_SYNTAX};
        }

        pos++;

        //p.procName = "xxx"
        if (pos + 2 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+2].tokenType == DOUBLE_QUOTE
            && (tokens[pos + 1].tokenType == NAME)) {
            switch (withStruct.first_entity) {
                case Entity::READ:
                case Entity::PRINT:
                case Entity::VARIABLE:
                case Entity::CALL:
                case Entity::PROCEDURE:{
                    withStruct.second_field_type = ACTUAL_WITH_NAME;
                    withStruct.second_name = tokens[pos + 1].nameValue;
                    break;
                }
                case Entity::WHILE:
                case Entity::IF:
                case Entity::STATEMENT:
                case Entity::ASSIGN:
                case Entity::CONSTANT:
                case Entity::INVALID_ENTITY_TYPE: {
                    return {pos, INVALID_WITH_SYNTAX};
                }
            }
            pos += 3;
        } else if (pos < tokens.size() && tokens[pos].tokenType == INTEGER) {
            switch (withStruct.first_entity) {
                case Entity::READ:
                case Entity::PRINT:
                case Entity::CALL:
                case Entity::WHILE:
                case Entity::IF:
                case Entity::STATEMENT:
                case Entity::ASSIGN:
                case Entity::CONSTANT:{
                    withStruct.second_field_type = ACTUAL_WITH_INTEGER;
                    withStruct.second_name = tokens[pos].nameValue;
                    break;
                }
                case Entity::VARIABLE:
                case Entity::PROCEDURE:
                case Entity::INVALID_ENTITY_TYPE: {
                    return {pos, INVALID_WITH_SYNTAX};
                }
            }
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == NAME) {
            DECLARED_SYNONYM_MAP declarationMap = container.getDeclarationMap();
            auto iterator = declarationMap.find( tokens[pos].nameValue);
            if (iterator == declarationMap.end()) {
                return {pos, UNDECLARED_ENTITY_WITH};
            } else {
                withStruct.second_entity = iterator -> second;
                withStruct.second_name = iterator->first;
                pos++;
            }

            if (pos < tokens.size() && tokens[pos].tokenType != DOT) {
                return {pos, INVALID_WITH_MISSING_DOT};
            }

            pos++;

            if (pos < tokens.size() && tokens[pos].tokenType != NAME) {
                return {pos, INVALID_WITH_SYNTAX};
            }
            std::pair<WithFieldType, Exception> fields = convertStringToWithType(tokens[pos]);
            if (fields.second != VALID) {
                return {pos, INVALID_WITH_FIELD};
            } else {
                withStruct.second_field_type = fields.first;
                // handle stmt#
                if (withStruct.second_field_type == STMT_INTEGER && tokens[pos + 1].tokenType == HASHTAG) {
                    pos++;
                } else {
                    return {pos, INVALID_WITH_SYNTAX};
                }
                pos++;
            }

        } else {
            return {pos, INVALID_WITH_SYNTAX};
        }
        container.addWithClause(withStruct);
        return {pos,VALID};

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
//               support while and if
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

        std::pair<Argument, bool> ARG1 = {{"", Argument::INVALID_ARGUMENT_TYPE}, false},
        ARG2 = {{"", Argument::INVALID_ARGUMENT_TYPE}, false};

        if (pos < tokens.size() && (tokens[pos].tokenType == NAME)) {
            ARG1 = convertStringToRef(tokens[pos], container);
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG1 = {{"_", Argument::WILDCARD}, true};
            pos++;
        } else if (pos + 1 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE
                   && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
            return {pos, INVALID_PATTERN_CONTENT};
        } else if (pos < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE) {
            pos++;
            std::string actualName;
            while (pos < tokens.size() && tokens[pos].tokenType != DOUBLE_QUOTE) {
                actualName += tokens[pos].nameValue;
                pos++;
            }
            ARG1 = {{actualName, Argument::ACTUAL_NAME}, true};
            pos++;
        } else {
            return {pos, INVALID_PATTERN_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == COMMA) {
            pos++;
        } else {
            return {pos, INVALID_PATTERN_SYNTAX};
        }

        // string without doubt quote is invalid for expression
        if (tokens[pos].tokenType == NAME) {
            return {pos, INVALID_PATTERN_CONTENT};
        }

        if (tokens[pos].tokenType == UNDERSCORE) {
            expression += "_";
            pos++;
        }
        if (tokens[pos].tokenType == DOUBLE_QUOTE) {
            pos++;
            while (pos < tokens.size() && tokens[pos].tokenType != DOUBLE_QUOTE) {
                expression += tokens[pos].nameValue;
                pos++;
            }

            // Skip the second double quote as it is handled in the while loop
            if (pos < tokens.size()) {
                pos++;
            } else {
                return {pos, INVALID_PATTERN_CONTENT};
            }

            if (tokens[pos].tokenType == UNDERSCORE) {
                expression += "_";
                pos++;
            }
        } else if (pos + 1 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE
                    && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
            return {pos, INVALID_PATTERN_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == RPAREN) {
            pos++;
        } else {
            return {pos, INVALID_PATTERN_SYNTAX};
        }

        ArgumentStruct aStruct = {expression, Argument::EXPRESSION};
        container.addPatternClause(ASSIGN_PATTERN, assign_syn, ARG1.first, aStruct);
        return {pos, VALID};
    }

    std::pair<int, Exception> parseDeclaration(std::vector<QPS::Token> &tokens,
                                          int pos,
                                          Entity::EntityType entityType,
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
        bool is_boolean_select = false;
        bool is_entity_select = false;
        while (pos < tokens.size()) {
            QPS::Token curr = tokens[pos];
            if (curr.tokenType == QPS::NAME && curr.nameValue == "Select") {
                pos++;
            } else if (curr.tokenType == QPS::NAME && curr.nameValue != "such" && curr.nameValue != "pattern"
                            && curr.nameValue != "BOOLEAN" && !is_boolean_select && curr.nameValue != "with") {
                is_entity_select = true;
                Entity::EntityType entityType = container.getQueryStruct().getDeclaration(curr.nameValue);
                if (entityType != Entity::INVALID_ENTITY_TYPE) {
                    container.addCandidateList(entityType, curr.nameValue);
                    pos++;
                } else {
                    return {pos, UNDECLARED_ENTITY_SUCH_THAT};
                }

            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "BOOLEAN" && !is_entity_select && !is_boolean_select){
                container.addCandidateListBoolean();
                is_boolean_select = true;
                pos++;
            } else if (curr.tokenType == QPS::COMMA && !is_boolean_select){
                pos++;
            } else if (curr.tokenType == QPS::NAME && (curr.nameValue == "such" || curr.nameValue == "pattern" || curr.nameValue == "with")){
                return {pos, VALID};
            } else if (curr.tokenType == GT && !is_boolean_select) {
                pos++;
                is_multiple_select = true;
            } else if (curr.tokenType == LT && !is_boolean_select) {
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
        std::pair<Argument, Exception> ARG1 = {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION},
        ARG2 = {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION};

        if (pos < tokens.size() && tokens[pos].tokenType == LPAREN) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

        if (pos < tokens.size() && (tokens[pos].tokenType == NAME || (tokens[pos].tokenType == INTEGER && tokens[pos].nameValue != "0"))) {
            ARG1 = convertStringToRef(tokens[pos], container);
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG1 = {{ "_", Argument::WILDCARD}, VALID};
            pos++;
        } else if (pos + 1 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
            return {pos, INVALID_RELATION_CONTENT};
        } else {
            return {pos, INVALID_RELATION_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == COMMA) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

       if (pos < tokens.size() && (tokens[pos].tokenType == NAME || (tokens[pos].tokenType == INTEGER && tokens[pos].nameValue != "0"))) {
            ARG2 = convertStringToRef(tokens[pos], container);
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
           return {pos, INVALID_RELATION_CONTENT};
       }  else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG2 = {{ "_", Argument::WILDCARD}, VALID};
            pos++;
        } else {
            return {pos, INVALID_RELATION_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == RPAREN) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }
        container.addSuchThatClause(relationType, ARG1.first, ARG2.first);
        container.setStatus(FINISH_PARSE_SUCH_CLAUSE);
        return {pos, VALID};
    }


    std::pair<int, Exception> parseRelationCalls(std::vector<QPS::Token> &tokens,
                                                   int pos, RelationType relationType,
                                                   Container &container) {
        std::pair<Argument, Exception> ARG1 = {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION},
                ARG2 = {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION};


        if (pos < tokens.size() && tokens[pos].tokenType == LPAREN) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == NAME) {
            ARG1 = convertStringToStmtRefCalls(tokens[pos], container);
            if (ARG1.second != VALID) {
                return {pos, INVALID_RELATION_CONTENT};
            }
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG1 = {{"_", Argument::WILDCARD}, VALID};
            pos++;
        } else if (pos + 2 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+2].tokenType == DOUBLE_QUOTE
                   && tokens[pos + 1].tokenType == NAME) {
            std::string actual_name = tokens[pos + 1].nameValue;
            ARG1 = {{actual_name, Argument::PROCEDURE_ACTUAL_NAME}, VALID};
            pos += 3;
        } else if (pos + 1 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
            return {pos, INVALID_RELATION_CONTENT};
        } else {
            return {pos, INVALID_RELATION_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == COMMA) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == NAME) {
            ARG2 = convertStringToStmtRefCalls(tokens[pos], container);
            if (ARG2.second != VALID) {
                return {pos, INVALID_RELATION_CONTENT};
            }
            pos++;
        } else if (pos + 2 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+2].tokenType == DOUBLE_QUOTE
                   && tokens[pos + 1].tokenType == NAME) {
            std::string actual_name = tokens[pos + 1].nameValue;
            ARG1 = {{actual_name, Argument::PROCEDURE_ACTUAL_NAME}, VALID};
            pos += 3;
        } else if (pos + 1 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
            return {pos, INVALID_RELATION_CONTENT};
        }  else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG2 = {{"_", Argument::WILDCARD}, VALID};
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
        std::pair<Argument, Exception> ARG1 = {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION},
                ARG2 = {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION};
        if (pos < tokens.size() && tokens[pos].tokenType == LPAREN) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

        if (pos < tokens.size() && (tokens[pos].tokenType == NAME || (tokens[pos].tokenType == INTEGER && tokens[pos].nameValue != "0"))) {
            ARG1 = convertStringToRef(tokens[pos], container);

            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG1 = {{ "_", Argument::WILDCARD}, VALID};
            pos++;
        } else if (pos + 2 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+2].tokenType == DOUBLE_QUOTE
                   && tokens[pos + 1].tokenType == NAME) {
            std::string actual_name = tokens[pos + 1].nameValue;
            ARG1 = {{actual_name, Argument::PROCEDURE_ACTUAL_NAME}, VALID};
            pos += 3;
        } else if (pos + 1 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
            return {pos, INVALID_RELATION_CONTENT};
        } else {
            return {pos, INVALID_RELATION_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == COMMA) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

        if (pos + 2 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+2].tokenType == DOUBLE_QUOTE
            && tokens[pos + 1].tokenType == NAME) {
            std::string actual_name = tokens[pos + 1].nameValue;
            ARG2 = {{actual_name, Argument::ACTUAL_NAME}, VALID};
            pos += 3;
        } else if (pos + 1 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+1].tokenType == DOUBLE_QUOTE) {
            return {pos, INVALID_RELATION_CONTENT};
        } else if (pos < tokens.size() && (tokens[pos].tokenType == NAME)) {
            ARG2 = convertStringToRef(tokens[pos], container);
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == UNDERSCORE) {
            ARG2 = {{"_", Argument::WILDCARD}, VALID};
            pos++;
        } else {
            return {pos, INVALID_RELATION_CONTENT};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == RPAREN) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }
        container.setStatus(FINISH_PARSE_SUCH_CLAUSE);
        container.addSuchThatClause(relationType, ARG1.first, ARG2.first);
        return {pos, VALID};
    }

    std::pair<Argument, Exception> convertStringToStmtRefCalls (Token &token, Container &container) {
        if (token.tokenType == NAME) {
            DECLARED_SYNONYM_MAP declarationMap = container.getDeclarationMap();
            auto iterator = declarationMap.find(token.nameValue);
            if (iterator == declarationMap.end()) {
                return {{"", Argument::INVALID_ARGUMENT_TYPE}, UNDECLARED_ENTITY_SUCH_THAT};
            }
            Entity::EntityType entityType = iterator->second;
            if (entityType == Entity::PROCEDURE) {
                return {{token.nameValue, Argument::PROCEDURE_SYNONYM}, VALID};
            } else {
                return {{token.nameValue, Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION_CONTENT};
            }
        } else {
            return {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION_SYNTAX};
        }
    }



    std::pair<Argument, Exception> convertStringToRef (Token &token, Container &container) {
        if (token.tokenType == INTEGER) {
            return {{token.nameValue, Argument::NUMBER}, VALID};
        } else if (token.tokenType == NAME) {
            DECLARED_SYNONYM_MAP declarationMap = container.getDeclarationMap();
            auto iterator = declarationMap.find(token.nameValue);
            if (iterator == declarationMap.end()) {
                return {{"", Argument::INVALID_ARGUMENT_TYPE}, UNDECLARED_ENTITY_SUCH_THAT};
            }
            Entity::EntityType entityType = iterator->second;
            switch (entityType) {
                case Entity::STATEMENT: {
                    return {{token.nameValue, Argument::STMT_SYNONYM}, VALID};
                }
                case Entity::READ: {
                    return {{token.nameValue, Argument::READ_SYNONYM}, VALID};
                }
                case Entity::PRINT: {
                    return {{token.nameValue, Argument::PRINT_SYNONYM}, VALID};
                }
                case Entity::CALL: {
                    return {{token.nameValue, Argument::CALL_SYNONYM}, VALID};
                }
                case Entity::WHILE:{
                    return {{token.nameValue, Argument::WHILE_SYNONYM}, VALID};
                }
                case Entity::IF:{
                    return {{token.nameValue, Argument::IF_SYNONYM}, VALID};
                }
                case Entity::PROCEDURE: {
                    return {{token.nameValue, Argument::PROCEDURE_SYNONYM}, VALID};
                }
                case Entity::ASSIGN:{
                    return {{token.nameValue, Argument::ASSIGN_SYNONYM}, VALID};
                }
                case Entity::VARIABLE:{
                    return {{token.nameValue, Argument::VAR_SYNONYM}, VALID};
                }
                case Entity::CONSTANT:{
                    return {{token.nameValue, Argument::CONST_SYNONYM}, VALID};
                }
                case Entity::INVALID_ENTITY_TYPE:{
                    return {{token.nameValue, Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION_CONTENT};
                }
            }
        } else {
            return {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION_SYNTAX};
        }
    }



    std::pair<WithFieldType, Exception> convertStringToWithType (Token &token) {
        if (token.tokenType != NAME) {
            return {INVALID_WITH_TYPE, INVALID_WITH_TYPE_EXCEPTION};
        }
        std::string field = token.nameValue;
        if (field == "varName") {
            return {VARNAME, VALID};
        } else if (field == "procName") {
            return {PROCNAME, VALID};
        } else if (field == "value") {
            return {CONSTANT_INTEGER, VALID};
        } else if (field == "stmt") {
            return {STMT_INTEGER, VALID};
        } else {
            return {INVALID_WITH_TYPE, INVALID_WITH_TYPE_EXCEPTION};
        }
    }

    std::pair<Entity::EntityType, bool> mapEntity(const QPS::Token& token) {
        if (token.tokenType != QPS::NAME) {
            return {Entity::INVALID_ENTITY_TYPE, false};
        }
        if (Argument::argumentMap.find(token.nameValue) == Argument::argumentMap.end()) {
            // not found
            return {Entity::INVALID_ENTITY_TYPE, false};
        } else {
            // found
            return {Entity::entityMap.at(token.nameValue), true};
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
            if (tokens[pos+1].tokenType != STAR) {
                return {relationMap.at(tokens[pos].nameValue), true};
            }

            if (tokens[pos].nameValue == "Follows") {
                return {FOLLOWS_T, true};
            }
            if (tokens[pos].nameValue == "Parent") {
                return {PARENT_T, true};
            }
            if (tokens[pos].nameValue == "Calls") {
                return {CALLS_P, true};
            }
            if (tokens[pos].nameValue == "Next") {
                return {NEXT_P, true};
            }
            if (tokens[pos].nameValue == "Affects") {
                return {AFFECTS_P, true};
            }
            return {INVALID_RELATION_TYPE, false};
        }
    }



}



