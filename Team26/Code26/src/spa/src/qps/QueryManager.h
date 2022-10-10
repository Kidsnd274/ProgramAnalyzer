#ifndef SPA_QUERYMANAGER_H
#define SPA_QUERYMANAGER_H

#include "pkb/PKBInterface.h"
#include "Tokenizer.h"
#include "QueryProcessorTypes.h"
#include "QueryPreprocessor.h"
#include "QueryResultProjector.h"
#include <list>
#include <vector>
#include <string>

namespace QPS {
    class QueryManager {
    public:
        void handleQuery(PKBInterface* pkb, std::string queryString, std::list<std::string>& results);
    };

}

#endif //SPA_QUERYMANAGER_H