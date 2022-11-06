#ifndef SPA_CONSTANTTABLE_H
#define SPA_CONSTANTTABLE_H

#include <string>
#include <vector>

class ConstantTable {
private:
    std::vector<int> constList;

public:
    void insertConst(int constant);
    std::vector<std::string> getAllConstants();
    void clear();
};

#endif  // SPA_CONSTANTTABLE_H
