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

bool RelationClause::isValid() {
//    auto iter = RelationClause::validationTable.find(this->argument1.argumentType);
//    if (iter != RelationClause::validationTable.end()) {
//        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
//            return true;
//        }
//    }
    return false;
}