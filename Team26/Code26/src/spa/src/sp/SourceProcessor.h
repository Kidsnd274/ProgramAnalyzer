#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "../util/Lexer.h"
#include "Parser.h"
#include "pkb/PKBInterface.h"

class SourceProcessor {
private:
    PKBInterface* pkbInterface;

public:
    explicit SourceProcessor(PKBInterface* pkbInterface) {
        this->pkbInterface = pkbInterface;
    }

    void processSIMPLE(std::string sourceFile);

    // Methods for QPS
    static bool checkExpressionString(std::string exprString);
    static std::shared_ptr<TNode> parseExpressionFromString(std::string exprString);
};
