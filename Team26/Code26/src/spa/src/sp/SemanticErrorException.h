#pragma once

#include <exception>
#include <string>
class SemanticErrorException : std::exception {
private:
    std::string errorMsg;
public:
    explicit SemanticErrorException(std::string err) {
        errorMsg = err;
    }

    char * what();
};
