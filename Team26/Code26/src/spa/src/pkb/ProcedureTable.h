#ifndef SPA_PROCEDURETABLE_H
#define SPA_PROCEDURETABLE_H

#include <string>
#include <unordered_set>
#include "Procedure.h"
#include "ProcedureNotFoundException.h"

class ProcedureTable {
private:
    std::unordered_set<Procedure*> procList;
public:
    void insertProc(Procedure proc);
    std::unordered_set<std::string> getAllProcedures();
    std::unordered_set<Procedure*> getProcList();
    std::string getProcedureNameOf(CFGHeadPtr cfg);
    Procedure* getProcedureByName(std::string name);
    Procedure* getProcByStmt(int stmt);
    void clear();
};

#endif  // SPA_PROCEDURETABLE_H
