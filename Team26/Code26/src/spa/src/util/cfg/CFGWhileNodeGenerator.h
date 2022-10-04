#ifndef SPA_CFGWHILENODEGENERATOR_H
#define SPA_CFGWHILENODEGENERATOR_H

#include "CFGNodeGenerator.h"

class CFGIfNodeGenerator : public CFGNodeGenerator {
private:
    CFGNodeGenerator previousGenerator;
    int topNodeStmtNumber;
public:
    CFGIfNodeGenerator(int ifStatementNumber) {
        this->topNodeStmtNumber = ifStatementNumber;
    }
    void addNode();
    CFGNodeGenerator finalize();
};

#endif //SPA_CFGWHILENODEGENERATOR_H
