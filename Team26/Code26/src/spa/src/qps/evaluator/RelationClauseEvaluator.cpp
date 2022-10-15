#include "RelationClauseEvaluator.h"

const std::unordered_map<std::string, ::RelationType> RelationClauseEvaluator::evaluatorRelationMap = {
        {"Follows", ::RelationType::FOLLOWS},    // Follows(stmtRef, stmtRef)
        {"FollowStar", ::RelationType::FOLLOWS_T},  // Follows*(stmtRef, stmtRef)
        {"Parent", ::RelationType::PARENT}, // Parent(stmtRef, stmtRef)
        {"ParentStar", ::RelationType::PARENT_T},   // Parent*(stmtRef, stmtRef)
        {"Uses", ::RelationType::USES_S},
        {"Modifies", ::RelationType::MODIFIES_S},
        {"Calls", ::RelationType::CALLS},
        {"CallsStar", ::RelationType::CALLS_T},
        {"Next", ::RelationType::NEXT},
        {"NextStar", ::RelationType::NEXT_T},
        {"Affects", ::RelationType::AFFECTS},
        {"AffectsStar", ::RelationType::AFFECTS_T},
};

void RelationClauseEvaluator::evaluate(QPS::ResultTable *resultTable) {
    switch(this->relationClause->relationType) {
        case (::RelationType::CALLS_T): {
            evaluateCallsT(resultTable);
            break;
        }
        case (::RelationType::CALLS): {
            evaluateCalls(resultTable);
            break;
        }
        case (::RelationType::AFFECTS): {
            evaluateAffects(resultTable);
            break;
        }
        case (::RelationType::AFFECTS_T): {
            evaluateAffectsT(resultTable);
            break;
        }
        case (::RelationType::FOLLOWS): {
            evaluateFollows(resultTable);
            break;
        }
        case (::RelationType::FOLLOWS_T): {
            evaluateFollowsT(resultTable);
            break;
        }
        case (::RelationType::MODIFIES_S): {
            evaluateModify(resultTable);
            break;
        }
        case (::RelationType::NEXT): {
            evaluateNext(resultTable);
            break;
        }
        case (::RelationType::NEXT_T): {
            evaluateNextT(resultTable);
            break;
        }
        case (::RelationType::PARENT): {
            evaluateParent(resultTable);
            break;
        }
        case (::RelationType::PARENT_T): {
            evaluateParentT(resultTable);
            break;
        }
        case (::RelationType::USES_S): {
            evaluateUse(resultTable);
            break;
        }
        default:
            return;
    }

}

void RelationClauseEvaluator::evaluateUse(QPS::ResultTable *resultTable) {
    //Uses_P only
    if (relationClause->getFirstArgument().argumentType == Argument::PROCEDURE_ACTUAL_NAME
    || relationClause->getSecondArgument().argumentType == Argument::PROCEDURE_SYNONYM) {
        evaluateUsesP(resultTable);
        return;
    }
    //Uses_S only
    if (relationClause->getFirstArgument().argumentType != Argument::WILDCARD) {
        evaluateUsesS(resultTable);
        return;
    }
    //argument 1 is wildcard, can be both Uses_P and Uses_S
    QPS::ResultTable r1 = QPS::ResultTable();
    QPS::ResultTable r2 = QPS::ResultTable();
    evaluateUsesS(&r1);
    //if argument 2 is synonym, then merge both tables
    if (Argument::isSynonym(relationClause->getSecondArgument().argumentType)) {
        evaluateUsesP(&r2);
        resultTable = QPS::ResultTable::mergeTable(&r1, &r2);
        return;
    }
    //if argument 2 is wildcard or actual name, then we only need to return either a trueTable or a falseTable
    if (&r1 == QPS::trueTable) {
        resultTable = QPS::trueTable;
        return;
    }
    evaluateUsesP(&r2);
    resultTable = &r2;
}

