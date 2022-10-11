#include "RelationClauseEvaluator.h"

void RelationClauseEvaluator::evaluate(QPS::ResultTable *resultTable) {
    switch(evaluatorRelationMap.find(typeid(this->relationClause).name())->second) {
        case (::RelationType::CALLS_T): {
            evaluateCallsT(resultTable);
        }
        case (::RelationType::CALLS): {
            evaluateCalls(resultTable);
        }
        case (::RelationType::AFFECTS): {
            evaluateAffects(resultTable);
        }
        case (::RelationType::AFFECTS_T): {
            evaluateAffectsT(resultTable);
        }
        case (::RelationType::FOLLOWS): {
            evaluateFollows(resultTable);
        }
        case (::RelationType::FOLLOWS_T): {
            evaluateFollowsT(resultTable);
        }
        case (::RelationType::MODIFIES_P): {
            evaluateModifiesP(resultTable);
        }
        case (::RelationType::MODIFIES_S): {
            evaluateModifiesS(resultTable);
        }
        case (::RelationType::NEXT): {
            evaluateNext(resultTable);
        }
        case (::RelationType::NEXT_T): {
            evaluateNextT(resultTable);
        }
        case (::RelationType::PARENT): {
            evaluateParent(resultTable);
        }
        case (::RelationType::PARENT_T): {
            evaluateParentT(resultTable);
        }
        case (::RelationType::USES_P): {
            evaluateUsesP(resultTable);
        }
        case (::RelationType::USES_S): {
            evaluateUsesS(resultTable);
        }
        default:
            return;
    }

}

void RelationClauseEvaluator::evaluateCalls(QPS::ResultTable *resultTable) {
    filterRelations(QPS_PKB_Interface::getAllCallRelations(), resultTable);
}


void RelationClauseEvaluator::evaluateCallsT(QPS::ResultTable *resultTable) {
    filterRelations(QPS_PKB_Interface::getAllCallTRelations(), resultTable);
};
void RelationClauseEvaluator::evaluateAffects(QPS::ResultTable *resultTable) {

};
void RelationClauseEvaluator::evaluateAffectsT(QPS::ResultTable *resultTable) {

};
void RelationClauseEvaluator::evaluateFollows(QPS::ResultTable *resultTable) {

};

void RelationClauseEvaluator::evaluateFollowsT(QPS::ResultTable *resultTable) {

};
void RelationClauseEvaluator::evaluateModifiesS(QPS::ResultTable *resultTable) {
    filterRelations(QPS_PKB_Interface::getAllModifiesRelations(), resultTable);
};
void RelationClauseEvaluator::evaluateModifiesP(QPS::ResultTable *resultTable) {
    filterRelations(QPS_PKB_Interface::getAllModifiesProcRelations(), resultTable);
};
void RelationClauseEvaluator::evaluateNext(QPS::ResultTable *resultTable) {

};
void RelationClauseEvaluator::evaluateNextT(QPS::ResultTable *resultTable) {

};
void RelationClauseEvaluator::evaluateParent(QPS::ResultTable *resultTable) {
    filterRelations(QPS_PKB_Interface::getAllParentRelations(), resultTable);
};
void RelationClauseEvaluator::evaluateParentT(QPS::ResultTable *resultTable) {
    filterRelations(QPS_PKB_Interface::getAllParentTRelations(), resultTable);
};
void RelationClauseEvaluator::evaluateUsesP(QPS::ResultTable *resultTable) {
    filterRelations(QPS_PKB_Interface::getAllUsesProcRelations(), resultTable);
};
void RelationClauseEvaluator::evaluateUsesS(QPS::ResultTable *resultTable) {
    filterRelations(QPS_PKB_Interface::getAllUsesRelations(), resultTable);
};

bool RelationClauseEvaluator::existInStringVector(string s, vector<string> v) {
    return std::find(v.begin(), v.end(), s) != v.end();
}

