#ifndef SPA_SP_DE_DESIGNEXTRACTORINTERFACE_H
#define SPA_SP_DE_DESIGNEXTRACTORINTERFACE_H

#include "CallStruct.h"
#include "FollowsExtractor.h"
#include "ParentExtractor.h"
#include "ModifiesExtractor.h"
#include "UsesExtractor.h"
class DesignExtractorInterface {
public:
    virtual ~DesignExtractorInterface() = default;
    virtual void extract(std::vector<std::shared_ptr<ProcedureNode>> procedures) = 0;
    virtual void addCallStatement(CallStruct &cs) = 0;
    virtual void addProcedure(std::string name) = 0;
};

#endif