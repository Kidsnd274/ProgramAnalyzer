#include <fstream>
#include "../util/Lexer.h"
#include "Parser.h"
#include "pkb/PKBInterface.h"

using namespace std;

class SourceProcessor {
private:
    PKBInterface* pkbInterface;

public:
    SourceProcessor(PKBInterface* pkbInterface) {
        this->pkbInterface = pkbInterface;
    }

    void processSIMPLE(std::string sourceFile);

    // Methods for QPS
    static bool checkExpressionString(std::string exprString);
    static std::shared_ptr<TNode> parseExpressionFromString(std::string exprString);
};
