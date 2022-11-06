#include <memory>
#include <queue>
#include <unordered_set>
#include <string>
#include <vector>
#include "Extractor.h"

class UsesExtractor : public Extractor {
private:
    void addToPkb(std::unordered_set<std::string> &varSet, bool isCond);
public:
    explicit UsesExtractor(PKBInterface *pkb) : Extractor(pkb) {}

    void extractFromIf(std::shared_ptr<IfNode> ptr) override;
    void extractFromWhile(std::shared_ptr<WhileNode> ptr) override;
    void extractFromPrint(std::shared_ptr<PrintNode> ptr) override;
    void extractFromAssign(std::shared_ptr<AssignNode> ptr) override;
    void extractFromExpressionTree(const std::shared_ptr<TNode>& ptr, bool isCond);
    void extractFromStatementsWithCond(int stmtNumber, const std::shared_ptr<TNode>& cond);
};
