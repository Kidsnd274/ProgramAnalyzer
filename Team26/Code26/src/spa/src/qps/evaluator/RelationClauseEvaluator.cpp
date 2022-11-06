#include "RelationClauseEvaluator.h"

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
    || relationClause->getFirstArgument().argumentType == Argument::PROCEDURE_SYNONYM) {
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
        ResultTable* resultTable1 = QPS::ResultTable::mergeTable(&r1, &r2);
        resultTable->replace(resultTable1);
        return;
    }
    //if argument 2 is wildcard or actual name, then we only need to return either a trueTable or a falseTable
    if (r1.isTrueTable()) {
        resultTable->setTrueTable();
        return;
    }
    evaluateUsesP(&r2);
    resultTable->replace(&r2);
}

void RelationClauseEvaluator::evaluateModify(QPS::ResultTable *resultTable) {
    //Modifies_P only
    if (relationClause->getFirstArgument().argumentType == Argument::PROCEDURE_ACTUAL_NAME
        || relationClause->getFirstArgument().argumentType == Argument::PROCEDURE_SYNONYM) {
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
        ResultTable* resultTable1 = QPS::ResultTable::mergeTable(&r1, &r2);;
        resultTable->replace(resultTable1);
        return;
    }
    //if argument 2 is wildcard or actual name, then we only need to return either a trueTable or a falseTable
    if (r1.isTrueTable()) {
        resultTable->setTrueTable();
        return;
    }
    evaluateModifiesP(&r2);
    resultTable->replace(&r2);
}
void RelationClauseEvaluator::evaluateCalls(QPS::ResultTable *resultTable) {
    filterRelations(QPS_Interface::getAllCallRelations(), resultTable);
}


