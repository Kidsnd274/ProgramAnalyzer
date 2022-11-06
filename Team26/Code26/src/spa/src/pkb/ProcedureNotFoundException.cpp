#include "ProcedureNotFoundException.h"

char *ProcedureNotFoundException::what() {
    return const_cast<char*>("Procedure not found in the Procedure Table!");
}
