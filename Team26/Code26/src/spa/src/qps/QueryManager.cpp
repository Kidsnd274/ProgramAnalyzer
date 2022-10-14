#include "QueryManager.h"

//namespace QPS {
//    void QueryManager::handleQuery(PKBInterface* pkb, std::string queryString, std::list<std::string>& results) {
//        QueryManager::setPKBInterface(pkb);
//        std::vector<QPS::Token> tokens; // Initialize a vector of SPToken to store the tokens.
//        QPS::tokenize(std::move(queryString), tokens); // Call tokenizer to read in PQL and tokenize it into tokens.
//
//        QPS::Container container = QPS::Container(tokens); // Initialize a container to store the result of tokenization.
//        Exception parsingException = QPS::parseToken(tokens, container); // Call QPS parser to parse the tokens into Query Structure. Store the result in container.queryStruct.
//
//        std::cout << exceptionToStringQPS(parsingException) << std::endl;
//        QueryStatus queryStatus;
//
//        switch (parsingException) {
//            case INVALID_ENTITY:
//            case INVALID_RELATION_SYNTAX:
//            case INVALID_SELECT:
//            case INVALID_SUCH_THAT:
//            case INVALID_PATTERN_NAME:
//            case INVALID_PATTERN_SYNTAX:
//            case INVALID_DECLARATION:
//            case UNMATCHED_QUERY_TYPE:
//            case INVALID_MULTIPLE_CLAUSE:
//            case INVALID_RELATION_CONTENT:
//            case INVALID_WITH_SYNTAX:
//            case INVALID_WITH_MISSING_DOT:
//            case INVALID_WITH_FIELD:
//            case UNDECLARED_SELECT_ENTITY:
//            case INVALID_WITH_TYPE_EXCEPTION:
//            case UNDECLARED_ENTITY_WITH:
//            case INVALID_PATTERN_CONTENT:
//            case INVALID_RELATION: {
//                queryStatus = SYNTAX_ERROR;
//                break;
//            }
//            case UNDECLARED_ENTITY_PATTERN:
//            case UNDECLARED_ENTITY_SUCH_THAT:{
//                queryStatus = SEMANTIC_ERROR;
//                break;
//            }
//            case VALID: {
//                queryStatus = VALID_QUERY;
//            }
//        }
//
//
//        QPS::QueryStruct query = container.getQueryStruct(); // Get the result of parsing.
//        if (query.queryStatus == VALID_QUERY || queryStatus != VALID_QUERY) {
//            query.queryStatus = queryStatus;
//        }
//        QPS::BasicQueryEvaluator basicQueryEvaluator = QPS::BasicQueryEvaluator();
//        basicQueryEvaluator.evaluateQuery(query); // Call basicQueryEvaluator to evaluate the query. Store the result in query.resultTable.
//
//        QPS::QueryResultProjector queryResultProjector = QPS::QueryResultProjector();
//        queryResultProjector.getSelectTuples(query, results); // Call queryResultProjector to format and print out the query result.
//    }
//}

void QueryManager::handleQuery(PKBInterface *pkb, std::string queryString, std::list<std::string> &results) {
    QPS_PKB_Interface::setPKBInterface(pkb);
    std::vector<QPS::Token> tokens; // Initialize a vector of SPToken to store the tokens.
    QPS::tokenize(std::move(queryString), tokens); // Call tokenizer to read in PQL and tokenize it into tokens.

    QPS::Container* container = new QPS::Container(tokens); // Initialize a container to store the result of tokenization.
    Exception parsingException = QPS::parseToken(tokens, *container); // Call QPS parser to parse the tokens into Query Structure. Store the result in container.queryStruct.

    Query query = container->getQueryStruct();
    QueryEvaluator::evaluate(query); // Call QueryEvaluator to evaluate the query. Store the result in query.resultTable.

    QueryResultProjector* queryResultProjector = new QueryResultProjector();
    queryResultProjector->getSelectTuples(query, results); // Call queryResultProjector to format and print out the query result.
}