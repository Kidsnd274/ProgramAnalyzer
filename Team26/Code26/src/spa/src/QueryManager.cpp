#include "QueryProcessorTypes.h"
#include "QueryPreprocessor.h"
#include "QueryStruct.h"
#include "Tokenizer.h"
#include "QueryManager.h"
#include "QueryEvaluator.h"
#include "ResultTable.h"
#include <vector>
#include <map>
#include <cstdio>
#include <iostream>

namespace QPS {

    class QueryManager {

    };
}

int main() {
    std::vector<QPS::Token> tokens;
    QPS::tokenize(std::cin, tokens);
    for (QPS::Token t : tokens) {
        std::string s = QPS::tokenMap.at(t.tokenType);
        std::cout << s + " " << std::endl;
    }

    std::cout << "Start parsing query" << std::endl;
    QPS::Container container = QPS::Container(tokens);
    QPS::parseToken(tokens, container);

    QPS::BasicQueryEvaluator basicQueryEvaluator = QPS::BasicQueryEvaluator();
    QPS::QueryStruct query = container.getQueryStruct();

//    printf("%s\n", "Query: candidate list");
//    for (QPS::CandidateStruct candidateStruct : container.getCandidateList()) {
//        std::cout << QPS::candidateToString(candidateStruct.typeOfCandidate) + ": " + candidateStruct.entityOfCandidate.nameOfEntity  << std::endl;
//    }

    std::cout << "Declaration:" << std::endl;
    for (auto& it: container.getDeclarationMap()) {
        std::cout << it.first << " : " << entityToString(it.second)  << std::endl;
    }

    printf("%s\n", "Query: candidate list");
    printf("len: %d\n", query.getCandidateList().size());
    for (auto iter : query.getCandidateList()) {
        std::cout << iter.entityOfCandidate.nameOfEntity << " " << iter.entityOfCandidate.typeOfEntity << iter.typeOfCandidate << std::endl;
    }

    printf("%s\n", "Query: Synonym list");
    for (auto iter : query.getDeclaredSynonymMap()) {
        std::cout << entityToString(iter.second) << " " << iter.first << std::endl;
    }

    printf("len: %d\n", query.getCandidateList().size());
    for (auto iter : query.getCandidateList()) {
        std::cout << iter.entityOfCandidate.nameOfEntity << iter.entityOfCandidate.typeOfEntity << iter.typeOfCandidate << std::endl;
    }

    basicQueryEvaluator.evaluateQuery(query);
    std::cout << "query status" << query.queryStatus << std::endl;
    query.resultTable.printTable();
    std::vector<std::string> result;
    query.resultTable.getSynonymValue(query.getCandidateList().begin()->entityOfCandidate.nameOfEntity, result);
    query.resultTable.printStringVector(result);
}