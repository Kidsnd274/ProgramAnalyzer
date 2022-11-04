#pragma once

#include <exception>
class SyntaxErrorException : std::exception {
public:
    char * what();
};
