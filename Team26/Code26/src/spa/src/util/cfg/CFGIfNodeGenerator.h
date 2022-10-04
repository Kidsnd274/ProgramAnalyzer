#ifndef SPA_CFGIFNODEGENERATOR_H
#define SPA_CFGIFNODEGENERATOR_H

#include <utility>
#include "CFGNodeGenerator.h"

class CFGIfNodeGenerator;

typedef std::shared_ptr<CFGIfNodeGenerator> CFGIfNodeGeneratorPtr;

class CFGIfNodeGenerator : public CFGNodeGenerator {
private:
    CFGNodeGeneratorPtr previousGenerator;
    int topNodeStmtNumber;
public:
    CFGIfNodeGenerator(CFGHeadPtr cfg, CFGNodeGeneratorPtr previousGenerator) : CFGNodeGenerator(std::move(cfg)) {
        this->previousGenerator = std::move(previousGenerator);
        this-> topNodeStmtNumber = cfg->getNextStatementNumber();
        // Creating new If Node
        CFGNodePtr newNode = CFGNode::createNode(topNodeStmtNumber);
        if (previousGenerator->previousNode != nullptr) {
            
        }
    }
    void addNode();
    void addNodeElse();
    CFGNodeGenerator finalize();
};

#endif //SPA_CFGIFNODEGENERATOR_H
