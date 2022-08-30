#include <map>
#include "Tokenizer.h"
#include "QueryHandler.h"

void parseToken(std::vector<Tokenization::Token> tokens) {
    for (Tokenization::Token token : tokens) {

    }
}



std::pair<EntityType, bool> parseEntity(Tokenization::Token token) {
    if (entityMap.find(token.nameValue) == entityMap.end()) {
        // not found
        return {INVALID_ENTITY, false};
    } else {
        // found
        return {entityMap.at(token.nameValue), true};
    }
}

std::pair<RelationType, bool> parseRelation(Tokenization::Token token) {
    if (relationMap.find(token.nameValue) == relationMap.end()) {
        // not found
        return {INVALID_RELATION, false};
    } else {
        // found
        return {relationMap.at(token.nameValue), true};
    }
}