#include "QueryManager.h"

void QueryManager::handleQuery(PKBInterface *pkb, std::string queryString, std::list<std::string> &results) {
    QPS_Interface::setPKBInterface(pkb);
    QPS_Interface::createRuntimeExtractor();

    std::vector<QPS::Token> tokens;  // Initialize a vector of SPToken to store the tokens.
    QPS::tokenize(std::move(queryString), tokens);  // Call tokenizer to read in PQL and tokenize it into tokens.

    QPS::Container* container = new QPS::Container(tokens);  // Initialize a container to store the result of tokenization.
    Exception parsingException = QPS::parseToken(tokens, *container);  // Call QPS parser to parse the tokens into Query Structure. Store the result in container.queryStruct.

    Query query = container->getQueryStruct();

    switch (parsingException) {
        case INVALID_ENTITY:
        case INVALID_RELATION_SYNTAX:
        case INVALID_SELECT:
        case INVALID_SUCH_THAT:
        case INVALID_PATTERN_NAME:
        case INVALID_PATTERN_SYNTAX:
        case INVALID_DECLARATION:
        case UNMATCHED_QUERY_TYPE:
        case INVALID_MULTIPLE_CLAUSE:
        case INVALID_WITH_SYNTAX:
        case INVALID_WITH_MISSING_DOT:
        case INVALID_WITH_FIELD:
        case INVALID_WITH_TYPE_EXCEPTION:
        case INVALID_PATTERN_CONTENT:
        case INVALID_CALL_SYNTAX:
        case INVALID_RELATION: {
            query.setStatus(SYNTAX_ERROR);
            break;
        }
        case UNDECLARED_ENTITY_WITH:
        case UNDECLARED_ENTITY_SUCH_THAT:
        case UNDECLARED_ENTITY_PATTERN:
        case UNDECLARED_SELECT_ENTITY:
        case INVALID_RELATION_CONTENT:
        case UNPAIRED_WITH_TYPE:
        case INVALID_PATTERN_TYPE: {
            query.setStatus(SEMANTIC_ERROR);;
            break;
        }
        case VALID: {
            query.setStatus(VALID_QUERY);;
        }
    }


    query.validate();

    QueryEvaluator::evaluate(&query);  // Call QueryEvaluator to evaluate the query. Store the result in query.resultTable.

    QPS_Interface::clearRuntimeExtractor();

    QueryResultProjector* queryResultProjector = new QueryResultProjector();
    queryResultProjector->getSelectTuples(query, results);  // Call queryResultProjector to format and print out the query result.
    delete container;
    delete queryResultProjector;
}
