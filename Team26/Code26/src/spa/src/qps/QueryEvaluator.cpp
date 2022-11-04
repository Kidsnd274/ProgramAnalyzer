#include "QueryEvaluator.h"
#include "evaluator/ClauseAssigner.h"

void QueryEvaluator::evaluate(Query* query) {
    if (query->getStatus() != VALID_QUERY) {
        return;
    }

    ResultTable* resultOfEvaluation = new ResultTable();
    ClauseAssigner* clauseAssigner = new ClauseAssigner();

    // Group the clauses
//    query->clauseList = QueryEvaluator::groupClauses(query->clauseList);

    // Add synonyms to the map
    unordered_map<string, int> synonymCount = countSynonym(query);

    // Evaluate the clauses
    for (auto iter = query->clauseList->begin(); iter != query->clauseList->end(); iter++) {
        ResultTable* resultTable = new ResultTable();
        clauseAssigner->assignClause(resultTable, *iter);
        resultOfEvaluation = ResultTable::mergeTable(resultOfEvaluation, resultTable);
        removeSynonym(**iter, &synonymCount, resultOfEvaluation);
    }
    for (auto synonym: query->getSynonymMap()) {
        if (!resultOfEvaluation->isSynonymPresent(synonym.second.argumentName)) {
            getAllEntity(synonym.second, resultOfEvaluation);
        }
    }
    query->resultTable = resultOfEvaluation;
}

void QueryEvaluator::getAllEntity(Argument argument, QPS::ResultTable *resultTable) {
    vector<string> synonym = {argument.argumentName};
    unordered_set<vector<string>, StringVectorHash> results;
    vector<string> entities = QPS_Interface::getAllEntity(&argument);
    for (auto e: entities) {
        results.insert({e});
    }
    ResultTable* entityTable = new ResultTable(synonym, results);
    resultTable->mergeTable(*entityTable);
}

int QueryEvaluator::calcHeuristic(Clause &clause) {
    return 0;
}

int QueryEvaluator::numOfSynonyms(Clause &clause) {
    int num = 0;
    if (Argument::isSynonym(clause.getFirstArgument().argumentType)) {
        num += 1;
    }
    if (Argument::isSynonym(clause.getSecondArgument().argumentType)) {
        num += 1;
    }
    return num;
}

std::vector<Clause*>* QueryEvaluator::groupClauses(std::vector<Clause*>* clauseList) {
    std::vector<Clause*>* resultList;
    // Iterate through clauseList to build the synonymClausesMap
    std::unordered_map<std::string, std::unordered_set<int>> synonymClausesMap;
    for (int i = 0; i < clauseList->size(); i++) {
        Clause* clause = clauseList->at(i);
        int numOfSynonyms = 0;
        Argument arg1 = clause->getFirstArgument();
        Argument arg2 = clause->getSecondArgument();
        if (Argument::isSynonym(arg1.argumentType)) {
            numOfSynonyms += 1;
            auto iter = synonymClausesMap.find(arg1.argumentName);
            if (iter != synonymClausesMap.end()) {
                iter->second.insert(i);
            } else {
                synonymClausesMap.insert(make_pair(arg1.argumentName, unordered_set<int> {i}));
            }
        }
        if (Argument::isSynonym(arg2.argumentType)) {
            numOfSynonyms += 1;
            auto iter = synonymClausesMap.find(arg2.argumentName);
            if (iter != synonymClausesMap.end()) {
                iter->second.insert(i);
            } else {
                synonymClausesMap.insert(make_pair(arg2.argumentName, unordered_set<int> {i}));
            }
        }
        if (numOfSynonyms == 0) { // Clauses without synonym will be put into group 1 directly.
            resultList->push_back(clause);
        }
    }

    // Merge adjacent clauses in each synonym's clauseSet
    UnionFindDisjointSet* ufds = new UnionFindDisjointSet(clauseList->size());
    ufds->initialize();
    int lastClauseIndex = -1;
    for (auto pair : synonymClausesMap) {
        for (auto clauseIndex : pair.second) {
            if (lastClauseIndex != -1) {
                ufds->merge(lastClauseIndex, clauseIndex);
            }
            lastClauseIndex = clauseIndex;
        }
    }

    // Iterate through clauseList and put clauses into corresponding group list.
    int numOfGroups = ufds->getNumberOfGroups();
    unordered_map<int, std::vector<int>> groups;
    for (int i = 0; i < clauseList->size(); i++) {
        int groupNumber = ufds->find(i);
        auto iter = groups.find(groupNumber);
        if (iter != groups.end()) {
            iter->second.push_back(i);
        } else {
            groups.insert(make_pair(groupNumber, i));
        }
    }

    // TODO: sort clauses within same group by heuristic.

    // Merge the group lists into one clauseList
    for (auto pair : groups) {
        for (auto clauseIndex : pair.second) {
            resultList->push_back(clauseList->at(clauseIndex));
        }
    }

    return resultList;
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
        if (synonymCount->count(arg1.argumentName) == 0) {
            resultTable->deleteColFromTable(arg1.argumentName);
        }
    }
    if (Argument::isSynonym(arg2.argumentType)) {
        if (synonymCount->count(arg2.argumentName) != 0) {
            (*synonymCount)[arg2.argumentName] -= 1;
        }
        if (synonymCount->count(arg2.argumentName) == 0) {
            resultTable->deleteColFromTable(arg2.argumentName);
        }
    }
}