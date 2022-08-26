#include <fstream>
#include "../util/Lexer.h"

//#ifndef SPA_SOURCEPROCESSOR_H not sure what these do
//#define SPA_SOURCEPROCESSOR_H

//#endif //SPA_SOURCEPROCESSOR_H

using namespace std;

class SourceProcessor {
public:
    void processSIMPLE(fstream* sourceFile);
};