#include "Clause.h"

bool Clause::isValid() {
    return false;
}

Argument Clause::getFirstArgument() {
    return Argument("", Argument::INVALID_ARGUMENT_TYPE);
}

Argument Clause::getSecondArgument() {
    return Argument("", Argument::INVALID_ARGUMENT_TYPE);
}
