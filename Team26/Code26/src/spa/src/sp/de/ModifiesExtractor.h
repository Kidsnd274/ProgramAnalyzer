#include "Extractor.h"
class ModifiesExtractor : public Extractor {
public:
    ModifiesExtractor(PKBInterface &pkb) : Extractor(pkb){}

    void extractFromProcedure(std::shared_ptr<ProcedureNode> ptr) override{};
    void extractFromIf(std::shared_ptr<IfNode> ptr) override {};
    void extractFromWhile(std::shared_ptr<WhileNode> ptr) override {};
    void extractFromRead(std::shared_ptr<ReadNode> ptr) override;
    void extractFromPrint(std::shared_ptr<PrintNode> ptr) override {};
    void extractFromAssign(std::shared_ptr<AssignNode> ptr) override;
};

