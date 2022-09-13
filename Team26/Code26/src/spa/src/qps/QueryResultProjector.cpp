#include "QueryResultProjector.h"
#include <list>
namespace QPS {
    void QueryResultProjector::projectResult(QPS::QueryStruct queryStruct, std::list<std::string>& results) {
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

    std::string QueryResultProjector::getSelectTuples(QPS::QueryStruct query, std::list<std::string>& results) {
        std::string resultString;
        std::vector<std::vector<std::string>> table = query.resultTable.getTable();
        std::unordered_set<std::string> rowStringSet;
        for (auto row : table) {
            std::string rowString; // = "("
            for (auto candidate : query.getCandidateList()) {
                int colNumber = query.resultTable.getSynonymColRef().find(
                        candidate.entityOfCandidate.nameOfEntity)->second;
                rowString += row.at(colNumber) + " ";
            }
            rowString = rowString.substr(0, rowString.length() - 1); //remove last space
            if (rowStringSet.find(rowString) == rowStringSet.end()) {
                resultString += rowString + ", ";
                rowStringSet.insert(rowString);
            }
        }
        for (auto &s: rowStringSet) {
            results.push_back(s);
        }
        return resultString.substr(0, resultString.length() - 2);
    }
}