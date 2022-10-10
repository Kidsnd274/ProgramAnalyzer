#pragma once

#include <exception>

class StatementNumberNotFoundException : std::exception {
public:
    char * what();
};