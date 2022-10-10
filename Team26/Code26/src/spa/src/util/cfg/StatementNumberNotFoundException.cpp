#include "StatementNumberNotFoundException.h"

char *StatementNumberNotFoundException::what() {
    return (char*) "StatementNumber not found when looking up CFG Map";
}
