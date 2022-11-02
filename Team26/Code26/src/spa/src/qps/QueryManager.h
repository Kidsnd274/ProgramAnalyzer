#ifndef SPA_QUERYMANAGER_H
#define SPA_QUERYMANAGER_H

#include <list>
#include <vector>
#include <string>
#include "pkb/PKBInterface.h"
#include "QPS_Interface.h"
#include "Tokenizer.h"
#include "QueryProcessorTypes.h"
#include "QueryPreprocessor.h"
#include "QueryEvaluator.h"
#include "QueryResultProjector.h"

namespace QPS {
    class QueryManager {
    public:
        void handleQuery(PKBInterface* pkb, std::string queryString, std::list<std::string>& results);
    };

}

#endif //SPA_QUERYMANAGER_H