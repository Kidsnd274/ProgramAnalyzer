#include "SourceProcessor.h"
#include <iostream>

using namespace std;

void SourceProcessor::processSIMPLE(fstream* sourceFile) {
    // Temporarily try and lexify and print out contents with no whitespaces
    Lexer *lexer = new Lexer(sourceFile);
    std::vector results = lexer->delimitBySpaceUsingFS();
    std::cout << "PRINTING LEXER TEST" << endl;
    for (int i = 0; i < results.size(); ++i) {
        std::cout << results[i] + " ";
    }
    std::cout.flush();
}