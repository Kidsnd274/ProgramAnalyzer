#ifndef SPA_QUERYPREPROCESSOR_H
#define SPA_QUERYPREPROCESSOR_H

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "QueryProcessorTypes.h"
#include "Container.h"
#include "Tokenizer.h"

namespace QPS {
    std::pair<Entity::EntityType, bool> mapEntity(const Token& token);
    std::pair<RelationType, bool> mapRelation(std::vector<QPS::Token> &tokens, int pos);
    std::pair<Argument, Exception> convertStringToARG(Token &token, Container &container);
    Exception parseToken(std::vector<Token> &tokens, Container &container);
    std::pair<Argument, Exception> convertStringToStmtRefCalls(Token &token, Container &container);
    std::pair<AttributeType, Exception> convertStringToWithType(Token &token);
}

#endif  // SPA_QUERYPREPROCESSOR_H
