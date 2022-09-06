#include "SourceProcessor.h"
#include <iostream>

void SourceProcessor::processSIMPLE(std::string sourceFile) {
    Lexer lexer(sourceFile);
    std::vector<SPToken> tokens = lexer.tokenize();
    Parser parser(tokens, pkbInterface);
    parser.parseSimple();
}