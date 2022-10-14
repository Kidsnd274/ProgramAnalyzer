#ifndef INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H
#define INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H

#include "Query.h"
#include "ResultTable.h"
#include <list>

namespace QPS {
    class QueryResultProjector {
    public:
        void projectResult(Query queryStruct, std::list<std::string>& results);
        std::string getSelectTuples(Query query, std::list<std::string>& results);
    };
}


#endif //INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H
