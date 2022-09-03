//
// Created by QMS on 4/9/2022.
//

#ifndef SPA_PROCEDURETABLE_H
#define SPA_PROCEDURETABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include "Procedure.h"

using namespace std;

class ProcedureTable {
private:
    vector<Procedure> procList;
public:
    void insertProc(Procedure proc);
};

#endif //SPA_PROCEDURETABLE_H
