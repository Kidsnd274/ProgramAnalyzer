#include "ConstantTable.h"

void ConstantTable::insertConst(int constant) {
    this->constList.insert(constant);
}

std::unordered_set<std::string> ConstantTable::getAllConstants() {
    std::unordered_set<std::string> result;
    for (int c: this->constList) {
        result.insert(std::to_string(c));
    }
    return result;
}

void ConstantTable::clear() {
    this->constList.clear();
}
