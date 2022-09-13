//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_MODIFIESTABLE_H
#define SPA_MODIFIESTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include "Statement.h"

using namespace std;

class ModifiesTable {
private:
    unordered_map<Statement, string> modifiesList;
public:
    void insertModifies(Statement statement, string varName);
    bool existModifies(Statement statement, string varName);
};

#endif //SPA_MODIFIESTABLE_H
