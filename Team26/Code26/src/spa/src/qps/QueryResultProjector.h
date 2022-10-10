#ifndef INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H
#define INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H

#include "qps/oldComponents/QueryStruct.h"
#include "ResultTable.h"
#include <list>

namespace QPS {
    class QueryResultProjector {
    public:
        void projectResult(QPS::QueryStruct queryStruct, std::list<std::string>& results);
        std::string getSelectTuples(QPS::QueryStruct query, std::list<std::string>& results);
    };
}


#endif //INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H
