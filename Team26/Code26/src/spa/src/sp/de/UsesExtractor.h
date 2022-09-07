#include "Extractor.h"
#include <unordered_set>
#include <queue>
class UsesExtractor : public Extractor {
public:
    UsesExtractor(PKBInterface &pkb) : Extractor(pkb){}

    void extractFromProcedure(std::shared_ptr<ProcedureNode> ptr) override{};
    void extractFromIf(std::shared_ptr<IfNode> ptr) override;
    void extractFromWhile(std::shared_ptr<WhileNode> ptr) override;
    void extractFromRead(std::shared_ptr<ReadNode> ptr) override {};
    void extractFromPrint(std::shared_ptr<PrintNode> ptr) override;
    void extractFromAssign(std::shared_ptr<AssignNode> ptr) override;
    void extractFromCond(std::shared_ptr<TNode> ptr);
    void extractFromStatementsWithCond(int stmtNumber, std::shared_ptr<TNode> cond);
};

