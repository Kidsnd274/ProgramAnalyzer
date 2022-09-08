//
// Created by QMS on 4/9/2022.
//
#include <stdio.h>
#include <string>
#include "Procedure.h"
#include "ProcedureTable.h"

using namespace std;

class ProcedureTable;

void ProcedureTable::insertProc(Procedure proc) {
    this->procList.push_back(proc);
}

vector<string> ProcedureTable::getAllProcedures() {
    vector<string> result;
    for (Procedure proc: this->procList) {
        result.push_back(proc.name);
    }
    return result;
}

