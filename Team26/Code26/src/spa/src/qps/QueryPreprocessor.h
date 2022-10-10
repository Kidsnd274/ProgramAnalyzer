#ifndef SPA_QUERYPREPROCESSOR_H
#define SPA_QUERYPREPROCESSOR_H

#include <utility>
#include <map>
#include <iostream>
#include "QueryProcessorTypes.h"
#include "Container.h"
#include "QueryManager.h"
#include "Tokenizer.h"

namespace QPS {
    std::pair<EntityType, bool> mapEntity(const Token& token);
    std::pair<RelationType, bool> mapRelation(std::vector<QPS::Token> &tokens, int pos);
    std::pair<ArgumentStruct, bool> convertStringToARG (Token &token, Container &container);
    std::pair<ArgumentStruct, Exception> convertStringToStmtRef (Token &token, Container &container);
    Exception parseToken(std::vector<Token> &tokens, Container &container);
    std::pair<ArgumentStruct, Exception> convertStringToEntRef (Token &token, Container &container);
    std::pair<ArgumentStruct, Exception> convertStringToStmtRefUM (Token &token, Container &container);
    std::pair<ArgumentStruct, Exception> convertStringToStmtRefCalls (Token &token, Container &container);
    std::pair<WithFieldType, Exception> convertStringToWithType (Token &token);
}


#endif //SPA_QUERYPREPROCESSOR_H