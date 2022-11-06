#include "QueryEvaluator.h"
#include "evaluator/ClauseAssigner.h"

bool lessThan(ClauseStruct& s1, ClauseStruct& s2) {
    if (s1.groupNumber == s2.groupNumber) {
        return s1.resultTable->getTable().size() < s2.resultTable->getTable().size();
    }
    return s1.groupNumber < s2.groupNumber;
}

void QueryEvaluator::evaluate(Query* query) {
    if (query->getStatus() != VALID_QUERY) {
        return;
    }

    ClauseAssigner* clauseAssigner = new ClauseAssigner();

    // Add synonyms to the map
    unordered_map<string, int> synonymCount = countSynonym(query);

    ClauseStruct* clauseStruct = new ClauseStruct[query->clauseList->size()];

    // Evaluate the clauses
    for (int i = 0; i < query->clauseList->size(); i++) {
        ResultTable* resultTable = new ResultTable();
        clauseAssigner->assignClause(resultTable, query->clauseList->at(i));
        if (resultTable->isFalseTable() || resultTable->isEmptyTable()) {
            query->resultTable->setFalseTable();
            return;
        }
        clauseStruct[i] = {
                query->clauseList->at(i),
                resultTable,
                0
        };
    }

    // Group the clauses
    QueryEvaluator::groupClauses(query->clauseList->size(), clauseStruct);
    sort(clauseStruct, clauseStruct + query->clauseList->size(), lessThan);

    // Merge the result tables
    ResultTable* resultOfEvaluation = new ResultTable();
    for (int i = 0; i < query->clauseList->size(); i++) {
        auto start = std::chrono::steady_clock::now();
        resultOfEvaluation = ResultTable::mergeTable(resultOfEvaluation, clauseStruct[i].resultTable);
        auto stop = std::chrono::steady_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
        cout << "Time taken by mergeTable: "
             << duration.count() << " milliseconds" << endl;

//        start = std::chrono::steady_clock::now();
//        std::cout << "drop column before: " << resultOfEvaluation->getTable().size() << std::endl;
//        removeSynonym(*clauseStruct[i].clause, &synonymCount, resultOfEvaluation);
//        std::cout << "drop column after: " << resultOfEvaluation->getTable().size() << std::endl;
//        stop = std::chrono::steady_clock::now();
//        duration = duration_cast<std::chrono::milliseconds>(stop - start);
//        cout << "Time taken by dropColumn: "
//             << duration.count() << " milliseconds" << endl;
    }

    // For candidates not in result table, get all entities and merge.
    for (auto synonym : query->getCandidateList()) {
        if (!resultOfEvaluation->isSynonymPresent(synonym.argument.argumentName)) {
            getAllEntity(synonym.argument, resultOfEvaluation);
        }
    }

    query->resultTable->replace(resultOfEvaluation);
}

void QueryEvaluator::getAllEntity(Argument argument, QPS::ResultTable *resultTable) {
    vector<string> synonym = {argument.argumentName};
    unordered_set<vector<string>, StringVectorHash> results;
    unordered_set<string> entities = QPS_Interface::getAllEntity(&argument);
    for (auto e: entities) {
        results.insert({e});
    }
    ResultTable* entityTable = new ResultTable(synonym, results);
    resultTable->mergeTable(*entityTable);
}

