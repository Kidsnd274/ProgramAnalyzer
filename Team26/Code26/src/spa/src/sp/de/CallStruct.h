#include <string>
#ifndef SPA_CALLSTRUCT_H
#define SPA_CALLSTRUCT_H

class CallStruct {
private:
    int stmtNumber;
    std::string procedureCalled;

public:
    CallStruct(int sn, std::string pc) {
        stmtNumber = sn;
        procedureCalled = pc;
    }

    int getStatementNumber() {
        return stmtNumber;
    }

    std::string getProcedureCalled() {
        return procedureCalled;
    }
};

#endif  // SPA_CALLSTRUCT_H
