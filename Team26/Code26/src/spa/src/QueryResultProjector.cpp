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

    std::string QueryResultProjector::getSelectTuples(QPS::QueryStruct query) {
        std::string resultString;
        std::vector<std::vector<std::string>> table = query.resultTable.getTable();
        std::unordered_set<std::string> rowStringSet;
        for (auto row : table) {
            std::string rowString = "(";
            for (auto candidate : query.getCandidateList()) {
                int colNumber = query.resultTable.getSynonymColRef().find(
                        candidate.entityOfCandidate.nameOfEntity)->second;
                rowString += row.at(colNumber) + ", ";
            }
            rowString[rowString.length() - 2] = ')';
            rowString[rowString.length() - 1] = '\n';
            if (rowStringSet.find(rowString) == rowStringSet.end()) {
                resultString += rowString;
                rowStringSet.insert(rowString);
            }
        }
        return resultString;
    }
}