void RelationClauseEvaluator::evaluateCallsT(QPS::ResultTable *resultTable) {
    filterRelations(QPS_Interface::getAllCallTRelations(), resultTable);
};
void RelationClauseEvaluator::evaluateAffectsT(QPS::ResultTable *resultTable) {
    Argument assignArgument = {"", Argument::ASSIGN_SYNONYM};
    std::unordered_set<std::string> assigns = QPS_Interface::getAllEntity(&assignArgument);
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();
    if (arg1.argumentType == Argument::ACTUAL_NAME) {
        int stmt1 = stoi(arg1.argumentName);
        std::unordered_set<STMT_NUM> s1 = QPS_Interface::getAffectsStar(stmt1);
        // ACTUAL_NAME, ACTUAL_NAME
        if (arg2.argumentType == Argument::ACTUAL_NAME) {
            int stmt2 = stoi(arg2.argumentName);
            if (find(s1.begin(), s1.end(), stmt2) != s1.end()) {
                resultTable->setTrueTable();
            } else {
                resultTable->setFalseTable();
            }
            return;
        }
        // ACTUAL_NAME, WILDCARD
        if (arg2.argumentType == Argument::WILDCARD) {
            if (s1.size() > 0) {
                resultTable->setFalseTable();
            } else {
                resultTable->setTrueTable();
            }
            return;
        }
        // ACTUAL_NAME, SYNONYM
        std::vector<std::string> synonyms = {arg2.argumentName};
        std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
        for (auto stmt2 : s1) {
            std::vector<std::string> currLine;
            currLine.push_back(std::to_string(stmt2));
            lines.insert(currLine);
        }
        resultTable = new ResultTable(synonyms, lines);
        return;
    }
    if (arg1.argumentType == Argument::WILDCARD && arg2.argumentType == Argument::WILDCARD) {
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffectsStar(stoi(a));
            if (affects.size() > 0) {
                resultTable->setTrueTable();
                return;
            }
        }
        resultTable->setFalseTable();
        return;
    }
    if (arg1.argumentType == Argument::WILDCARD && arg2.argumentType == Argument::ACTUAL_NAME) {
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffectsStar(stoi(a));
            if (find(affects.begin(), affects.end(), stoi(arg2.argumentName)) != affects.end()) {
                resultTable->setTrueTable();
                return;
            }
        }
        resultTable->setFalseTable();
        return;
    }
    std::vector<std::string> synonyms = {};
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
    if (Argument::isSynonym(arg1.argumentType) && arg2.argumentType == Argument::ACTUAL_NAME) {
        synonyms.push_back(arg1.argumentName);
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffectsStar(stoi(a));
            if (find(affects.begin(), affects.end(), stoi(arg2.argumentName)) != affects.end()) {
                lines.insert({a});
            }
        }
    }
    if (Argument::isSynonym(arg1.argumentType) && arg2.argumentType == Argument::WILDCARD) {
        synonyms.push_back(arg1.argumentName);
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffectsStar(stoi(a));
            if (affects.size() > 0) {
                lines.insert({a});
            }
        }
    }
    if (arg1.argumentType == Argument::WILDCARD && Argument::isSynonym(arg2.argumentType)) {
        synonyms.push_back(arg2.argumentName);
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffectsStar(stoi(a));
            for (auto second: affects) {
                lines.insert({std::to_string(second)});
            }
        }
    }
    if (Argument::isSynonym(arg1.argumentType) && Argument::isSynonym(arg2.argumentType)) {
        synonyms.push_back(arg1.argumentName);
        synonyms.push_back(arg2.argumentName);
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffectsStar(stoi(a));
            for (auto second: affects) {
                lines.insert({a, std::to_string(second)});
            }
        }
    }
    resultTable = new ResultTable(synonyms, lines);
    return;
};
void RelationClauseEvaluator::evaluateAffects(QPS::ResultTable *resultTable) {
    Argument assignArgument = {"", Argument::ASSIGN_SYNONYM};
    std::unordered_set<std::string> assigns = QPS_Interface::getAllEntity(&assignArgument);
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();
    if (arg1.argumentType == Argument::ACTUAL_NAME) {
        int stmt1 = stoi(arg1.argumentName);
        std::unordered_set<STMT_NUM> s1 = QPS_Interface::getAffects(stmt1);
        // ACTUAL_NAME, ACTUAL_NAME
        if (arg2.argumentType == Argument::ACTUAL_NAME) {
            int stmt2 = stoi(arg2.argumentName);
            if (find(s1.begin(), s1.end(), stmt2) != s1.end()) {
                resultTable->setTrueTable();
            } else {
                resultTable->setFalseTable();
            }
            return;
        }
        // ACTUAL_NAME, WILDCARD
        if (arg2.argumentType == Argument::WILDCARD) {
            if (s1.size() > 0) {
                resultTable->setFalseTable();
            } else {
                resultTable->setTrueTable();
            }
            return;
        }
        // ACTUAL_NAME, SYNONYM
        std::vector<std::string> synonyms = {arg2.argumentName};
        std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
        for (auto stmt2 : s1) {
            std::vector<std::string> currLine;
            currLine.push_back(std::to_string(stmt2));
            lines.insert(currLine);
        }
        resultTable = new ResultTable(synonyms, lines);
        return;
    }
    if (arg1.argumentType == Argument::WILDCARD && arg2.argumentType == Argument::WILDCARD) {
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffects(stoi(a));
            if (affects.size() > 0) {
                resultTable->setTrueTable();
                return;
            }
        }
        resultTable->setFalseTable();
        return;
    }
    if (arg1.argumentType == Argument::WILDCARD && arg2.argumentType == Argument::ACTUAL_NAME) {
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffects(stoi(a));
            if (find(affects.begin(), affects.end(), stoi(arg2.argumentName)) != affects.end()) {
                resultTable->setTrueTable();
                return;
            }
        }
        resultTable->setFalseTable();
        return;
    }
    std::vector<std::string> synonyms = {};
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
    if (Argument::isSynonym(arg1.argumentType) && arg2.argumentType == Argument::ACTUAL_NAME) {
        synonyms.push_back(arg1.argumentName);
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffects(stoi(a));
            if (find(affects.begin(), affects.end(), stoi(arg2.argumentName)) != affects.end()) {
                lines.insert({a});
            }
        }
    }
    if (Argument::isSynonym(arg1.argumentType) && arg2.argumentType == Argument::WILDCARD) {
        synonyms.push_back(arg1.argumentName);
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffects(stoi(a));
            if (affects.size() > 0) {
                lines.insert({a});
            }
        }
    }
    if (arg1.argumentType == Argument::WILDCARD && Argument::isSynonym(arg2.argumentType)) {
        synonyms.push_back(arg2.argumentName);
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffects(stoi(a));
            for (auto second: affects) {
                lines.insert({std::to_string(second)});
            }
        }
    }
    if (Argument::isSynonym(arg1.argumentType) && Argument::isSynonym(arg2.argumentType)) {
        synonyms.push_back(arg1.argumentName);
        synonyms.push_back(arg2.argumentName);
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffects(stoi(a));
            for (auto second: affects) {
                lines.insert({a, std::to_string(second)});
            }
        }
    }
    resultTable = new ResultTable(synonyms, lines);
    return;
};
void RelationClauseEvaluator::evaluateFollows(QPS::ResultTable *resultTable) {
    filterRelations(QPS_Interface::getAllFollowsRelations(), resultTable);
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

std::unordered_set<std::unordered_set<Statement*>*>& filterStmtList(const std::unordered_set<std::unordered_set<Statement*>*>& stmtList, Argument& arg) {
    std::unordered_set<std::unordered_set<Statement*>*>* resultStmtList = new std::unordered_set<std::unordered_set<Statement*>*>();
    for (auto iter : stmtList) {
        std::unordered_set<Statement*> lineResult;
        for (auto stmt : *iter) {
            bool matched = true;
            if (Argument::isSynonym(arg.argumentType)) {
                matched = isStatementTypeMatched(stmt->type, arg.argumentType);
            }
            if (arg.argumentType == Argument::NUMBER) {
                matched = (stmt->lineNumber == stoi(arg.argumentName));
            }
            if (matched) {
                lineResult.insert(stmt);
            }
        }
        resultStmtList->insert(&lineResult);
    }
    return *resultStmtList;
}

void RelationClauseEvaluator::evaluateFollowsT(QPS::ResultTable *resultTable) {
    std::unordered_set<std::unordered_set<Statement*>*> stmtList = QPS_Interface::getAllStmtLists();
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();

    std::unordered_set<std::unordered_set<Statement*>*> stmtListOfArg1 = filterStmtList(stmtList, arg1);
    std::unordered_set<std::unordered_set<Statement*>*> stmtListOfArg2 = filterStmtList(stmtList, arg2);

    std::unordered_set<std::string>* synonyms = new std::unordered_set<std::string>();
    if (Argument::isSynonym(arg1.argumentType)) {
        synonyms->insert(arg1.argumentName);
    }
    if (Argument::isSynonym(arg2.argumentType)) {
        synonyms->insert(arg2.argumentName);
    }

    std::unordered_set<std::vector<std::string>, StringVectorHash> result;
    for (int i = 0; i < stmtList.size(); i++) {
        for (Statement stmt1 : stmtListOfArg1.at(i)) {
            for (Statement stmt2 : stmtListOfArg2.at(i)) {
                if (stmt1.lineNumber >= stmt2.lineNumber) {
                    continue;
                }
                bool isSynArg1 = Argument::isSynonym(arg1.argumentType);
                bool isSynArg2 = Argument::isSynonym(arg2.argumentType);
                if (isSynArg1 && isSynArg2) {
                    result.insert({std::to_string(stmt1.lineNumber), std::to_string(stmt2.lineNumber)});
                    continue;
                }
                if (isSynArg1 && !isSynArg2) {
                    result.insert({std::to_string(stmt1.lineNumber)});
                    continue;
                }
                if (!isSynArg1 && isSynArg2) {
                    result.insert({std::to_string(stmt2.lineNumber)});
                    continue;
                }
                if (!isSynArg1 && !isSynArg2) {
                    resultTable->setTrueTable();
                    return;
                }
            }
        }
    }
    if (!Argument::isSynonym(arg1.argumentType) && !Argument::isSynonym(arg2.argumentType)) {
        resultTable->setFalseTable();
    } else {
        resultTable->replace(new ResultTable(*synonyms, result));
    }
};

void RelationClauseEvaluator::evaluateModifiesS(QPS::ResultTable *resultTable) {
    filterRelations(QPS_Interface::getAllModifiesRelations(), resultTable);
};

void RelationClauseEvaluator::evaluateModifiesP(QPS::ResultTable *resultTable) {
    filterRelations(QPS_Interface::getAllModifiesProcRelations(), resultTable);
};

void RelationClauseEvaluator::evaluateNext(QPS::ResultTable *resultTable) {
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();
    if (arg1.argumentType == Argument::ACTUAL_NAME) {
        int stmt1 = stoi(arg1.argumentName);
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt1);
        // ACTUAL_NAME, ACTUAL_NAME
        if (arg2.argumentType == Argument::ACTUAL_NAME) {
            int stmt2 = stoi(arg2.argumentName);
            if (QPS_Interface::runtimeExtractor->isNext(cfgHeadPtr, stmt1, stmt2) == true) {
                resultTable->setTrueTable();
            } else {
                resultTable->setFalseTable();
            }
            return;
        }
        // ACTUAL_NAME, WILDCARD
        if (arg2.argumentType == Argument::WILDCARD) {
            if (QPS_Interface::runtimeExtractor->getNextNodes(cfgHeadPtr, stmt1).empty()) {
                resultTable->setFalseTable();
            } else {
                resultTable->setTrueTable();
            }
            return;
        }
        // ACTUAL_NAME, SYNONYM
        std::vector<std::string> synonyms = {arg2.argumentName};
        std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
        for (auto stmt2 : QPS_Interface::runtimeExtractor->getNextNodes(cfgHeadPtr, stmt1)) {
            std::vector<std::string> currLine;
            currLine.push_back(std::to_string(stmt2));
            lines.insert(currLine);
        }
        resultTable = new ResultTable(synonyms, lines);
        return;
    }
    if (arg1.argumentType == Argument::WILDCARD) {
        // WILDCARD, WILDCARD
        if (arg2.argumentType == Argument::WILDCARD) {
            // If there is a proc with more than 1 statements, next(_, _) is always true
            std::vector<Procedure> procList = QPS_Interface::getProcList();
            for (auto proc : procList) {
                if (proc.endingStmtNo > proc.startingStmtNo) {
                    resultTable->setTrueTable();
                    return;
                }
            }
            resultTable->setFalseTable();
            return;
        }
        // WILDCARD, ACTUAL_NAME
        if (arg2.argumentType == Argument::ACTUAL_NAME) {
            int stmt2 = stoi(arg2.argumentName);
            CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt2);
            // next(_, s2) is always true unless s2 is the first statement in the procedure
            if (!cfgHeadPtr->isFirstStatementInCFG(stmt2)) {
                resultTable->setTrueTable();
            } else {
                resultTable->setFalseTable();
            }
            return;
        }
        // WILDCARD, SYNONYM
        std::vector<Procedure> procList = QPS_Interface::getProcList();
        std::vector<std::string> synonyms = {arg2.argumentName};
        std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
        for (auto proc : procList) {
            CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(proc.startingStmtNo);
            // next(_, s2) is always true unless s2 is the first statement in the procedure
            for (int stmt2 = proc.startingStmtNo; stmt2 <= proc.endingStmtNo; stmt2++) {
                if (!cfgHeadPtr->isFirstStatementInCFG(stmt2)) {
                    lines.insert(std::vector<std::string> {std::to_string(stmt2)});
                }
            }
        }
        resultTable = new ResultTable(synonyms, lines);
        return;
    }
    // SYNONYM, WILDCARD
    std::vector<Procedure> procList = QPS_Interface::getProcList();
    std::vector<std::string> synonyms = {arg1.argumentName};
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
    if (arg2.argumentType == Argument::WILDCARD) {
        for (auto proc : procList) {
            for (int i = proc.startingStmtNo; i <= proc.endingStmtNo; i++) {
                if (!QPS_Interface::runtimeExtractor->getNextNodes(proc.cfg, i).empty()) {
                    lines.insert(std::vector<std::string> {std::to_string(i)});
                }
            }
        }
        resultTable = new ResultTable(synonyms, lines);
        return;
    }
    // SYNONYM, ACTUAL_NAME
    if (arg2.argumentType == Argument::ACTUAL_NAME) {
        int stmt2 = stoi(arg2.argumentName);
        for (auto proc : procList) {
            for (int i = proc.startingStmtNo; i <= proc.endingStmtNo; i++) {
                if (QPS_Interface::runtimeExtractor->isNext(proc.cfg, i, stmt2)) {
                    lines.insert(std::vector<std::string> {std::to_string(i)});
                }
            }
        }
        resultTable = new ResultTable(synonyms, lines);
        return;
    }
    // SYNONYM, SYNONYM
    synonyms.push_back(arg2.argumentName);
    for (auto proc : procList) {
        for (int i = proc.startingStmtNo; i <= proc.endingStmtNo; i++) {
            for (auto stmt2 : QPS_Interface::runtimeExtractor->getNextNodes(proc.cfg, i)) {
                lines.insert(std::vector<std::string> {std::to_string(i), std::to_string(stmt2)});
            }
        }
    }
    resultTable = new ResultTable(synonyms, lines);
};

