#include "NextTable.h"

void NextTable::insertNext(int frontStmtLineNumber, int backStmtLineNumber) {
    if (this->nextList.find(frontStmtLineNumber) != this->nextList.end()) {
        this->nextList.find(frontStmtLineNumber)->second.push_back(backStmtLineNumber);
    } else {
        std::pair<int, std::vector<int>> next (frontStmtLineNumber, {backStmtLineNumber});
        this->nextList.insert(next);
    }
}

std::unordered_map<int, std::vector<int>>& NextTable::getAllNext() {
    return this->nextList;
}