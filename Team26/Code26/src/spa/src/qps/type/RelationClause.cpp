#include "RelationClause.h"

Argument RelationClause::getFirstArgument() {
    return this->argument1;
}

Argument RelationClause::getSecondArgument() {
    return this->argument2;
};

void RelationClause::setFirstArgument(const Argument& argument) {
    this->argument1 = argument;
}

void RelationClause::setSecondArgument(const Argument& argument) {
    this->argument2 = argument;
}