void RelationClauseEvaluator::evaluateNextT(QPS::ResultTable *resultTable) {
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();
    if (arg1.argumentType == Argument::ACTUAL_NAME) {
        int stmt1 = stoi(arg1.argumentName);
        std::unordered_set<STMT_NUM> nextStarSet = QPS_Interface::getNextStar(stmt1);
        // ACTUAL_NAME, ACTUAL_NAME
        if (arg2.argumentType == Argument::ACTUAL_NAME) {
            int stmt2 = stoi(arg2.argumentName);
            if (nextStarSet.find(stmt2) != nextStarSet.end()) {
                resultTable->setTrueTable();
            } else {
                resultTable->setFalseTable();
            }
            return;
        }
        // ACTUAL_NAME, WILDCARD
        if (arg2.argumentType == Argument::WILDCARD) {
            if (nextStarSet.empty()) {
                resultTable->setFalseTable();
            } else {
                resultTable->setTrueTable();
            }
            return;
        }
        // ACTUAL_NAME, SYNONYM
        std::vector<std::string> synonyms = {arg2.argumentName};
        std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
        for (auto stmt2 : nextStarSet) {
            lines.insert(std::vector<std::string> {std::to_string(stmt2)});
        }
        resultTable = new ResultTable(synonyms, lines);
        return;
    }
    if (arg1.argumentType == Argument::WILDCARD) {
        // WILDCARD, WILDCARD
        if (arg2.argumentType == Argument::WILDCARD) {
            std::vector<Procedure> procList = QPS_Interface::getProcList();
            // If there exist a procedure with more than 1 statements, next*(_, _) is always true
            for (auto proc: procList) {
                if (proc.endingStmtNo - proc.startingStmtNo > 0) {
                    resultTable->setTrueTable();
                    return;
                }
            }
            resultTable->setFalseTable();
            return;
        }
        // WILDCARD, ACTUAL_NAME
        if (arg2.argumentType == Argument::ACTUAL_NAME) {
            int stmt2 = stoi(arg2.argumentName);
            CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt2);
            // next*(_, s2) is always true unless s2 is the first statement in the procedure
            if (!cfgHeadPtr->isFirstStatementInCFG(stmt2)) {
                resultTable->setTrueTable();
            } else {
                resultTable->setFalseTable();
            }
            return;
        }
        // WILDCARD, SYNONYM
        std::vector<Procedure> procList = QPS_Interface::getProcList();
        std::vector<std::string> synonyms = {arg2.argumentName};
        std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
        for (auto proc : procList) {
            CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(proc.startingStmtNo);
            // next*(_, s2) is always true unless s2 is the first statement in the procedure
            for (int stmt2 = proc.startingStmtNo; stmt2 <= proc.endingStmtNo; stmt2++) {
                if (!cfgHeadPtr->isFirstStatementInCFG(stmt2)) {
                    lines.insert(std::vector<std::string> {std::to_string(stmt2)});
                }
            }
        }
        resultTable = new ResultTable(synonyms, lines);
        return;
    }

    std::vector<Procedure> procList = QPS_Interface::getProcList();
    std::vector<std::string> synonyms = {arg1.argumentName};
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
    // SYNONYM, WILDCARD
    if (arg2.argumentType == Argument::WILDCARD) {
        for (auto proc : procList) {
            for (int i = proc.startingStmtNo; i <= proc.endingStmtNo; i++) {
                std::unordered_set<STMT_NUM> nextStarSet = QPS_Interface::getNextStar(i);
                if (!nextStarSet.empty()) {
                    lines.insert(std::vector<std::string> {std::to_string(i)});
                }
            }
        }
        resultTable = new ResultTable(synonyms, lines);
        return;
    }
    // SYNONYM, ACTUAL_NAME
    if (arg2.argumentType == Argument::ACTUAL_NAME) {
        int stmt2 = stoi(arg2.argumentName);
        Procedure* proc = QPS_Interface::getProcByStmt(stmt2);
        for (int stmt1 = proc->startingStmtNo; stmt1 <= proc->endingStmtNo; stmt1++) {
            std::unordered_set<STMT_NUM> nextStarSet = QPS_Interface::getNextStar(stmt1);
            if (nextStarSet.find(stmt2) != nextStarSet.end()) {
                lines.insert(std::vector<std::string> {std::to_string(stmt1)});
            }
        }
        resultTable = new ResultTable(synonyms, lines);
        return;
    }
    // SYNONYM, SYNONYM
    synonyms.push_back(arg2.argumentName);
    for (auto proc : procList) {
        for (int stmt1 = proc.startingStmtNo; stmt1 <= proc.endingStmtNo; stmt1++) {
            std::unordered_set<STMT_NUM> nextStarSet = QPS_Interface::getNextStar(stmt1);
            for (auto stmt2 : nextStarSet) {
                lines.insert(std::vector<std::string> {std::to_string(stmt1), std::to_string(stmt2)});
            }
        }
    }
    resultTable = new ResultTable(synonyms, lines);
};

