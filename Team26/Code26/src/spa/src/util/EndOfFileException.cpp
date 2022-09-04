#include "EndOfFileException.h"

char *EndOfFileException::what() {
    return (char *) "No more tokens left!";
}