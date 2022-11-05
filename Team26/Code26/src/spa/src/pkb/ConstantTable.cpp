//
// Created by QMS on 4/9/2022.
//
#include <stdio.h>
#include <string>
#include <unordered_set>
#include "ConstantTable.h"

using namespace std;

void ConstantTable::insertConst(int constant) {
    this->constList.insert(constant);
}

unordered_set<string> ConstantTable::getAllConstants() {
    unordered_set<string> result;
    for (int c: this->constList) {
        result.insert(std::to_string(c));
    }
    return result;
}

void ConstantTable::clear() {
    this->constList.clear();
}
