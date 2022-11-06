#ifndef SPA_VARTABLE_H
#define SPA_VARTABLE_H

#include <unordered_set>
#include <string>

using namespace std;

class VarTable {
private:
    std::unordered_set<std::string> varList;

public:
    void insertVar(std::string var);
    std::unordered_set<std::string> getAllVariables();
    void clear();
};

#endif  // SPA_VARTABLE_H
