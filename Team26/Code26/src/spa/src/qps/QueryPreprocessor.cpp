#include "QueryPreprocessor.h"
#include "sp/SourceProcessor.h"

namespace QPS {
    std::pair<int, Exception> parseDeclaration(std::vector<QPS::Token> &tokens,int pos,Entity::EntityType entityType,Container &container);
    std::pair<int, Exception> parseSelect(std::vector<QPS::Token> &tokens, int pos, Container &container);
    std::pair<int, Exception> parseWithObject (std::vector<QPS::Token> &tokens, int pos, Container &container, Argument& argument1, WithClause::WithClauseArgument& arg1);
    std::pair<int, Exception> parseRelation(std::vector<QPS::Token> &tokens, int tokenPos, Container &container, RelationType relationType);
    std::pair<int, Exception> parseEntity(std::vector<QPS::Token> &tokens, int pos, Container &container, Entity::EntityType entityType);
    std::pair<int, Exception> parsePattern(std::vector<QPS::Token> &tokens, int pos, Container &container);
    std::pair<int, Exception> parseRelationStmtStmt(std::vector<QPS::Token> &tokens, int pos, RelationType relationType, Container &container);
    std::pair<int, Exception> parseRelationStmtEnt(std::vector<QPS::Token> &tokens, int pos, RelationType relationType, Container &container);
    std::pair<int, Exception> parseRelationCalls(std::vector<QPS::Token> &tokens, int pos, RelationType relationType, Container &container);
    std::pair<int, Exception> parseWithClause(std::vector<QPS::Token> &tokens, int pos, Container &container);
    std::pair<int, Exception> parseCallArg(std::vector<QPS::Token> &tokens, int pos, std::pair<Argument, Exception>& ARG1, Container &container);
    std::pair<int, Exception> parsePatternExpression (std::vector<QPS::Token> &tokens,int pos,Container &container, std::string &expression,  std::string &trimString);
    std::pair<int, Exception> parsePatternType (std::vector<QPS::Token> &tokens,int pos,Container &container, Argument::ArgumentType &typeOfPattern, std::string &pattern_syn);
    std::pair<int, Exception> parsePatternLeft (std::vector<QPS::Token> &tokens,int pos,Container &container, std::pair<Argument, bool> &ARG1);

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
                std::pair<int, Exception> result = parseEntity(tokens, tokenPos, container, entityMappingResult.first);
                if (result.second == VALID) {
                    tokenPos = result.first;
                } else {
                    return result.second;
                }
            } else if (relationMappingResult.second && container.getStatus() == START_PARSE_SUCH_CLAUSE) {
                // Valid relation
                std::pair<int, Exception> result = parseRelation(tokens, tokenPos, container, relationMappingResult.first);
                if (result.second == VALID) {
                    tokenPos = result.first;
                } else {
                    return result.second;
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

    std::pair<int, Exception> parseEntity(std::vector<QPS::Token> &tokens, int tokenPos, Container &container, Entity::EntityType entityType) {
        std::pair<int, Exception> result;
        tokenPos++;
        switch (entityType) {
            case Entity::STATEMENT: {
                result = parseDeclaration(tokens, tokenPos, Entity::STATEMENT,container);
                break;
            }
            case Entity::READ_ENTITY: {
                result = parseDeclaration(tokens, tokenPos, Entity::READ_ENTITY,container);
                break;
            }
            case Entity::PRINT_ENTITY: {
                result = parseDeclaration(tokens, tokenPos, Entity::PRINT_ENTITY,container);
                break;
            }
            case Entity::CALL_ENTITY: {
                result = parseDeclaration(tokens, tokenPos, Entity::CALL_ENTITY,container);
                break;
            }
            case Entity::WHILE_ENTITY: {
                result = parseDeclaration(tokens, tokenPos, Entity::WHILE_ENTITY,container);
                break;
            }
            case Entity::IF_ENTITY: {
                result = parseDeclaration(tokens, tokenPos, Entity::IF_ENTITY,container);
                break;
            }
            case Entity::ASSIGN_ENTITY: {
                result = parseDeclaration(tokens, tokenPos, Entity::ASSIGN_ENTITY,container);
                break;
            }
            case Entity::VARIABLE: {
                result = parseDeclaration(tokens, tokenPos,Entity::VARIABLE,container);
                break;
            }
            case Entity::CONSTANT:{
                result = parseDeclaration(tokens, tokenPos,Entity::CONSTANT,container);
                break;
            }
            case Entity::PROCEDURE: {
                result = parseDeclaration(tokens, tokenPos,Entity::PROCEDURE,container);
                break;
            }
            case Entity::INVALID_ENTITY_TYPE: {
                return {tokenPos, INVALID_ENTITY};
            }
        }

        if (result.second == VALID) {
            tokenPos = result.first;
            return {tokenPos, VALID};
        } else {
            // Invalid query
            return {tokenPos, result.second};
        }
    }


    std::pair<int, Exception> parseRelation(std::vector<QPS::Token> &tokens, int tokenPos, Container &container, RelationType relationType) {
        std::pair<int, Exception> result;
        tokenPos++;
        switch (relationType) {
            case FOLLOWS: {
                result = parseRelationStmtStmt(tokens, tokenPos,FOLLOWS, container);
                break;
            }
            case FOLLOWS_T: {
                tokenPos += 1;
                result = parseRelationStmtStmt(tokens, tokenPos,FOLLOWS_T, container);
                break;
            }
            case PARENT: {
                result = parseRelationStmtStmt(tokens, tokenPos,PARENT, container);
                break;
            }
            case PARENT_T: {
                tokenPos += 1;
                result = parseRelationStmtStmt(tokens, tokenPos,PARENT_T, container);
                break;
            }
            case USES_S: {
                result = parseRelationStmtEnt(tokens, tokenPos,USES_S, container);
                break;
            }
            case MODIFIES_S:{
                result = parseRelationStmtEnt(tokens, tokenPos,MODIFIES_S, container);
                break;
            }
            case USES_P: {
                result = parseRelationStmtEnt(tokens, tokenPos,USES_P, container);
                break;
            }
            case MODIFIES_P:{
                result = parseRelationStmtEnt(tokens, tokenPos,MODIFIES_P, container);
                break;
            }
            case CALLS:{
                result = parseRelationCalls(tokens, tokenPos,CALLS, container);
                break;
            }
            case CALLS_T:{
                tokenPos += 1;
                result = parseRelationCalls(tokens, tokenPos,CALLS_T, container);
                break;
            }
            case NEXT:{
                result = parseRelationStmtStmt(tokens, tokenPos,NEXT, container);
                break;
            }
            case NEXT_T:{
                tokenPos += 1;
                result = parseRelationStmtStmt(tokens, tokenPos,NEXT_T, container);
                break;
            }
            case AFFECTS:{
                result = parseRelationStmtStmt(tokens, tokenPos,AFFECTS, container);
                break;
            }
            case AFFECTS_T:{
                tokenPos += 1;
                result = parseRelationStmtStmt(tokens, tokenPos,AFFECTS_T, container);
                break;
            }
            case INVALID_RELATION_TYPE: {
                return {tokenPos, INVALID_RELATION};
            }
        }
        if (result.second == VALID) {
            tokenPos = result.first - 1;
            return {tokenPos, VALID};
        } else {
            // Invalid query
            return {tokenPos, result.second};
        }
    }

    std::pair<int, Exception> parseWithObject (std::vector<QPS::Token> &tokens, int pos, Container &container, Argument& argument1, WithClause::WithClauseArgument& arg1) {
        if (pos < tokens.size() && tokens[pos].tokenType == NAME) {
            Argument::ArgumentType argumentType = container.getSynonymType(tokens[pos].nameValue);
            if (argumentType == Argument::INVALID_ARGUMENT_TYPE) {
                return {pos, UNDECLARED_ENTITY_WITH};
            }
            argument1 = Argument(tokens[pos].nameValue, argumentType);
            pos++;
        } else {
            return {pos, INVALID_WITH_SYNTAX};
        }

        if (pos < tokens.size() && tokens[pos].tokenType != DOT) {
            return {pos, INVALID_WITH_MISSING_DOT};
        }

        pos++;

        if (pos < tokens.size() && tokens[pos].tokenType == NAME) {
            std::pair<AttributeType, Exception> fields = convertStringToWithType(tokens[pos]);
            if (fields.second != VALID) {
                return {pos, INVALID_WITH_FIELD};
            } else {
                arg1 = {argument1, fields.first};
                // handle stmt#
                if (fields.first == STMT_LINE_NUMBER && tokens[pos + 1].tokenType == HASHTAG) {
                    pos++;
                } else if (fields.first == STMT_LINE_NUMBER) {
                    return {pos, INVALID_WITH_SYNTAX};
                }
                pos++;
            }
        }
        return {pos, VALID};
    }

    std::pair<int, Exception> parseWithClause(std::vector<QPS::Token> &tokens, int pos, Container &container) {
        WithClause::WithClauseArgument arg1, arg2;
        Argument argument1, argument2;
        std::pair<int, Exception> result = parseWithObject(tokens, pos, container, argument1, arg1);
        if (result.second == VALID) {
            pos = result.first;
        } else {
            return {pos, result.second};
        }

        if (pos < tokens.size() && tokens[pos].tokenType != SINGLE_EQ) {
            return {pos, INVALID_WITH_SYNTAX};
        }
        pos++;

        //p.procName = "xxx"
        if (pos + 2 < tokens.size() && tokens[pos].tokenType == DOUBLE_QUOTE && tokens[pos+2].tokenType == DOUBLE_QUOTE
            && (tokens[pos + 1].tokenType == NAME)) {
            switch (arg1.argument.argumentType) {
                case Argument::READ_SYNONYM:
                case Argument::PRINT_SYNONYM:
                case Argument::VAR_SYNONYM:
                case Argument::CALL_SYNONYM:
                case Argument::PROCEDURE_SYNONYM:{
                    argument2 = Argument(tokens[pos + 1].nameValue, Argument::ACTUAL_NAME);
                    arg2 = {argument2, INAPPLICABLE};
                    break;
                }
                case Argument::ACTUAL_NAME:
                case Argument::NUMBER:
                case Argument::WILDCARD:
                case Argument::EXPRESSION:
                case Argument::PROCEDURE_ACTUAL_NAME:
                case Argument::BOOLEAN_ARG:
                case Argument::WHILE_SYNONYM:
                case Argument::IF_SYNONYM:
                case Argument::STMT_SYNONYM:
                case Argument::ASSIGN_SYNONYM:
                case Argument::CONST_SYNONYM:
                case Argument::INVALID_ARGUMENT_TYPE: {
                    return {pos, INVALID_WITH_SYNTAX};
                }

            }
            pos += 3;
        } else if (pos < tokens.size() && tokens[pos].tokenType == INTEGER) {
            switch (arg1.argument.argumentType) {
                case Argument::READ_SYNONYM:
                case Argument::PRINT_SYNONYM:
                case Argument::CALL_SYNONYM:
                case Argument::WHILE_SYNONYM:
                case Argument::IF_SYNONYM:
                case Argument::STMT_SYNONYM:
                case Argument::ASSIGN_SYNONYM:
                case Argument::CONST_SYNONYM:{
                    argument2 = Argument(tokens[pos + 1].nameValue, Argument::NUMBER);
                    arg2 = {argument2, INAPPLICABLE};
                    break;
                }
                case Argument::ACTUAL_NAME:
                case Argument::NUMBER:
                case Argument::WILDCARD:
                case Argument::EXPRESSION:
                case Argument::PROCEDURE_ACTUAL_NAME:
                case Argument::BOOLEAN_ARG:
                case Argument::VAR_SYNONYM:
                case Argument::PROCEDURE_SYNONYM:
                case Argument::INVALID_ARGUMENT_TYPE: {
                    return {pos, INVALID_WITH_SYNTAX};
                }

            }
            pos++;
        } else if (pos < tokens.size() && tokens[pos].tokenType == NAME) {
            result = parseWithObject(tokens, pos, container, argument1, arg1);
            if (result.second == VALID) {
                pos = result.first;
            } else {
                return {pos, result.second};
            }

        } else {
            return {pos, INVALID_WITH_SYNTAX};
        }
        container.addWithClause(arg1, arg2);
        return {pos,VALID};

    }

    std::pair<int, Exception> parsePatternExpression (std::vector<QPS::Token> &tokens,int pos,Container &container, std::string &expression, std::string &trimString) {
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
                trimString += tokens[pos].nameValue;
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

        return {pos, VALID};
    }

    std::pair<int, Exception> parsePatternType (std::vector<QPS::Token> &tokens,int pos,Container &container, Argument::ArgumentType &typeOfPattern, std::string &pattern_syn) {
        if (pos < tokens.size() && tokens[pos].tokenType == NAME) {
            Argument::ArgumentType argumentType = container.getSynonymType(tokens[pos].nameValue);
            if (argumentType == Argument::INVALID_ARGUMENT_TYPE) {
                return {pos, UNDECLARED_ENTITY_WITH};
            } else if (argumentType == Argument::ASSIGN_SYNONYM || argumentType == Argument::IF_SYNONYM || argumentType == Argument::WHILE_SYNONYM) {
                pattern_syn = tokens[pos].nameValue;
                typeOfPattern = argumentType;
                pos++;
            } else {
                return {pos, INVALID_PATTERN_TYPE};
            }
        } else {
            return {pos, INVALID_PATTERN_TYPE};
        }
        return {pos, VALID};
    }

    std::pair<int, Exception> parsePatternLeft (std::vector<QPS::Token> &tokens,int pos,Container &container, std::pair<Argument, bool> &ARG1) {
        if (pos < tokens.size() && (tokens[pos].tokenType == NAME)) {
            ARG1 = convertStringToARG(tokens[pos], container);
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
        return {pos, VALID};
    }

    std::pair<int, Exception> parsePattern (std::vector<QPS::Token> &tokens,int pos,Container &container) {
        std::string pattern_syn;
        std::string expression;
        std::string trimmedString;
        Argument::ArgumentType typeOfPattern;
        std::pair<int, Exception> result = parsePatternType(tokens, pos, container, typeOfPattern, pattern_syn);
        if (result.second == VALID) {
            pos = result.first;
        } else {
            return {pos, result.second};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == LPAREN) {
            pos++;
        } else {
            return {pos, INVALID_PATTERN_SYNTAX};
        }

        std::pair<Argument, bool> ARG1 = {{"", Argument::INVALID_ARGUMENT_TYPE}, false};

        result = parsePatternLeft(tokens, pos, container, ARG1);
        if (result.second == VALID) {
            pos = result.first;
        } else {
            return {pos, result.second};
        }


        if (pos < tokens.size() && tokens[pos].tokenType == COMMA) {
            pos++;
        } else {
            return {pos, INVALID_PATTERN_SYNTAX};
        }

        result = parsePatternExpression(tokens, pos, container, expression, trimmedString);
        if (result.second == VALID) {
            pos = result.first;
        } else {
            return {pos, result.second};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == RPAREN) {
            pos++;
        } else {
            return {pos, INVALID_PATTERN_SYNTAX};
        }

        if (!trimmedString.empty()  && !SourceProcessor::checkExpressionString(trimmedString)) {
            return {pos, INVALID_PATTERN_SYNTAX};
        }

        container.addPatternClause(typeOfPattern, pattern_syn, ARG1.first, Argument(expression, Argument::EXPRESSION));
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
            } else if (curr.tokenType == QPS::NAME) {
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
        bool is_select_parsed = false;
        while (pos < tokens.size()) {
            QPS::Token curr = tokens[pos];
            if (curr.tokenType == QPS::NAME && curr.nameValue == "Select" && !is_select_parsed) {
                is_select_parsed = true;
                pos++;
            } else if (curr.tokenType == QPS::NAME && curr.nameValue != "such" && curr.nameValue != "pattern"
                            && curr.nameValue != "BOOLEAN" && !is_boolean_select && curr.nameValue != "with") {
                is_entity_select = true;

                Argument::ArgumentType argumentType = container.getSynonymType(curr.nameValue);
                if (argumentType == Argument::INVALID_ARGUMENT_TYPE) {
                    return {pos, UNDECLARED_SELECT_ENTITY};
                }
                container.addCandidateList(argumentType, curr.nameValue);
                pos++;

            } else if (curr.tokenType == QPS::NAME && curr.nameValue == "BOOLEAN" && !is_entity_select && !is_boolean_select){
                container.addCandidateListBoolean();
                is_boolean_select = true;
                pos++;
            } else if (curr.tokenType == QPS::COMMA && !is_boolean_select && is_multiple_select){
                pos++;
            } else if (curr.tokenType == QPS::NAME && (curr.nameValue == "such" || curr.nameValue == "pattern" || curr.nameValue == "with")){
                return {pos, VALID};
            } else if (curr.tokenType == GT && !is_boolean_select) {
                pos++;
                is_closed = true;
                break;
            } else if (curr.tokenType == LT && !is_boolean_select) {
                pos++;
                is_multiple_select = true;
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
            ARG1 = convertStringToARG(tokens[pos], container);
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
            ARG2 = convertStringToARG(tokens[pos], container);
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

    std::pair<int, Exception> parseCallArg(std::vector<QPS::Token> &tokens, int pos, std::pair<Argument, Exception>& ARG1, Container &container) {
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
        return {pos, VALID};
    }


    std::pair<int, Exception> parseRelationCalls(std::vector<QPS::Token> &tokens, int pos, RelationType relationType, Container &container) {
        std::pair<Argument, Exception> ARG1 = {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION},
                ARG2 = {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION};


        if (pos < tokens.size() && tokens[pos].tokenType == LPAREN) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }
        std::pair<int, Exception> result = parseCallArg(tokens, pos, ARG1, container);
        if (result.second == VALID) {
            pos = result.first;
        } else {
            return {pos, result.second};
        }

        if (pos < tokens.size() && tokens[pos].tokenType == COMMA) {
            pos++;
        } else {
            return {pos, INVALID_RELATION_SYNTAX};
        }

        result = parseCallArg(tokens, pos, ARG2, container);
        if (result.second == VALID) {
            pos = result.first;
        } else {
            return {pos, result.second};
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
            ARG1 = convertStringToARG(tokens[pos], container);

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
            ARG2 = convertStringToARG(tokens[pos], container);
            if (ARG2.second != VALID) {
                return {pos, ARG2.second};
            }
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

            Argument::ArgumentType argumentType = container.getSynonymType(token.nameValue);
            if (argumentType == Argument::INVALID_ARGUMENT_TYPE) {
                return {{"", Argument::INVALID_ARGUMENT_TYPE}, UNDECLARED_ENTITY_SUCH_THAT};
            }

            if (argumentType == Argument::PROCEDURE_SYNONYM) {
                return {{token.nameValue, Argument::PROCEDURE_SYNONYM}, VALID};
            } else {
                return {{token.nameValue, Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION_CONTENT};
            }
        } else {
            return {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION_SYNTAX};
        }
    }



    std::pair<Argument, Exception> convertStringToARG (Token &token, Container &container) {
        if (token.tokenType == INTEGER) {
            return {{token.nameValue, Argument::NUMBER}, VALID};
        } else if (token.tokenType == NAME) {
            Argument::ArgumentType argumentType = container.getSynonymType(token.nameValue);
            if (argumentType == Argument::INVALID_ARGUMENT_TYPE) {
                return {{"", Argument::INVALID_ARGUMENT_TYPE}, UNDECLARED_ENTITY_SUCH_THAT};
            }
            return {{token.nameValue, argumentType}, VALID};
        } else {
            return {{"", Argument::INVALID_ARGUMENT_TYPE}, INVALID_RELATION_SYNTAX};
        }
    }



    std::pair<AttributeType, Exception> convertStringToWithType (Token &token) {
        if (token.tokenType != NAME) {
            return {INVALID_ATTR_TYPE, INVALID_WITH_TYPE_EXCEPTION};
        }
        std::string field = token.nameValue;
        if (field == "varName") {
            return {WITH_VAR_NAME, VALID};
        } else if (field == "procName") {
            return {PROC_NAME, VALID};
        } else if (field == "value") {
            return {WITH_CONST_VALUE, VALID};
        } else if (field == "stmt") {
            return {STMT_LINE_NUMBER, VALID};
        } else {
            return {INVALID_ATTR_TYPE, INVALID_WITH_TYPE_EXCEPTION};
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
                return {CALLS_T, true};
            }
            if (tokens[pos].nameValue == "Next") {
                return {NEXT_T, true};
            }
            if (tokens[pos].nameValue == "Affects") {
                return {AFFECTS_T, true};
            }
            return {INVALID_RELATION_TYPE, false};
        }
    }



}



