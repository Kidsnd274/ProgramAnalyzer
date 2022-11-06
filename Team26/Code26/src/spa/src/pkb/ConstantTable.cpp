#include "ConstantTable.h"

void ConstantTable::insertConst(int constant) {
    this->constList.push_back(constant);
}

std::vector<std::string> ConstantTable::getAllConstants() {
    std::vector<std::string> result;
    for (int c : this->constList) {
        result.push_back(std::to_string(c));
    }
    return result;
}

void ConstantTable::clear() {
    this->constList.clear();
}
