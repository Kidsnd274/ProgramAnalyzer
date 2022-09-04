#ifndef SPA_QUERYPREPROCESSOR_H
#define SPA_QUERYPREPROCESSOR_H

#include <utility>
#include <map>
#include <iostream>
#include "QueryProcessorTypes.h"
#include "Tokenizer.h"

namespace QPS {
    std::pair<EntityType, bool> mapEntity(Token token);
    std::pair<RelationType, bool> mapRelation(Token token);
    void parseToken(std::vector<Token> &tokens);
}


#endif //SPA_QUERYPREPROCESSOR_H