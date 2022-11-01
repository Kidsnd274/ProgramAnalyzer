#pragma once

#include <exception>

class CFGNotInitializedException : std::exception {
public:
    char * what();
};
