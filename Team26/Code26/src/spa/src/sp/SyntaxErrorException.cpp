#include "SyntaxErrorException.h"

char *SyntaxErrorException::what() {
    return "Concrete Syntax Violated!";
}
