#include "Argument.h"

const std::map<std::string, Argument::ArgumentType> Argument::argumentMap = {
        {"stmt",      STMT_SYNONYM},
        {"read",      READ_SYNONYM},
        {"print",     PRINT_SYNONYM},
        {"call",      CALL_SYNONYM},
        {"while",     WHILE_SYNONYM},
        {"if",        IF_SYNONYM},
        {"assign",    ASSIGN_SYNONYM},
        {"variable",  VAR_SYNONYM},
        {"constant",  CONST_SYNONYM},
        {"procedure", PROCEDURE_SYNONYM},
        {"",          INVALID_ARGUMENT_TYPE}
};

bool Argument::isSynonym(Argument::ArgumentType argumentType) {
    switch (argumentType) {
        case STMT_SYNONYM:
        case READ_SYNONYM:
        case PRINT_SYNONYM:
        case CALL_SYNONYM:
        case WHILE_SYNONYM:
        case IF_SYNONYM:
        case ASSIGN_SYNONYM:
        case VAR_SYNONYM:
        case CONST_SYNONYM:
        case PROCEDURE_SYNONYM:
            return true;
        default:
            return false;
    }
}
