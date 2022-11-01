#include "CFGNotInitializedException.h"

char *CFGNotInitializedException::what() {
    return (char*) "CFG has not been initialized yet and contains 0 nodes";
}
