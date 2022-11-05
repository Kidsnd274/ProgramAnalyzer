#include "NextTable.h"

void NextTable::insertNext(int frontStmtLineNumber, int backStmtLineNumber) {
    if (this->nextList.find(frontStmtLineNumber) != this->nextList.end()) {
        this->nextList.find(frontStmtLineNumber)->second.insert(backStmtLineNumber);
    } else {
        std::pair<int, std::unordered_set<int>> next (frontStmtLineNumber, {backStmtLineNumber});
        this->nextList.insert(next);
    }
}

std::unordered_map<int, std::unordered_set<int>>& NextTable::getAllNext() {
    return this->nextList;
}

void NextTable::clear() {
    this->nextList.clear();
}
