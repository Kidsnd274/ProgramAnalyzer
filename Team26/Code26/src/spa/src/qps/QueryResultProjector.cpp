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
        result.deleteDuplicateRows({});

        result.printTable();
    }

    std::string QueryResultProjector::getSelectTuples(QPS::QueryStruct query, std::list<std::string>& results) {
        if (query.queryStatus == QPS::SEMANTIC_ERROR) {
            results.push_back("SemanticError");
            return "SemanticError";
        }
        if (query.queryStatus == QPS::SYNTAX_ERROR) {
            results.push_back("SyntaxError");
            return "SyntaxError";
        }

        std::string resultString;
        std::vector<std::vector<std::string>> table = query.resultTable.getTable();
        std::unordered_set<std::string> rowStringSet;
        std::vector<std::string> sNames;
        std::unordered_set<std::vector<std::string>, StringVectorHash> tupleValues;
        for (auto &sRef: query.getCandidateList()) {
            sNames.push_back(sRef.entityOfCandidate.nameOfEntity);
        }
        query.resultTable.getSynonymsValues(sNames, tupleValues);
        for (auto row : tupleValues) {
            std::string rowString; // = "("

            // C5 (Minor): Commented-out code - Delete if not needed

//            for (auto candidate : query.getCandidateList()) {
//                int colNumber = query.resultTable.getSynonymColRef().find(
//                        candidate.entityOfCandidate.nameOfEntity)->second;
//                rowString += row.at(colNumber) + " ";
//            }
//            rowString = rowString.substr(0, rowString.length() - 1); //remove last space
//            if (rowStringSet.find(rowString) == rowStringSet.end()) {
//                resultString += rowString + ", ";
//                rowStringSet.insert(rowString);
//            }
            std::for_each(row.begin(), row.end(), [&](const std::string &piece){ rowString += piece + " "; });
            std::string trimmedRowString = rowString.substr(0, rowString.length() - 1);
            resultString += trimmedRowString + ", ";
            rowStringSet.insert(trimmedRowString);
            results.push_back(trimmedRowString);
        }
//        for (auto &s: rowStringSet) {
//            results.push_back(s);
//        }
        return resultString.substr(0, resultString.length() - 2);
    }
}