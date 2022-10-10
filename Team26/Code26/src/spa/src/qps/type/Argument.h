#ifndef SPA_ARGUMENT_H
#define SPA_ARGUMENT_H

#include <string>

class Argument {
public:
    enum ArgumentType {
        IF_SYNONYM,
        WHILE_SYNONYM,
        READ_SYNONYM,
        PRINT_SYNONYM,
        CALL_SYNONYM,
        ASSIGN_SYNONYM,
        STMT_SYNONYM,
        VAR_SYNONYM,
        PROCEDURE_SYNONYM,
        CONST_SYNONYM,
        ACTUAL_NAME,
        NUMBER,
        WILDCARD,
        EXPRESSION,
        INVALID_ARGUMENT_TYPE,
        PROCEDURE_ACTUAL_NAME
    };

public:
    std::string argumentName;
    ArgumentType argumentType;

public:
    Argument(std::string argumentName, ArgumentType argumentType) {
        this->argumentName = argumentName;
        this->argumentType = argumentType;
    }
};


#endif //SPA_ARGUMENT_H
