//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_MODIFIESTABLE_H
#define SPA_MODIFIESTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class ModifiesTable {
private:
    unordered_map<int, string> modifiesList;
public:
    void insertModifies(int stmtLineNumber, string varName);
    bool existModifies(int stmtLineNumber, string varName);
    bool existStatement(int stmtLineNumber);
    string getModifiesVar(int stmtLineNumber);
};

#endif //SPA_MODIFIESTABLE_H
