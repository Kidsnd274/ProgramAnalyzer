#include "CFGNotInitializedException.h"

char *CFGNotInitializedException::what() {
    return const_cast<char*>("CFG has not been initialized yet and contains 0 nodes");
}
