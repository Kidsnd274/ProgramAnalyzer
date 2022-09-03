#ifndef SPA_QUERYPREPROCESSOR_H
#define SPA_QUERYPREPROCESSOR_H

#include <utility>
#include <map>
#include <iostream>
#include "QueryProcessorTypes.h"
#include "Tokenizer.h"

namespace QPS {
    void parseToken(std::vector<QPS::Token> &tokens);
}


#endif //SPA_QUERYPREPROCESSOR_H