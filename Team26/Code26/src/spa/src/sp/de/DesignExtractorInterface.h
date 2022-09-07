#ifndef SPA_SP_DE_DESIGNEXTRACTORINTERFACE_H
#define SPA_SP_DE_DESIGNEXTRACTORINTERFACE_H

#include "Extractor.h"
class DesignExtractorInterface {
public:
    virtual void extract(std::shared_ptr<ProcedureNode> p);
};

#endif