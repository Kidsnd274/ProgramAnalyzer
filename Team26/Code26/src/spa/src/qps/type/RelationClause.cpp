#include "RelationClause.h"

Argument RelationClause::getFirstArgument() {
    return this.argument1;
}

Argument RelationClause::getSecondArgument() {
    return this->argument2;
};

void RelationClause::setFirstArgument(Argument argument) {
    this->argument1 = argument;
}

void RelationClause::setSecondArgument(Argument argument) {
    this->argument2 = argument;
}

bool RelationClause::isValid() {
    return false;
}