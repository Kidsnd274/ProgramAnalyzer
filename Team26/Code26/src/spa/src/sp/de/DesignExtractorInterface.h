#ifndef SPA_SP_DE_DESIGNEXTRACTORINTERFACE_H
#define SPA_SP_DE_DESIGNEXTRACTORINTERFACE_H

#include "FollowsExtractor.h"
#include "ParentExtractor.h"
#include "ModifiesExtractor.h"
#include "UsesExtractor.h"
class DesignExtractorInterface {
public:
    virtual void extract(std::shared_ptr<ProcedureNode> p);
};

#endif