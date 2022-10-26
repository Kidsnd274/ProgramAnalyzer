#ifndef SPA_NEXTTABLE_H
#define SPA_NEXTTABLE_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

class NextTable {
private:
    std::unordered_map<int, std::vector<int>> nextList;

public:
    void insertNext(int frontStmtLineNumber, int backStmtLineNumber);
    std::unordered_map<int, std::vector<int>>& getAllNext();
    void clear();
};


#endif //SPA_NEXTTABLE_H