void RelationClauseEvaluator::evaluateModify(QPS::ResultTable *resultTable) {
    //Modifies_P only
    if (relationClause->getFirstArgument().argumentType == Argument::PROCEDURE_ACTUAL_NAME
        || relationClause->getSecondArgument().argumentType == Argument::PROCEDURE_SYNONYM) {
        evaluateModifiesP(resultTable);
        return;
    }
    //Modifies_S only
    if (relationClause->getFirstArgument().argumentType != Argument::WILDCARD) {
        evaluateModifiesS(resultTable);
        return;
    }
    //argument 1 is wildcard, can be both Modifies_P and Modifies_S
    QPS::ResultTable r1 = QPS::ResultTable();
    QPS::ResultTable r2 = QPS::ResultTable();
    evaluateModifiesS(&r1);
    //if argument 2 is synonym, then merge both tables
    if (Argument::isSynonym(relationClause->getSecondArgument().argumentType)) {
        evaluateModifiesP(&r2);
        resultTable = QPS::ResultTable::mergeTable(&r1, &r2);
        return;
    }
    //if argument 2 is wildcard or actual name, then we only need to return either a trueTable or a falseTable
    if (&r1 == QPS::trueTable) {
        resultTable = QPS::trueTable;
        return;
    }
    evaluateModifiesP(&r2);
    resultTable = &r2;
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
    unordered_map<int, int> map = QPS_PKB_Interface::getAllFollowsRelations();
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    unordered_set<vector<string>, StringVectorHash> result;
    for (auto relation: map) { //e.g. "p1" calls "p2, p3"
        if (arg1.argumentType == Argument::NUMBER) {
            if (relation.first != stoi(arg1.argumentName)) {
                continue;
            }
        }
        if (arg2.argumentType == Argument::NUMBER) {
            if (relation.second != stoi(arg2.argumentName)) {
                continue;
            }
        }
        result.insert({to_string(relation.first), to_string(relation.second)});
    }
    if (!Argument::isSynonym(arg1.argumentType) && !Argument::isSynonym(arg2.argumentType)) {
        if (result.size() == 0) {
            resultTable = QPS::falseTable;
        } else {
            resultTable = QPS::trueTable;
        }
        return;
    }
    resultTable = filterTable(&result);
};

bool isStatementTypeMatched(StatementType::StmtType stmtType, Argument::ArgumentType argumentType) {
    if (argumentType == Argument::STMT_SYNONYM) {
        return true;
    }
    if (stmtType == StatementType::READ && argumentType == Argument::READ_SYNONYM) {
        return true;
    }
    if (stmtType == StatementType::ASSIGN && argumentType == Argument::ASSIGN_SYNONYM) {
        return true;
    }
    if (stmtType == StatementType::WHILE && argumentType == Argument::WHILE_SYNONYM) {
        return true;
    }
    if (stmtType == StatementType::IF && argumentType == Argument::IF_SYNONYM) {
        return true;
    }
    if (stmtType == StatementType::PRINT && argumentType == Argument::PRINT_SYNONYM) {
        return true;
    }
    if (stmtType == StatementType::CALL && argumentType == Argument::CALL_SYNONYM) {
        return true;
    }
    return false;
}

std::vector<std::vector<Statement>>& filterStmtList(const std::vector<std::vector<Statement>>& stmtList, Argument& arg) {
    std::vector<std::vector<Statement>> resultStmtList;
    for (auto iter = stmtList.begin(); iter != stmtList.end(); iter++) {
        std::vector<Statement> lineResult;
        for (auto stmt = iter->begin(); stmt != iter->end(); stmt++) {
            bool matched = true;
            if (Argument::isSynonym(arg.argumentType)) {
                matched = isStatementTypeMatched(stmt->type, arg.argumentType);
            }
            if (arg.argumentType == Argument::NUMBER) {
                matched = (stmt->lineNumber == stoi(arg.argumentName));
            }
            if (matched) {
                lineResult.push_back(*stmt);
            }
        }
        resultStmtList.push_back(lineResult);
    }
    return resultStmtList;
}

