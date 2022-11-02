#include "EndOfFileException.h"

char *EndOfFileException::what() {
    return const_cast<char*>("No more tokens left!");
}
