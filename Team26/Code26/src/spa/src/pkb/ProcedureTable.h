#ifndef SPA_PROCEDURETABLE_H
#define SPA_PROCEDURETABLE_H

#include <string>
#include <vector>
#include "Procedure.h"
#include "ProcedureNotFoundException.h"

class ProcedureTable {
private:
    std::vector<Procedure> procList;
public:
    void insertProc(Procedure proc);
    std::vector<std::string> getAllProcedures();
    std::vector<Procedure> getProcList();
    std::string getProcedureNameOf(CFGHeadPtr cfg);
    Procedure getProcedureByName(std::string name);
    Procedure* getProcByStmt(int stmt);
    void clear();
};

#endif  // SPA_PROCEDURETABLE_H
