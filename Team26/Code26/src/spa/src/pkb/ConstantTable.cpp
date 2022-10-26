//
// Created by QMS on 4/9/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include "ConstantTable.h"

using namespace std;

void ConstantTable::insertConst(int constant) {
    this->constList.push_back(constant);
}

vector<string> ConstantTable::getAllConstants() {
    vector<string> result;
    for (int c: this->constList) {
        result.push_back(std::to_string(c));
    }
    return result;
}