void RelationClauseEvaluator::evaluateFollowsT(QPS::ResultTable *resultTable) {
    std::vector<std::vector<Statement>> stmtList = QPS_PKB_Interface::getAllStmtLists();
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();

    std::vector<std::vector<Statement>> stmtListOfArg1 = filterStmtList(stmtList, arg1);
    std::vector<std::vector<Statement>> stmtListOfArg2 = filterStmtList(stmtList, arg2);

    vector<string>* synonyms = new vector<string>();
    if (Argument::isSynonym(arg1.argumentType)) {
        synonyms->push_back(arg1.argumentName);
    }
    if (Argument::isSynonym(arg2.argumentType)) {
        synonyms->push_back(arg2.argumentName);
    }

    unordered_set<vector<string>, StringVectorHash> result;
    for (int i = 0; i < stmtList.size(); i++) {
        for (Statement stmt1 : stmtListOfArg1.at(i)) {
            for (Statement stmt2 : stmtListOfArg2.at(i)) {
                if (stmt1.lineNumber >= stmt2.lineNumber) {
                    continue;
                }
                bool isSynArg1 = Argument::isSynonym(arg1.argumentType);
                bool isSynArg2 = Argument::isSynonym(arg2.argumentType);
                if (isSynArg1 && isSynArg2) {
                    result.insert({to_string(stmt1.lineNumber), to_string(stmt2.lineNumber)});
                    continue;
                }
                if (isSynArg1 && !isSynArg2) {
                    result.insert({to_string(stmt1.lineNumber)});
                    continue;
                }
                if (!isSynArg1 && isSynArg2) {
                    result.insert({to_string(stmt2.lineNumber)});
                    continue;
                }
                if (!isSynArg1 && !isSynArg2) {
                    resultTable = QPS::trueTable;
                    return;
                }
            }
        }
    }
    if (!Argument::isSynonym(arg1.argumentType) && !Argument::isSynonym(arg2.argumentType)) {
        resultTable = QPS::falseTable;
    } else {
        resultTable = new ResultTable(*synonyms, result);
    }
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
        if (arg1.argumentType == Argument::PROCEDURE_ACTUAL_NAME) {
            if (relation.first != arg1.argumentName) {
                continue;
            }
        }
        if (arg2.argumentType == Argument::PROCEDURE_ACTUAL_NAME) {
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
    if (!Argument::isSynonym(arg1.argumentType) && !Argument::isSynonym(arg2.argumentType)) {
        if (result.size() == 0) {
            resultTable = QPS::falseTable;
        } else {
            resultTable = QPS::trueTable;
        }
        return;
    }
    resultTable = filterTable(&result);
}

void RelationClauseEvaluator::filterRelations(unordered_map<int, vector<int>> map, QPS::ResultTable *resultTable) {
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    unordered_set<vector<string>, StringVectorHash> result;
    for (auto relation: map) { //e.g. "p1" calls "p2, p3"
        if (arg1.argumentType == Argument::NUMBER) {
            if (relation.first != stoi(arg1.argumentName)) {
                continue;
            }
        }
        if (arg2.argumentType == Argument::NUMBER) {
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
    if (!Argument::isSynonym(arg1.argumentType) && !Argument::isSynonym(arg2.argumentType)) {
        if (result.size() == 0) {
            resultTable = QPS::falseTable;
        } else {
            resultTable = QPS::trueTable;
        }
        return;
    }
    resultTable = filterTable(&result);
}

void
RelationClauseEvaluator::filterRelations(unordered_map<int, vector<std::string>> map, QPS::ResultTable *resultTable) {
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    unordered_set<vector<string>, StringVectorHash> result;
    for (auto relation: map) { //e.g. "p1" calls "p2, p3"
        if (arg1.argumentType == Argument::NUMBER) {
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
    if (!Argument::isSynonym(arg1.argumentType) && !Argument::isSynonym(arg2.argumentType)) {
        if (result.size() == 0) {
            resultTable = QPS::falseTable;
        } else {
            resultTable = QPS::trueTable;
        }
        return;
    }
    resultTable = filterTable(&result);
}

ResultTable *RelationClauseEvaluator::filterTable(unordered_set<vector<std::string>, QPS::StringVectorHash> *result) {
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    vector<string> synonyms;
    if (arg1.argumentType == Argument::PROCEDURE_SYNONYM) {
        synonyms.push_back(arg1.argumentName);
    }
    if (arg2.argumentType == Argument:: PROCEDURE_SYNONYM) {
        synonyms.push_back(arg2.argumentName);
    }
    unordered_set<vector<std::string>, QPS::StringVectorHash> filteredResult;
    bool isArg1Synonym = Argument::isSynonym(arg1.argumentType);
    bool isArg2Synonym = Argument::isSynonym(arg2.argumentType);
    for (auto r: *result) {
        vector<string> tableRow;
        if (isArg1Synonym) {
            tableRow.push_back(r[0]);
        }
        if (isArg2Synonym) {
            tableRow.push_back(r[1]);
        }
        filteredResult.insert(tableRow);
    }
    ResultTable r = ResultTable(synonyms, filteredResult);
    return &r;
}






