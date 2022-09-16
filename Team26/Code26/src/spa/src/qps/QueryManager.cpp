#include "QueryPreprocessor.h"
#include "QueryManager.h"
#include "Container.h"
#include "QueryEvaluator.h"
#include "QueryResultProjector.h"
#include <utility>
#include <vector>
#include <iostream>
#include <list>

namespace QPS {
    PKBInterface* QueryManager::pkb;

    void QueryManager::handleQuery(PKBInterface* pkb, std::string queryString, std::list<std::string>& results) {
        QueryManager::setPKBInterface(pkb);
        std::vector<QPS::Token> tokens; // Initialize a vector of SPToken to store the tokens.
        QPS::tokenize(std::move(queryString), tokens); // Call tokenizer to read in PQL and tokenize it into tokens.
//        std::cout << "==========tokenizing-----------" << std::endl;
//        for (QPS::Token token : tokens) {
//            std::cout << token.nameValue + " "+ tokenMap.at(token.tokenType) << std::endl;
//        }
        QPS::Container container = QPS::Container(tokens); // Initialize a container to store the result of tokenization.
        Exception parsingException = QPS::parseToken(tokens, container); // Call QPS parser to parse the tokens into Query Structure. Store the result in container.queryStruct.
        if (parsingException != VALID) {
            std::cout << exceptionToStringQPS(parsingException) << std::endl;
            return ;
        } else {
            std::cout << "VALID" << std::endl;
        }

        //////////////// for test only /////////////////
        std::cout << "————————Declaration————————" << std::endl;
        for (auto& it: container.getDeclarationMap()) {
            std::cout << it.first << " : " << entityToString(it.second)  << std::endl;
        }
        std::cout << "————————Candidate————————" << std::endl;
        for (QPS::CandidateStruct candidateStruct : container.getCandidateList()) {
            std::cout << QPS::candidateToString(candidateStruct.typeOfCandidate) + ": " + candidateStruct.entityOfCandidate.nameOfEntity  << std::endl;
        }
        std::cout << "————————Relation————————" << std::endl;
        SUCH_THAT_LIST  suchThatList = container.getSuchThatList();
        for (RelationStruct relationStruct: suchThatList) {
            std::cout << QPS::relationToString(relationStruct.typeOfRelation) + ": " + relationStruct.arg1.nameOfArgument + " - "+ QPS::ARGToString(relationStruct.arg1.typeOfArgument)
                         + "  " + relationStruct.arg2.nameOfArgument + " - " + QPS::ARGToString(relationStruct.arg2.typeOfArgument)<< std::endl;
        }

        std::cout << "————————Pattern————————" << std::endl;
        PATTERN_LIST patternList = container.getPatternList();
        for (const PatternStruct& patternStruct: patternList) {
            std::cout << patternStruct.arg1.nameOfArgument + " - " + QPS::ARGToString(patternStruct.arg1.typeOfArgument) << std::endl;
            std::cout << patternStruct.arg2.nameOfArgument + " - " + QPS::ARGToString(patternStruct.arg2.typeOfArgument) << std::endl;
        }
        //////////////// for test only /////////////////

        QPS::QueryStruct query = container.getQueryStruct(); // Get the result of parsing.
        QPS::BasicQueryEvaluator basicQueryEvaluator = QPS::BasicQueryEvaluator();
        basicQueryEvaluator.evaluateQuery(query); // Call basicQueryEvaluator to evaluate the query. Store the result in query.resultTable.

        QPS::QueryResultProjector queryResultProjector = QPS::QueryResultProjector();
        queryResultProjector.getSelectTuples(query, results); // Call queryResultProjector to format and print out the query result.
    }
}