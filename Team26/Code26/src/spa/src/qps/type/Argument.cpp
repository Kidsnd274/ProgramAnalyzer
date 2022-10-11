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


