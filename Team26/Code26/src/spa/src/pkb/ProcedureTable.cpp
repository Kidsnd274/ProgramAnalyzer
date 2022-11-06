#include "ProcedureTable.h"

class ProcedureTable;

void ProcedureTable::insertProc(Procedure proc) {
    this->procList.insert(&proc);
}

std::unordered_set<std::string> ProcedureTable::getAllProcedures() {
    std::unordered_set<std::string> result;
    for (auto proc: this->procList) {
        result.insert(proc->name);
    }
    return result;
}

std::unordered_set<Procedure*> ProcedureTable::getProcList() {
    return this->procList;
}

std::string ProcedureTable::getProcedureNameOf(CFGHeadPtr cfg) {
    std::string result = "";
    for (auto proc: this->procList) {
        if (proc->cfg == cfg)  {
            result = proc->name;
            break;
        }
    }
    return result;
}

Procedure* ProcedureTable::getProcedureByName(std::string name) {
    Procedure* result;
    for (auto proc: this->procList) {
        if (proc->name == name)  {
            return proc;
        }
    }
    return result;
}

Procedure* ProcedureTable::getProcByStmt(int stmt) {
    for (auto proc: this->procList) {
        if ((stmt >= proc->startingStmtNo) && (stmt <= proc->endingStmtNo))  {
            return proc;
        }
    }
    throw ProcedureNotFoundException();
}

void ProcedureTable::clear() {
    this->procList.clear();
}
