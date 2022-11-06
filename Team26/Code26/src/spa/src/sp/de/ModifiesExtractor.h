#include <memory>
#include <vector>
#include <string>
#include "Extractor.h"

class ModifiesExtractor : public Extractor {
public:
    explicit ModifiesExtractor(PKBInterface *pkb) : Extractor(pkb) {}

    void extractFromIf(std::shared_ptr<IfNode> ptr) override;
    void extractFromWhile(std::shared_ptr<WhileNode> ptr) override;
    void extractFromRead(std::shared_ptr<ReadNode> ptr) override;
    void extractFromAssign(std::shared_ptr<AssignNode> ptr) override;
    void extractFromModifiesStatements(std::string varModified, int stmtNumber);
};

