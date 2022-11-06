#include "ProcedureTable.h"

class ProcedureTable;

void ProcedureTable::insertProc(Procedure proc) {
    this->procList.push_back(proc);
}

std::vector<std::string> ProcedureTable::getAllProcedures() {
    std::vector<std::string> result;
    for (Procedure proc : this->procList) {
        result.push_back(proc.name);
    }
    return result;
}

std::vector<Procedure> ProcedureTable::getProcList() {
    return this->procList;
}

std::string ProcedureTable::getProcedureNameOf(CFGHeadPtr cfg) {
    std::string result = "";
    for (Procedure proc : this->procList) {
        if (proc.cfg == cfg)  {
            result = proc.name;
            break;
        }
    }
    return result;
}

Procedure ProcedureTable::getProcedureByName(std::string name) {
    Procedure result;
    for (Procedure &proc : this->procList) {
        if (proc.name == name)  {
            return proc;
        }
    }
    return result;
}

Procedure* ProcedureTable::getProcByStmt(int stmt) {
    for (Procedure &proc : this->procList) {
        if ((stmt >= proc.startingStmtNo) && (stmt <= proc.endingStmtNo))  {
            return &proc;
        }
    }
    throw ProcedureNotFoundException();
}

void ProcedureTable::clear() {
    this->procList.clear();
}
