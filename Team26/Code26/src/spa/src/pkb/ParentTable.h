#ifndef SPA_PARENTTABLE_H

#include <stdio.h>
#include <string>
#include <unordered_set>
#include <unordered_map>

class ParentTable {
private:
    std::unordered_map<int, std::unordered_set<int>> parentList;
public:
    void insertParent(int parentStmtLineNumber, int childStmtListNumber);
    bool existParent(int parentStmtLineNumber, int childStmtListNumber);
    std::unordered_map<int, std::unordered_set<int>> getAllParents();
    void clear();
};

#endif //SPA_PARENTTABLE_H
