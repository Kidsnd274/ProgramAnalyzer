#include "StatementNumberNotFoundException.h"

char *StatementNumberNotFoundException::what() {
    return const_cast<char*>("StatementNumber not found when looking up CFG Map");
}
