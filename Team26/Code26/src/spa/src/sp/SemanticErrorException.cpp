#include "SemanticErrorException.h"

char *SemanticErrorException::what() {
    return reinterpret_cast<char*>(errorMsg.data());
}