void RelationClauseEvaluator::evaluateParent(QPS::ResultTable *resultTable) {
    filterRelations(QPS_Interface::getAllParentRelations(), resultTable);
};

void RelationClauseEvaluator::evaluateParentT(QPS::ResultTable *resultTable) {
    filterRelations(QPS_Interface::getAllParentTRelations(), resultTable);
};

void RelationClauseEvaluator::evaluateUsesP(QPS::ResultTable *resultTable) {
    filterRelations(QPS_Interface::getAllUsesProcRelations(), resultTable);
};

void RelationClauseEvaluator::evaluateUsesS(QPS::ResultTable *resultTable) {
    filterRelations(QPS_Interface::getAllUsesRelations(), resultTable);
};

bool RelationClauseEvaluator::existInStringVector(std::string s, std::vector<std::string> v) {
    return std::find(v.begin(), v.end(), s) != v.end();
}

bool RelationClauseEvaluator::existInStringUnorderedSet(std::string s, std::unordered_set<std::string> set) {
    return set.find(s) != set.end();
}

bool RelationClauseEvaluator::existInIntVector(int s, std::vector<int> v) {
    return std::find(v.begin(), v.end(), s) != v.end();
}

bool RelationClauseEvaluator::existInIntUnorderedSet(int s, std::unordered_set<int> set) {
    return set.find(s) != set.end();
}

