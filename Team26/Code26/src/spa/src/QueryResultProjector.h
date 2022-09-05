#ifndef INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H
#define INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H

#include "QueryStruct.h"
#include "ResultTable.h"

namespace QPS {
    class QueryResultProjector {
    public:
        void projectResult(QPS::QueryStruct queryStruct);
        std::string getSelectTuples(QPS::QueryStruct query);
    };
}


#endif //INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H
