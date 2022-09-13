//
// Created by QMS on 13/9/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "ModifiesTable.h"

using namespace std;

void ModifiesTable::insertModifies(Statement statement, string varName) {
    this->modifiesList.insert(make_pair(statement, varName));
}
bool ModifiesTable::existModifies(Modifies modifies) {
    vector<Modifies> list = this->modifiesList;
    if (std::find(list.begin(), list.end(), modifies) != list.end())
}
