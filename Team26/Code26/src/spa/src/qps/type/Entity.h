#ifndef SPA_ENTITY_H
#define SPA_ENTITY_H

#include <string>
#include <map>
#include "Argument.h"

class Entity {
public:
    enum EntityType {
        STATEMENT,
        READ,
        PRINT,
        CALL,
        WHILE,
        IF,
        ASSIGN,
        VARIABLE,
        CONSTANT,
        PROCEDURE,
        INVALID_ENTITY_TYPE
    };

    const static std::map<std::string, EntityType> entityMap;

    static Argument::ArgumentType mapToArgument(EntityType entityType);
    static std::string entityToString(Entity::EntityType entityType);
};


#endif //SPA_ENTITY_H
