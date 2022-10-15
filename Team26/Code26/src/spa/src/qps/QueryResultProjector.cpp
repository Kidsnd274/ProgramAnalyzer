#include "QueryResultProjector.h"


void QueryResultProjector::projectResult(Query query, std::list<std::string> &results) {
    QPS::ResultTable* resultTable = query.resultTable;
    auto candidateList = query.getCandidateList();
    std::vector<std::string> synonyms;
    for (auto &candidate : candidateList) {
        synonyms.push_back(candidate.argumentName);
    }
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> values;
    resultTable->getSynonymsValues(synonyms, values);
    QPS::ResultTable result = QPS::ResultTable(synonyms, values);
    result.deleteDuplicateRows({});
    result.printTable();
}


std::string QueryResultProjector::getSelectTuples(Query query, std::list<std::string> &results) {
    if (query.getStatus() == SYNTAX_ERROR) {
        results.emplace_back("SyntaxError");
        return "SyntaxError";
    }
    if (query.getStatus() == SEMANTIC_ERROR) {
        results.emplace_back("SemanticError");
        return "SemanticError";
    }

    std::string resultString;
    std::vector<std::vector<std::string>> table = query.resultTable->getTable();
    std::unordered_set<std::string> rowStringSet;
    std::vector<std::string> synonyms;
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> tupleValues;
    for (auto &candidate : query.getCandidateList()) {
        synonyms.push_back(candidate.argumentName);
    }
    query.resultTable->getSynonymsValues(synonyms, tupleValues);
    for (auto row : tupleValues) {
        std::string rowString;
        std::for_each(row.begin(), row.end(), [&](const std::string &piece){ rowString += piece + " "; });
        std::string trimmedRowString = rowString.substr(0, rowString.length() - 1);
        resultString += trimmedRowString + ", ";
        rowStringSet.insert(trimmedRowString);
        results.push_back(trimmedRowString);
    }
    return resultString.substr(0, resultString.length() - 2);
}