void RelationClauseEvaluator::filterRelations(std::unordered_map<string, std::unordered_set<std::string>> map,
                                              QPS::ResultTable *resultTable) {
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    std::unordered_set<std::vector<std::string>, StringVectorHash> result;
    for (auto relation: map) { //e.g. "p1" calls "p2, p3"
        if (arg1.argumentType == Argument::PROCEDURE_ACTUAL_NAME) {
            if (relation.first != arg1.argumentName) {
                continue;
            }
        }
        if (arg2.argumentType == Argument::ACTUAL_NAME || arg2.argumentType == Argument::PROCEDURE_ACTUAL_NAME) {
            if (!existInStringUnorderedSet(arg2.argumentName, relation.second)) {
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
            resultTable->setFalseTable();
        } else {
            resultTable->setTrueTable();
        }
        return;
    }
    resultTable->replace(filterTable(&result));
}

void RelationClauseEvaluator::filterRelations(std::unordered_map<int, std::unordered_set<int>> map, QPS::ResultTable *resultTable) {
    std::unordered_map<int, std::unordered_set<int>> temp = map;
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    std::unordered_set<std::vector<std::string>, StringVectorHash> result;
    for (auto relation: map) {  // e.g. "p1" calls "p2, p3"
        if (arg1.argumentType == Argument::NUMBER) {
            if (relation.first != stoi(arg1.argumentName)) {
                continue;
            }
        }
        if (arg2.argumentType == Argument::NUMBER) {
            if (!existInIntUnorderedSet(stoi(arg2.argumentName), relation.second)) {
                continue;
            } else {
                result.insert({std::to_string(relation.first), arg2.argumentName});
                continue;
            }
        }
        for (auto s: relation.second) {
            result.insert({std::to_string(relation.first), std::to_string(s)});
        }
    }
    if (!Argument::isSynonym(arg1.argumentType) && !Argument::isSynonym(arg2.argumentType)) {
        if (result.size() == 0) {
            resultTable->setFalseTable();
        } else {
            resultTable->setTrueTable();
        }
        return;
    }
    resultTable->replace(filterTable(&result));
}

void RelationClauseEvaluator::filterRelations(std::unordered_map<int, std::unordered_set<std::string>> map, QPS::ResultTable *resultTable) {
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    std::unordered_set<std::vector<std::string>, StringVectorHash> result;
    for (auto relation: map) { //e.g. "p1" calls "p2, p3"
        if (arg1.argumentType == Argument::NUMBER) {
            if (relation.first != stoi(arg1.argumentName)) {
                continue;
            }
        }
        if (arg2.argumentType == Argument::ACTUAL_NAME) {
            if (!existInStringUnorderedSet(arg2.argumentName, relation.second)) {
                continue;
            } else {
                result.insert({std::to_string(relation.first), arg2.argumentName});
                continue;
            }
        }
        for (auto s: relation.second) {
            result.insert({std::to_string(relation.first), s});
        }
    }
    if (!Argument::isSynonym(arg1.argumentType) && !Argument::isSynonym(arg2.argumentType)) {
        if (result.size() == 0) {
            resultTable->setFalseTable();
        } else {
            resultTable->setTrueTable();
        }
        return;
    }
    resultTable->replace(filterTable(&result));
}

void RelationClauseEvaluator::filterRelations(std::unordered_map<int, int> map, QPS::ResultTable *resultTable) {
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    std::unordered_set<std::vector<std::string>, StringVectorHash> result;
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
        result.insert({std::to_string(relation.first), std::to_string(relation.second)});
    }
    if (!Argument::isSynonym(arg1.argumentType) && !Argument::isSynonym(arg2.argumentType)) {
        if (result.size() == 0) {
            resultTable->setFalseTable();
        } else {
            resultTable->setTrueTable();
        }
        return;
    }
    resultTable->replace(filterTable(&result));
}