bool RelationClauseEvaluator::existInIntVector(int s, vector<int> v) {
    return std::find(v.begin(), v.end(), s) != v.end();
}
void RelationClauseEvaluator::filterRelations(unordered_map<std::string, vector<std::string>> map,
                                              QPS::ResultTable *resultTable) {
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    unordered_set<vector<string>, StringVectorHash> result;
    for (auto relation: map) { //e.g. "p1" calls "p2, p3"
        if (arg1.argumentType == Argument::ACTUAL_NAME) {
            if (relation.first != arg1.argumentName) {
                continue;
            }
        }
        if (arg2.argumentType == Argument::ACTUAL_NAME) {
            if (!existInStringVector(arg2.argumentName, relation.second)) {
                continue;
            } else {
                result.insert({relation.first, arg2.argumentName});
                continue;
            }
        }
        for (auto s: relation.second) {
            result.insert({relation.first, s});
        }
    }
    vector<string> synonyms;
    if (arg1.argumentType == Argument::PROCEDURE_SYNONYM) {
        synonyms.push_back(arg1.argumentName);
    }
    if (arg2.argumentType == Argument:: PROCEDURE_SYNONYM) {
        synonyms.push_back(arg2.argumentName);
    }
    if (synonyms.size() == 0) {
        if (result.size() == 0) {
            resultTable = QPS::falseTable;
        } else {
            resultTable = QPS::trueTable;
        }
        return;
    }
    ResultTable r = ResultTable(synonyms, result);
    resultTable = &r;
}

void RelationClauseEvaluator::filterRelations(unordered_map<int, vector<int>> map, QPS::ResultTable *resultTable) {
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    unordered_set<vector<string>, StringVectorHash> result;
    for (auto relation: map) { //e.g. "p1" calls "p2, p3"
        if (arg1.argumentType == Argument::ACTUAL_NAME) {
            if (relation.first != stoi(arg1.argumentName)) {
                continue;
            }
        }
        if (arg2.argumentType == Argument::ACTUAL_NAME) {
            if (!existInIntVector(stoi(arg2.argumentName), relation.second)) {
                continue;
            } else {
                result.insert({to_string(relation.first), arg2.argumentName});
                continue;
            }
        }
        for (auto s: relation.second) {
            result.insert({to_string(relation.first), to_string(s)});
        }
    }
    vector<string> synonyms;
    if (arg1.argumentType == Argument::PROCEDURE_SYNONYM) {
        synonyms.push_back(arg1.argumentName);
    }
    if (arg2.argumentType == Argument:: PROCEDURE_SYNONYM) {
        synonyms.push_back(arg2.argumentName);
    }
    if (synonyms.size() == 0) {
        if (result.size() == 0) {
            resultTable = QPS::falseTable;
        } else {
            resultTable = QPS::trueTable;
        }
        return;
    }
    ResultTable r = ResultTable(synonyms, result);
    resultTable = &r;
}

void
RelationClauseEvaluator::filterRelations(unordered_map<int, vector<std::string>> map, QPS::ResultTable *resultTable) {
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    unordered_set<vector<string>, StringVectorHash> result;
    for (auto relation: map) { //e.g. "p1" calls "p2, p3"
        if (arg1.argumentType == Argument::ACTUAL_NAME) {
            if (relation.first != stoi(arg1.argumentName)) {
                continue;
            }
        }
        if (arg2.argumentType == Argument::ACTUAL_NAME) {
            if (!existInStringVector(arg2.argumentName, relation.second)) {
                continue;
            } else {
                result.insert({to_string(relation.first), arg2.argumentName});
                continue;
            }
        }
        for (auto s: relation.second) {
            result.insert({to_string(relation.first), s});
        }
    }
    vector<string> synonyms;
    if (arg1.argumentType == Argument::PROCEDURE_SYNONYM) {
        synonyms.push_back(arg1.argumentName);
    }
    if (arg2.argumentType == Argument:: PROCEDURE_SYNONYM) {
        synonyms.push_back(arg2.argumentName);
    }
    if (synonyms.size() == 0) {
        if (result.size() == 0) {
            resultTable = QPS::falseTable;
        } else {
            resultTable = QPS::trueTable;
        }
        return;
    }
    ResultTable r = ResultTable(synonyms, result);
    resultTable = &r;
}




