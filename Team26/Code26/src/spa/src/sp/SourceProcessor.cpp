#include "SourceProcessor.h"
#include <iostream>

void SourceProcessor::processSIMPLE(std::string sourceFile) {
    Lexer lexer(sourceFile);
    std::vector<SPToken> tokens = lexer.tokenize();
    Parser parser(tokens, pkbInterface);
    parser.parseSimple();
}

bool SourceProcessor::checkExpressionString(std::string exprString) {
    std::string main = "procedure test {\nx = " + exprString + ";\n}";
    try {
        Lexer lexer(main);
        std::vector<SPToken> tokens = lexer.tokenize();
        auto *pkbInterface = new PKBInterface();
        Parser parser = Parser(tokens, pkbInterface);
        parser.parseSimple();
    }
    catch (SyntaxErrorException) {
        return false;
    }
    return true;
}

std::shared_ptr<TNode> SourceProcessor::parseExpressionFromString(std::string exprString) {
    if (!checkExpressionString(exprString)) {
        throw SyntaxErrorException();
    }
    std::string expr = exprString.append(";");
    return Parser::parseExpressionFromString(std::move(exprString));
}
