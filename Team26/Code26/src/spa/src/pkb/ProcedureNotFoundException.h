#pragma once

#include <exception>
class ProcedureNotFoundException : std::exception {
public:
    char * what ();
};
