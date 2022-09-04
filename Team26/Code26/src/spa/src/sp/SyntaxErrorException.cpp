#include "SyntaxErrorException.h"

char *SyntaxErrorException::what() {
    return (char *)"Concrete Syntax Violated!";
}
