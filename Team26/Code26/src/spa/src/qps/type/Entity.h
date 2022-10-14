#ifndef SPA_ENTITY_H
#define SPA_ENTITY_H

#include <string>
#include <map>
#include "Argument.h"

class Entity {
public:
    enum EntityType {
        STATEMENT,
        READ_ENTITY,
        PRINT_ENTITY,
        CALL_ENTITY,
        WHILE_ENTITY,
        IF_ENTITY,
        ASSIGN_ENTITY,
        VARIABLE,
        CONSTANT,
        PROCEDURE,
        INVALID_ENTITY_TYPE
    };

    static const std::map<std::string, Entity::EntityType> entityMap;

    static Argument::ArgumentType mapToArgument(EntityType entityType);
    static std::string entityToString(Entity::EntityType entityType);
};


#endif //SPA_ENTITY_H
