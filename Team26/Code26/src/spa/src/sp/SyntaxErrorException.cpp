#include "SyntaxErrorException.h"

char *SyntaxErrorException::what() {
    return const_cast<char*>("Concrete Syntax Violated!");
}
