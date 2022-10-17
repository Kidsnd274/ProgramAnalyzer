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

//    for (auto candidate: query->getCandidateList()) {
//        if (candidate.argument.argumentType == Argument::BOOLEAN_ARG) {
//            continue;
//        }
//        if (!resultOfEvaluation->isSynonymPresent(candidate.argument.argumentName)) {
//            getAllEntity(candidate.argument, resultOfEvaluation);
//        }
//    }

    // Merge with synonyms to be selected
    for (auto synonym: query->getSynonymMap()) {
        if (!resultOfEvaluation->isSynonymPresent(synonym.second.argumentName)) {
            getAllEntity(synonym.second, resultOfEvaluation);
        }
    }

    // With clause
    for (auto iter = query->clauseList->begin(); iter != query->clauseList->end(); iter++) {
        if (typeid(**iter) != typeid(WithClause)) {
            continue;
        }
        clauseAssigner->assignClause(resultOfEvaluation, *iter);
    }

    // For select s.AttrName, change value to their corresponding AttrName
//    changeToAttrName(query, resultOfEvaluation);

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

//void QueryEvaluator::changeToAttrName(Query *query, QPS::ResultTable *resultTable) {
//    std::vector<pair<int, Query::CandidateStruct>> colsToChange;
//    for (auto candidate : query->getCandidateList()) {
//        if (candidate.attributeType != INAPPLICABLE) {
//            colsToChange.push_back(
//                    make_pair(
//                            resultTable->getSynonymColRef().find(candidate.argument.argumentName)->second,
//                            candidate
//                    )
//            );
//        }
//    }
//    std::vector<std::vector<std::string>> attrNameResultTable = resultTable->getTable();
//    for (int i = 0; i < attrNameResultTable.size(); i++) {
//        std::vector<std::string> row = attrNameResultTable.at(i);
//        for (auto col : colsToChange) {
//            int colNum = col.first;
//            string temp = getAttrName(row.at(colNum), col.second);
//            row[colNum] = getAttrName(row.at(colNum), col.second);
//        }
//        attrNameResultTable[i] = row;
//    }
//    resultTable->setTable(attrNameResultTable);
//}
