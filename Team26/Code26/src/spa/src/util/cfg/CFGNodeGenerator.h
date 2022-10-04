#ifndef SPA_CFGNODEGENERATOR_H
#define SPA_CFGNODEGENERATOR_H

#include "CFGHead.h"
#include <memory>
#include <utility>

class CFGNodeGenerator;

typedef std::shared_ptr<CFGNodeGenerator> CFGNodeGeneratorPtr;

class CFGNodeGenerator {
public:
    CFGHeadPtr cfg;
    CFGNodePtr previousNode = nullptr;
    CFGNodeGenerator(CFGHeadPtr cfg) {
        this->cfg = std::move(cfg);
    }
    virtual void addNode();
    virtual CFGNodeGenerator finalize();
};

#endif //SPA_CFGNODEGENERATOR_H
