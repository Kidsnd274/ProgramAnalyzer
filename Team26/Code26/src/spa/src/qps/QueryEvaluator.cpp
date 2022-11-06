#include "QueryEvaluator.h"
#include "evaluator/ClauseAssigner.h"

bool lessThan(ClauseStruct& s1, ClauseStruct& s2) {
    if (s1.groupNumber == s2.groupNumber) {
        return s1.resultTable->getTable().size() < s2.resultTable->getTable().size();
    }
    return s1.groupNumber < s2.groupNumber;
}

bool haveCommonSynonyms(ResultTable* r1, ResultTable* r2) {
    for (auto syn : r1->getSynonymColRef()) {
        if (r2->isSynonymPresent(syn.first)) {
            return true;
        }
    }
    return false;
}

void QueryEvaluator::evaluate(Query* query) {
    if (query->getStatus() != VALID_QUERY) {
        return;
    }

    ClauseAssigner* clauseAssigner = new ClauseAssigner();

    // Add synonyms to the map
    std::unordered_map<std::string, int> synonymCount = countSynonym(query);

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
    std::sort(clauseStruct, clauseStruct + query->clauseList->size(), lessThan);

    // Merge the result tables
    ResultTable* resultOfEvaluation = new ResultTable();
    for (int i = 0; i < query->clauseList->size(); i++) {
         if (haveCommonSynonyms(clauseStruct[i].resultTable, resultOfEvaluation)) {
            resultOfEvaluation = ResultTable::mergeTable(resultOfEvaluation, clauseStruct[i].resultTable);
            removeSynonym(*clauseStruct[i].clause, &synonymCount, resultOfEvaluation);
        } else {
            removeSynonym(*clauseStruct[i].clause, &synonymCount, clauseStruct[i].resultTable);
            resultOfEvaluation = ResultTable::mergeTable(resultOfEvaluation, clauseStruct[i].resultTable);
        }
    }
    delete[] clauseStruct;

    // For candidates not in result table, get all entities and merge.
    for (auto synonym : query->getCandidateList()) {
        if (!resultOfEvaluation->isSynonymPresent(synonym.argument.argumentName)) {
            getAllEntity(synonym.argument, resultOfEvaluation);
        }
    }

    query->resultTable->replace(resultOfEvaluation);
}

void QueryEvaluator::getAllEntity(Argument argument, QPS::ResultTable *resultTable) {
    std::vector<std::string> synonym = {argument.argumentName};
    std::unordered_set<std::vector<std::string>, StringVectorHash> results;
    std::unordered_set<std::string> entities = QPS_Interface::getAllEntity(&argument);
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
                synonymClausesMap.insert(std::make_pair(arg1.argumentName, std::unordered_set<int> {i}));
            }
        }
        if (Argument::isSynonym(arg2.argumentType)) {
            numOfSynonyms += 1;
            auto iter = synonymClausesMap.find(arg2.argumentName);
            if (iter != synonymClausesMap.end()) {
                iter->second.insert(i);
            } else {
                synonymClausesMap.insert(std::make_pair(arg2.argumentName, std::unordered_set<int> {i}));
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
    std::unordered_map<std::string, int> synonymCount = {};
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
    std::vector<std::string> sToDelete;
    if (Argument::isSynonym(arg1.argumentType)) {
        if (synonymCount->count(arg1.argumentName) != 0) {
            (*synonymCount)[arg1.argumentName] -= 1;
        }
        if (synonymCount->find(arg1.argumentName)->second == 0) {
            if (resultTable->getColNum() == 1 && !resultTable->isEmptyTable()) {
                resultTable->setTrueTable();
            }
            sToDelete.push_back(arg1.argumentName);
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
            sToDelete.push_back(arg2.argumentName);
        }
    }
    resultTable->deleteColFromTable(sToDelete);
//    resultTable->deleteDuplicateRows({});
}
