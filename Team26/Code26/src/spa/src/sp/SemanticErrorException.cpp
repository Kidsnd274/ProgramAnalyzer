#include "SemanticErrorException.h"

char *SemanticErrorException::what() {
    return (char*) errorMsg.data();
}