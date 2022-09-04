#include "QueryResultProjector.h"

namespace QPS {
    void QueryResultProjector::projectResult(QPS::QueryStruct queryStruct) {
        ResultTable resultTable = queryStruct.resultTable;
        CANDIDATE_LIST candidateList = queryStruct.getCandidateList();
        std::vector<std::string> synonymNames;
        for (auto &candidate: candidateList) {
            synonymNames.push_back(candidate.entityOfCandidate.nameOfEntity);
        }
        std::unordered_set<std::vector<std::string>, StringVectorHash> values;
        resultTable.getSynonymsValues(synonymNames, values);
        ResultTable result = ResultTable(synonymNames, values);
        result.deleteDuplicateRows();
        result.printTable();
    }
}