#ifndef SPA_NEXTTABLE_H
#define SPA_NEXTTABLE_H

#include <unordered_map>
class NextTable {
private:
    std::unordered_map<int, int> nextList;

public:
    void insertNext(int frontStmtLineNumber, int backStmtLineNumber);
    std::unordered_map<int, int>& getAllNext();
};


#endif //SPA_NEXTTABLE_H
