#include "QueryPreprocessor.h"
#include "QueryStruct.h"
#include "Tokenizer.h"
#include "QueryManager.h"
#include "QueryEvaluator.h"
#include "QueryResultProjector.h"
#include <vector>
#include <iostream>
#include <cstdio>
#include <list>

namespace QPS {
    void QueryManager::handleQuery(PKBInterface* pkb, std::string queryString, std::list<std::string>& results) {
        std::vector<QPS::Token> tokens; // Initialize a vector of SPToken to store the tokens.
        QPS::tokenize(queryString, tokens); // Call tokenizer to read in PQL and tokenize it into tokens.
        QPS::Container container = QPS::Container(tokens); // Initialize a container to store the result of tokenization.
        QPS::parseToken(tokens, container); // Call QPS parser to parse the tokens into Query Structure. Store the result in container.queryStruct.

        QPS::QueryStruct query = container.getQueryStruct(); // Get the result of parsing.
        QPS::BasicQueryEvaluator basicQueryEvaluator = QPS::BasicQueryEvaluator();
        basicQueryEvaluator.evaluateQuery(query, pkb); // Call basicQueryEvaluator to evaluate the query. Store the result in query.resultTable.

        QPS::QueryResultProjector queryResultProjector = QPS::QueryResultProjector();
        queryResultProjector.getSelectTuples(query, results); // Call queryResultProjector to format and print out the query result.
//        std::cout << queryResultProjector.getSelectTuples(query, results) << std::endl;
        // for test only
//        puts("\nPrint Result Table:");
//        query.resultTable.printTable();
    }
}

//int main() {
//    QPS::QueryManager queryManager = QPS::QueryManager();
////    queryManager.handleQuery();
//}