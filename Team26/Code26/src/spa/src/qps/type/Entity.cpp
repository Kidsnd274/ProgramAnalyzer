#include "Entity.h"

const std::map<std::string, Entity::EntityType> entityMap = {{"stmt",      Entity::STATEMENT},
                                                            {"read",      Entity::READ},
                                                            {"print",     Entity::PRINT},
                                                            {"call",      Entity::CALL},
                                                            {"while",     Entity::WHILE},
                                                            {"if",        Entity::IF},
                                                            {"assign",    Entity::ASSIGN},
                                                            {"variable",  Entity::VARIABLE},
                                                            {"constant",  Entity::CONSTANT},
                                                            {"procedure", Entity::PROCEDURE},
                                                            {"",          Entity::INVALID_ENTITY_TYPE}};


Argument::ArgumentType Entity::mapToArgument(Entity::EntityType entityType) {
    switch (entityType) {

        case Entity::STATEMENT: {
            return Argument::STMT_SYNONYM;
        }
        case Entity::READ:{
            return Argument::READ_SYNONYM;
        }
        case Entity::PRINT:{
            return Argument::PRINT_SYNONYM;
        }
        case Entity::CALL:{
            return Argument::CALL_SYNONYM;
        }
        case Entity::WHILE:{
            return Argument::WHILE_SYNONYM;
        }
        case Entity::IF:{
            return Argument::IF_SYNONYM;
        }
        case Entity::ASSIGN:{
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
