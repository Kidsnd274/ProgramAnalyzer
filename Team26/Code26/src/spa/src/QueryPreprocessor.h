#include <utility>
#include "Tokenizer.h"
#include "QueryProcessorTypes.h"

#ifndef SPA_QUERYPREPROCESSOR_H
#define SPA_QUERYPREPROCESSOR_H

#endif //SPA_QUERYPREPROCESSOR_H

namespace QueryPreprocessor{
    std::pair<QueryProcessorTypes::EntityType, bool> mapEntity(Tokenization::Token token);
    std::pair<QueryProcessorTypes::RelationType, bool> mapRelation(Tokenization::Token token);
    void parseToken(std::vector<Tokenization::Token> tokens);
}