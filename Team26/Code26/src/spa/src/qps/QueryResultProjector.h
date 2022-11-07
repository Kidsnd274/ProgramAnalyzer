#ifndef INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H
#define INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H

#include <algorithm>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>
#include "Query.h"
#include "QPS_Interface.h"
#include "ResultTable.h"

class QueryResultProjector {
public:
    std::string getSelectTuples(Query query, std::list<std::string>& results);
};

#endif  // INC_22S1_CP_SPA_TEAM_26_QUERYRESULTPROJECTOR_H