void QueryEvaluator::groupClauses(int n, ClauseStruct* clauseStruct) {
    // Iterate through clauseList to build the synonymClausesMap
    std::unordered_map<std::string, std::unordered_set<int>> synonymClausesMap;
    for (int i = 0; i < n; i++) {
        Clause* clause = clauseStruct[i].clause;

        Argument arg1 = clause->getFirstArgument();
        Argument arg2 = clause->getSecondArgument();
        int numOfSynonyms = 0;
        if (Argument::isSynonym(arg1.argumentType)) {
            numOfSynonyms += 1;
            auto iter = synonymClausesMap.find(arg1.argumentName);
            if (iter != synonymClausesMap.end()) {
                iter->second.insert(i);
            } else {
                synonymClausesMap.insert(std::make_pair(arg1.argumentName, unordered_set<int> {i}));
            }
        }
        if (Argument::isSynonym(arg2.argumentType)) {
            numOfSynonyms += 1;
            auto iter = synonymClausesMap.find(arg2.argumentName);
            if (iter != synonymClausesMap.end()) {
                iter->second.insert(i);
            } else {
                synonymClausesMap.insert(std::make_pair(arg2.argumentName, unordered_set<int> {i}));
            }
        }
        if (numOfSynonyms == 0) { // clause with no synonym will be put into group 0 directly.
            clauseStruct[i].groupNumber = 0;
        }
    }

    // Merge adjacent clauses in each synonym's clauseSet
    UnionFindDisjointSet* ufds = new UnionFindDisjointSet(n);
    ufds->initialize();
    for (auto pair : synonymClausesMap) {
        int lastClauseIndex = -1;
        for (auto clauseIndex : pair.second) {
            if (lastClauseIndex != -1) {
                ufds->merge(lastClauseIndex, clauseIndex);
            }
            lastClauseIndex = clauseIndex;
        }
    }

    // Assign group number to each clause.
    for (int i = 0; i < n; i++) {
        clauseStruct->groupNumber = ufds->find(i);
    }
}

std::unordered_map<std::string, int>
QueryEvaluator::countSynonym(Query* query) {
    std::vector<Clause *> *clauseList = query->clauseList;
    std::unordered_set<std::string> candidates = query->getCandidates();
    unordered_map<string, int> synonymCount = {};
    for (auto clause: *clauseList) {
        Argument arg1 = clause->getFirstArgument();
        Argument arg2 = clause->getSecondArgument();
        if (Argument::isSynonym(arg1.argumentType)) {
            if (synonymCount.count(arg1.argumentName) == 0) {
                synonymCount[arg1.argumentName] = 1;
            } else {
                synonymCount[arg1.argumentName] += 1;
            }
        }
        if (Argument::isSynonym(arg2.argumentType)) {
            if (synonymCount.count(arg2.argumentName) == 0) {
                synonymCount[arg2.argumentName] = 1;
            } else {
                synonymCount[arg2.argumentName] += 1;
            }
        }
    }
    for (auto candidate: candidates) {
        if (synonymCount.count(candidate) == 0) {
            synonymCount[candidate] = 1;
        } else {
            synonymCount[candidate] += 1;
        }
    }
    return synonymCount;
}

void QueryEvaluator::removeSynonym(Clause &clause, std::unordered_map<std::string, int> *synonymCount,
                                   QPS::ResultTable *resultTable) {
    Argument arg1 = clause.getFirstArgument();
    Argument arg2 = clause.getSecondArgument();
    if (Argument::isSynonym(arg1.argumentType)) {
        if (synonymCount->count(arg1.argumentName) != 0) {
            (*synonymCount)[arg1.argumentName] -= 1;
        }
        if (synonymCount->find(arg1.argumentName)->second == 0) {
            if (resultTable->getColNum() == 1 && !resultTable->isEmptyTable()) {
                resultTable->setTrueTable();
            }
            resultTable->deleteColFromTable(arg1.argumentName);
        }
    }
    if (Argument::isSynonym(arg2.argumentType)) {
        if (synonymCount->count(arg2.argumentName) != 0) {
            (*synonymCount)[arg2.argumentName] -= 1;
        }
        if (synonymCount->find(arg2.argumentName)->second == 0) {
            if (resultTable->getColNum() == 1 && !resultTable->isEmptyTable()) {
                resultTable->setTrueTable();
            }
            resultTable->deleteColFromTable(arg2.argumentName);
        }
    }
    resultTable->deleteDuplicateRows({});
}