#include "Entity.h"

const std::map<std::string, Entity::EntityType> Entity::entityMap = {{"stmt",      Entity::STATEMENT},
                                                             {"read",      Entity::READ_ENTITY},
                                                             {"print",     Entity::PRINT_ENTITY},
                                                             {"call",      Entity::CALL_ENTITY},
                                                             {"while",     Entity::WHILE_ENTITY},
                                                             {"if",        Entity::IF_ENTITY},
                                                             {"assign",    Entity::ASSIGN_ENTITY},
                                                             {"variable",  Entity::VARIABLE},
                                                             {"constant",  Entity::CONSTANT},
                                                             {"procedure", Entity::PROCEDURE},
                                                             {"",          Entity::INVALID_ENTITY_TYPE}};

Argument::ArgumentType Entity::mapToArgument(Entity::EntityType entityType) {
    switch (entityType) {

        case Entity::STATEMENT: {
            return Argument::STMT_SYNONYM;
        }
        case Entity::READ_ENTITY:{
            return Argument::READ_SYNONYM;
        }
        case Entity::PRINT_ENTITY:{
            return Argument::PRINT_SYNONYM;
        }
        case Entity::CALL_ENTITY:{
            return Argument::CALL_SYNONYM;
        }
        case Entity::WHILE_ENTITY:{
            return Argument::WHILE_SYNONYM;
        }
        case Entity::IF_ENTITY:{
            return Argument::IF_SYNONYM;
        }
        case Entity::ASSIGN_ENTITY:{
            return Argument::ASSIGN_SYNONYM;
        }
        case Entity::VARIABLE:{
            return Argument::VAR_SYNONYM;
        }
        case Entity::CONSTANT:{
            return Argument::CONST_SYNONYM;
        }
        case Entity::PROCEDURE:{
            return Argument::PROCEDURE_SYNONYM;
        }
        case Entity::INVALID_ENTITY_TYPE:{
            return Argument::INVALID_ARGUMENT_TYPE;
        }
    }
}

std::string Entity::entityToString(Entity::EntityType entityType) {
    switch (entityType) {
        case Entity::STATEMENT: {
            return "stmt";
        }
        case Entity::READ_ENTITY: {
            return "read";
        }
        case Entity::PRINT_ENTITY: {
            return "print";
        }
        case Entity::CALL_ENTITY: {
            return "call";
        }
        case Entity::WHILE_ENTITY: {
            return "while";
        }
        case Entity::IF_ENTITY: {
            return "if";
        }
        case Entity::ASSIGN_ENTITY: {
            return "assign";
        }
        case Entity::VARIABLE: {
            return "variable";
        }

        case Entity::CONSTANT: {
            return "constant";
        }
        case Entity::PROCEDURE: {
            return "procedure";
        }
        case Entity::INVALID_ENTITY_TYPE:
            return "invalid";

    }
}

