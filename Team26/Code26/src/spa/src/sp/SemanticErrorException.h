#pragma once

#include <exception>
#include <string>
class SemanticErrorException : std::exception {
private:
    std::string errorMsg;
public:
    SemanticErrorException(std::string err) {
        errorMsg = err;
    }

    char * what();
};
