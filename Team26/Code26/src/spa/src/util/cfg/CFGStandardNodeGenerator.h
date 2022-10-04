#ifndef SPA_CFGSTANDARDNODEGENERATOR_H
#define SPA_CFGSTANDARDNODEGENERATOR_H

#include <utility>

#include "CFGNodeGenerator.h"
#include "CFGHead.h"

class CFGStandardNodeGenerator;

typedef std::shared_ptr<CFGStandardNodeGenerator> CFGStandardNodeGeneratorPtr;

class CFGStandardNodeGenerator : public CFGNodeGenerator {
public:
    CFGStandardNodeGenerator(CFGHeadPtr cfg) : CFGNodeGenerator(std::move(cfg)) {

    }
    void addNode() override;
    CFGNodeGenerator finalize() override;
    static CFGStandardNodeGeneratorPtr createGenerator(CFGHeadPtr cfg);
};

#endif //SPA_CFGSTANDARDNODEGENERATOR_H
