//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_MODIFIESTABLE_H
#define SPA_MODIFIESTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include "Modifies.h"

using namespace std;

class ModifiesTable {
private:
    vector<Modifies> modifiesList;
public:
    void insertModifies(Modifies modifies);
    bool existModifies(Modifies modifies);
};

#endif //SPA_MODIFIESTABLE_H
