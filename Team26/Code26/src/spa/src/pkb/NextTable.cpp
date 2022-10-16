#include "NextTable.h"

void NextTable::insertNext(int frontStmtLineNumber, int backStmtLineNumber) {
    this->nextList.insert(std::make_pair(frontStmtLineNumber, backStmtLineNumber));
}

std::unordered_map<int, int>& NextTable::getAllNext() {
    return this->nextList;
}