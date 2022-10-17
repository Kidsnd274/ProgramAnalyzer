#include "ProcedureNotFoundException.h"

char *ProcedureNotFoundException::what() {
    return (char*) "Procedure not found in the Procedure Table!";
}
