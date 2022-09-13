//
// Created by QMS on 13/9/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include "Modifies.h"
#include "ModifiesTable.h"

using namespace std;

void ModifiesTable::insertModifies(Modifies modifies) {
    this->modifiesList.push_back(modifies);
}
bool ModifiesTable::existModifies(Modifies modifies) {

}