ResultTable* RelationClauseEvaluator::filterTable(std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> *result) {
    Argument arg1 = relationClause->getFirstArgument();
    Argument arg2 = relationClause->getSecondArgument();
    std::vector<std::string> a1;
    std::vector<std::string> a2;
    bool isArg1Synonym = Argument::isSynonym(arg1.argumentType);
    bool isArg2Synonym = Argument::isSynonym(arg2.argumentType);
    bool isArg2Pushed = false;
    std::vector<std::string> synonyms;
    if (isArg1Synonym) {
        synonyms.push_back(arg1.argumentName);
        a1 = QPS_Interface::getAllEntity(&arg1);
    }
    if (isArg2Synonym && std::find(synonyms.begin(), synonyms.end(), arg2.argumentName) == synonyms.end()) {
        synonyms.push_back(arg2.argumentName);
        a2 = QPS_Interface::getAllEntity(&arg2);
        isArg2Pushed = true;
    }
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> filteredResult;
    for (auto r: *result) {
        std::vector<std::string> tableRow;
        if (isArg1Synonym && isArg2Synonym) {
            if (std::find(a1.begin(), a1.end(), r[0])!= a1.end()
            && std::find(a2.begin(), a2.end(), r[1])!= a2.end()) {
                if (arg1.argumentType == arg2.argumentType && arg1.argumentName == arg2.argumentName) {
                    if (r[0] != r[1]) {
                        continue;
                    }
                }
                tableRow.push_back(r[0]);
                if (isArg2Pushed) {
                    tableRow.push_back(r[1]);
                }
                filteredResult.insert(tableRow);
            }
        } else if (isArg1Synonym && std::find(a1.begin(), a1.end(), r[0])!= a1.end() ) {
            tableRow.push_back(r[0]);
            filteredResult.insert(tableRow);
        } else if (isArg2Synonym && std::find(a2.begin(), a2.end(), r[1])!= a2.end()) {
            tableRow.push_back(r[1]);
            filteredResult.insert(tableRow);
        }

    }

    ResultTable* r = new ResultTable(synonyms, filteredResult);
    return r;
}
