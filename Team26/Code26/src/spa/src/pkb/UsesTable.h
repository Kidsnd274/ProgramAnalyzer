//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_USESTABLE_H
#define SPA_USESTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class UsesTable {
private:
    unordered_map<int, vector<string>> usesList;
public:
    void insertUses(int stmtLineNumber, string varName);
    bool existUses(int stmtLineNumber, string varName);
};

#endif //SPA_USESTABLE_H
