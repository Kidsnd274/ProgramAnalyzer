#include <fstream>
#include "../util/Lexer.h"
#include "Parser.h"
#include "PKBInterface.h"

using namespace std;

class SourceProcessor {
private:
    PKBInterface* pkbInterface;

public:
    SourceProcessor(PKBInterface* pkbInterface) {
        this->pkbInterface = pkbInterface;
    }

    void processSIMPLE(std::string sourceFile);
};