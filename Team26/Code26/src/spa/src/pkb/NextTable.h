#ifndef SPA_NEXTTABLE_H
#define SPA_NEXTTABLE_H

#include <unordered_map>
#include <unordered_set>
#include <unordered_set>

class NextTable {
private:
    std::unordered_map<int, std::unordered_set<int>> nextList;

public:
    void insertNext(int frontStmtLineNumber, int backStmtLineNumber);
    std::unordered_map<int, std::unordered_set<int>>& getAllNext();
    void clear();
};


#endif //SPA_NEXTTABLE_H
