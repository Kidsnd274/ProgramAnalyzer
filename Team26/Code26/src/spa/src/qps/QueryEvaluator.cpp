#include "QueryEvaluator.h"
#include "evaluator/ClauseAssigner.h"

void QueryEvaluator::evaluate(Query* query) {
    if (query->getStatus() != VALID_QUERY) {
        return;
    }

    ResultTable* resultOfEvaluation = new ResultTable();
    ClauseAssigner* clauseAssigner = new ClauseAssigner();

    // Relation clause and Pattern clause
    for (auto iter = query->clauseList->begin(); iter != query->clauseList->end(); iter++) {
        if (typeid(**iter).name() == typeid(WithClause).name()) {
            continue;
        }
        ResultTable* resultTable = new ResultTable();
        clauseAssigner->assignClause(resultTable, *iter);
        resultOfEvaluation = ResultTable::mergeTable(resultOfEvaluation, resultTable);
//        resultOfEvaluation->mergeTable(*resultTable);
    }

    // Merge with synonyms to be selected
    for (auto candidate: query->getCandidateList()) {
        if (candidate.argument.argumentType == Argument::BOOLEAN_ARG) {
            continue;
        }
        if (!resultOfEvaluation->isSynonymPresent(candidate.argument.argumentName)) {
            getAllEntity(candidate.argument, resultOfEvaluation);
        }
    }

    // With clause
    for (auto iter = query->clauseList->begin(); iter != query->clauseList->end(); iter++) {
        if (typeid(**iter) != typeid(WithClause)) {
            continue;
        }
        clauseAssigner->assignClause(resultOfEvaluation, *iter);
    }


    query->resultTable = resultOfEvaluation;
}

void QueryEvaluator::getAllEntity(Argument argument, QPS::ResultTable *resultTable) {
    vector<string> synonym = {argument.argumentName};
    unordered_set<vector<string>, StringVectorHash> results;
    vector<string> entities = QPS_PKB_Interface::getAllEntity(&argument);
    for (auto e: entities) {
        results.insert({e});
    }
    ResultTable* entityTable = new ResultTable(synonym, results);
    resultTable->mergeTable(*entityTable);
}

void QueryEvaluator::changeToAttrName(Query *query, QPS::ResultTable *resultTable) {
    std::vector<pair<int, Query::CandidateStruct>> colsToChange;
    for (auto candidate : query->getCandidateList()) {
        if (candidate.attributeType != INVALID_ATTR_TYPE) {
            colsToChange.push_back(
                    make_pair(
                            resultTable->getSynonymColRef().find(candidate.argument.argumentName)->second,
                            candidate
                    )
            );
        }
    }
    for (auto row : resultTable->getTable()) {
        for (auto col : colsToChange) {
            int colNum = col.first;
            row.at(colNum) = getAttr(row.at(colNum), col.second);
        }
    }
}

std::string QueryEvaluator::getAttr(std::string value, Query::CandidateStruct candidate) {
    if (candidate.attributeType == PROC_STMT_LINE_NUMBER) {
        return QPS_PKB_Interface::getProcLineNumberByName(value);
    }
    return value;
}
