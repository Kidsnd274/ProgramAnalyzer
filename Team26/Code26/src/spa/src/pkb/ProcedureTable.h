//
// Created by QMS on 4/9/2022.
//

#ifndef SPA_PROCEDURETABLE_H
#define SPA_PROCEDURETABLE_H

#include <stdio.h>
#include <string>
#include <unordered_set>
#include "Procedure.h"

using namespace std;

class ProcedureTable {
private:
    unordered_set<Procedure> procList;
public:
    void insertProc(Procedure proc);
    unordered_set<string> getAllProcedures();
    unordered_set<Procedure> getProcList();
    std::string getProcedureNameOf(CFGHeadPtr cfg);
    Procedure getProcedureByName(std::string name);
    Procedure* getProcByStmt(int stmt);
    void clear();
};

#endif //SPA_PROCEDURETABLE_H
