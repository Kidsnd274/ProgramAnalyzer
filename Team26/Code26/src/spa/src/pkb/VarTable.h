#ifndef SPA_VARTABLE_H
#define SPA_VARTABLE_H

#include <string>
#include <vector>

class VarTable {
private:
    std::vector<std::string> varList;

public:
    void insertVar(std::string var);
    std::vector<std::string> getAllVariables();
    void clear();
};

#endif  // SPA_VARTABLE_H
