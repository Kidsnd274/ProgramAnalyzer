#ifndef SPA_CONSTANTTABLE_H
#define SPA_CONSTANTTABLE_H

#include <unordered_set>
#include <string>

class ConstantTable {
private:
    std::unordered_set<int> constList;
public:
    void insertConst(int constant);
    std::unordered_set<std::string> getAllConstants();
    void clear();
};

#endif  // SPA_CONSTANTTABLE_H
