#include "QueryResultProjector.h"
#include "QPS_Interface.h"


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

    if (query.isBooleanQuery()) {
        if (!table.empty() || query.clauseList->empty() || query.resultTable->isTrueTable()) {
            results.push_back("TRUE");
        } else {
            results.push_back("FALSE");
        }
    } else {
        for (auto &candidate: query.getCandidateList()) {
            synonyms.push_back(candidate.argument.argumentName);
        }
        for (auto row : query.resultTable->getTable()) {
            std::string rowString;
            for (auto &candidate : query.getCandidateList()) {
                std::string value = row.at(query.resultTable->getSynonymColRef().find(candidate.argument.argumentName)->second);
                rowString += QPS_Interface::getAttrName(value, candidate) + " ";
            }
            std::string trimmedRowString = rowString.substr(0, rowString.length() - 1);
            if (rowStringSet.find(trimmedRowString) == rowStringSet.end()) {
                rowStringSet.insert(trimmedRowString);
                results.push_back(trimmedRowString);
            }
        }
    }
    return resultString.substr(0, resultString.length() - 2);
}
