#include "RelationClauseEvaluator.h"

void RelationClauseEvaluator::evaluate(QPS::ResultTable *resultTable) {
    switch(this->relationClause->relationType) {
        case (::RelationType::CALLS_T): {
            filterRelations(QPS_Interface::getAllCallTRelations(), resultTable);
            break;
        }
        case (::RelationType::CALLS): {
            filterRelations(QPS_Interface::getAllCallRelations(), resultTable);
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
            filterRelations(QPS_Interface::getAllFollowsRelations(), resultTable);
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
            filterRelations(QPS_Interface::getAllParentRelations(PARENT), resultTable);
            break;
        }
        case (::RelationType::PARENT_T): {
            filterRelations(QPS_Interface::getAllParentRelations(PARENT_T), resultTable);
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

std::vector<std::vector<Statement>>& filterStmtList(const std::unordered_set<std::unordered_set<Statement*>*>& stmtList, Argument& arg) {
    std::vector<std::vector<Statement>>* resultStmtList = new std::vector<std::vector<Statement>>();
    for (auto iter : stmtList) {
        std::vector<Statement> lineResult;
        for (auto stmt : *iter) {
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
        resultStmtList->push_back(lineResult);
    }
    return *resultStmtList;
}

void RelationClauseEvaluator::evaluateAffects(QPS::ResultTable *resultTable) {
    Argument assignArgument = {"", Argument::ASSIGN_SYNONYM};
    std::unordered_set<std::string> assigns = QPS_Interface::getAllEntity(&assignArgument);
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();
    // ensure both synonyms are assigns
    if (!validateAffectsParameter(resultTable)) {
        return;
    }
    // start evaluation
    if (arg1.argumentType == Argument::NUMBER) {
        int stmt1 = stoi(arg1.argumentName);
        std::unordered_set<STMT_NUM> s1 = QPS_Interface::getAffects(stmt1);
        // ACTUAL_NAME, ACTUAL_NAME
        if (arg2.argumentType == Argument::NUMBER) {
            int stmt2 = stoi(arg2.argumentName);
            if (s1.find(stmt2) != s1.end()) {
                resultTable->setTrueTable();
            } else {
                resultTable->setFalseTable();
            }
            return;
        }
        // ACTUAL_NAME, WILDCARD
        if (arg2.argumentType == Argument::WILDCARD) {
            if (s1.size() > 0) {
                resultTable->setTrueTable();
            } else {
                resultTable->setFalseTable();
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
        ResultTable *table = new ResultTable(synonyms, lines);
        resultTable->replace(table);
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
    if (arg1.argumentType == Argument::WILDCARD && arg2.argumentType == Argument::NUMBER) {
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffects(stoi(a));
            if (affects.find(stoi(arg2.argumentName)) != affects.end()) {
                resultTable->setTrueTable();
                return;
            }
        }
        resultTable->setFalseTable();
        return;
    }
    std::vector<std::string> synonyms = {};
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
    if (Argument::isSynonym(arg1.argumentType) && arg2.argumentType == Argument::NUMBER) {
        synonyms.push_back(arg1.argumentName);
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffects(stoi(a));
            if (affects.find(stoi(arg2.argumentName)) != affects.end()) {
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
        if (arg1.argumentName != arg2.argumentName) {
            synonyms.push_back(arg2.argumentName);
        }
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffects(stoi(a));
            for (auto second: affects) {
                if (arg1.argumentName == arg2.argumentName) {
                    if (a == std::to_string(second)) {
                        lines.insert({a});
                    }
                } else {
                    lines.insert({a, std::to_string(second)});
                }
            }
        }
    }
    ResultTable *table = new ResultTable(synonyms, lines);
    resultTable->replace(table);
    return;
};

void RelationClauseEvaluator::evaluateAffectsT(QPS::ResultTable *resultTable) {
    Argument assignArgument = {"", Argument::ASSIGN_SYNONYM};
    std::unordered_set<std::string> assigns = QPS_Interface::getAllEntity(&assignArgument);
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();
    // ensure both synonyms are assigns
    if (!validateAffectsParameter(resultTable)) {
        return;
    }
    // start evaluation
    if (arg1.argumentType == Argument::NUMBER) {
        int stmt1 = stoi(arg1.argumentName);
        std::unordered_set<STMT_NUM> s1 = QPS_Interface::getAffectsStar(stmt1);
        // ACTUAL_NAME, ACTUAL_NAME
        if (arg2.argumentType == Argument::NUMBER) {
            int stmt2 = stoi(arg2.argumentName);
            if (s1.find(stmt2) != s1.end()) {
                resultTable->setTrueTable();
            } else {
                resultTable->setFalseTable();
            }
            return;
        }
        // ACTUAL_NAME, WILDCARD
        if (arg2.argumentType == Argument::WILDCARD) {
            if (s1.size() > 0) {
                resultTable->setTrueTable();
            } else {
                resultTable->setFalseTable();
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
        ResultTable *table = new ResultTable(synonyms, lines);
        resultTable->replace(table);
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
    if (arg1.argumentType == Argument::WILDCARD && arg2.argumentType == Argument::NUMBER) {
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffectsStar(stoi(a));
            if (affects.find(stoi(arg2.argumentName)) != affects.end()) {
                resultTable->setTrueTable();
                return;
            }
        }
        resultTable->setFalseTable();
        return;
    }
    std::vector<std::string> synonyms = {};
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
    if (Argument::isSynonym(arg1.argumentType) && arg2.argumentType == Argument::NUMBER) {
        synonyms.push_back(arg1.argumentName);
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffectsStar(stoi(a));
            if (affects.find(stoi(arg2.argumentName)) != affects.end()) {
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
        if (arg1.argumentName != arg2.argumentName) {
            synonyms.push_back(arg2.argumentName);
        }
        for (auto a: assigns) {
            std::unordered_set<STMT_NUM> affects = QPS_Interface::getAffectsStar(stoi(a));
            for (auto second: affects) {
                if (arg1.argumentName == arg2.argumentName) {
                    if (a == std::to_string(second)) {
                        lines.insert({a});
                    }
                } else {
                    lines.insert({a, std::to_string(second)});
                }
            }
        }
    }
    ResultTable *table = new ResultTable(synonyms, lines);
    resultTable->replace(table);
    return;
};

void RelationClauseEvaluator::evaluateUse(QPS::ResultTable *resultTable) {
    //Uses_P only
    if (relationClause->getFirstArgument().argumentType == Argument::PROCEDURE_ACTUAL_NAME
        || relationClause->getFirstArgument().argumentType == Argument::PROCEDURE_SYNONYM) {
        filterRelations(QPS_Interface::getAllUsesProcRelations(), resultTable);
        return;
    }
    //Uses_S only
    if (relationClause->getFirstArgument().argumentType != Argument::WILDCARD) {
        filterRelations(QPS_Interface::getAllUsesRelations(), resultTable);
        return;
    }
    //argument 1 is wildcard, can be both Uses_P and Uses_S
    QPS::ResultTable r1 = QPS::ResultTable();
    QPS::ResultTable r2 = QPS::ResultTable();
    filterRelations(QPS_Interface::getAllUsesRelations(), &r1);
    //if argument 2 is synonym, then merge both tables
    if (Argument::isSynonym(relationClause->getSecondArgument().argumentType)) {
        filterRelations(QPS_Interface::getAllUsesProcRelations(), &r2);
        ResultTable* resultTable1 = QPS::ResultTable::mergeTable(&r1, &r2);
        resultTable->replace(resultTable1);
        return;
    }
    //if argument 2 is wildcard or actual name, then we only need to return either a trueTable or a falseTable
    if (r1.isTrueTable()) {
        resultTable->setTrueTable();
        return;
    }
    filterRelations(QPS_Interface::getAllUsesProcRelations(), &r2);
    resultTable->replace(&r2);
}

void RelationClauseEvaluator::evaluateModify(QPS::ResultTable *resultTable) {
    //Modifies_P only
    if (relationClause->getFirstArgument().argumentType == Argument::PROCEDURE_ACTUAL_NAME
        || relationClause->getFirstArgument().argumentType == Argument::PROCEDURE_SYNONYM) {
        filterRelations(QPS_Interface::getAllModifiesProcRelations(), resultTable);
        return;
    }
    //Modifies_S only
    if (relationClause->getFirstArgument().argumentType != Argument::WILDCARD) {
        filterRelations(QPS_Interface::getAllModifiesRelations(), resultTable);
        return;
    }
    //argument 1 is wildcard, can be both Modifies_P and Modifies_S
    QPS::ResultTable r1 = QPS::ResultTable();
    QPS::ResultTable r2 = QPS::ResultTable();
    filterRelations(QPS_Interface::getAllModifiesRelations(), &r1);
    //if argument 2 is synonym, then merge both tables
    if (Argument::isSynonym(relationClause->getSecondArgument().argumentType)) {
        filterRelations(QPS_Interface::getAllModifiesProcRelations(), &r2);
        ResultTable* resultTable1 = QPS::ResultTable::mergeTable(&r1, &r2);;
        resultTable->replace(resultTable1);
        return;
    }
    //if argument 2 is wildcard or actual name, then we only need to return either a trueTable or a falseTable
    if (r1.isTrueTable()) {
        resultTable->setTrueTable();
        return;
    }
    filterRelations(QPS_Interface::getAllModifiesProcRelations(), &r2);
    resultTable->replace(&r2);
}

void RelationClauseEvaluator::evaluateFollowsT(QPS::ResultTable *resultTable) {
    std::unordered_set<std::unordered_set<Statement*>*> stmtList = QPS_Interface::getAllStmtLists();
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();

    std::vector<std::vector<Statement>> stmtListOfArg1 = filterStmtList(stmtList, arg1);
    std::vector<std::vector<Statement>> stmtListOfArg2 = filterStmtList(stmtList, arg2);

    std::vector<std::string>* synonyms = new std::vector<std::string>();
    if (Argument::isSynonym(arg1.argumentType)) {
        synonyms->push_back(arg1.argumentName);
    }
    if (Argument::isSynonym(arg2.argumentType)) {
        synonyms->push_back(arg2.argumentName);
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

void RelationClauseEvaluator::evaluateNext(QPS::ResultTable *resultTable) {
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();
    if (arg1.argumentType == Argument::NUMBER) {
        int stmt1 = stoi(arg1.argumentName);
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt1);
        // ACTUAL_NAME, ACTUAL_NAME
        if (arg2.argumentType == Argument::NUMBER) {
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
        std::unordered_set<std::string> actualNames = QPS_Interface::getAllEntity(&arg2);
        for (auto stmt2 : QPS_Interface::runtimeExtractor->getNextNodes(cfgHeadPtr, stmt1)) {
            if (actualNames.find(std::to_string(stmt2)) == actualNames.end()) {
                continue;
            }
            std::vector<std::string> currLine;
            currLine.push_back(std::to_string(stmt2));
            lines.insert(currLine);
        }
        resultTable->replace(new ResultTable(synonyms, lines));
        return;
    }
    if (arg1.argumentType == Argument::WILDCARD) {
        // WILDCARD, WILDCARD
        if (arg2.argumentType == Argument::WILDCARD) {
            // If there is a proc with more than 1 statements, next(_, _) is always true
            std::unordered_set<Procedure*> procList = QPS_Interface::getProcList();
            for (auto proc : procList) {
                if (proc->endingStmtNo > proc->startingStmtNo) {
                    resultTable->setTrueTable();
                    return;
                }
            }
            resultTable->setFalseTable();
            return;
        }
        // WILDCARD, ACTUAL_NAME
        if (arg2.argumentType == Argument::NUMBER) {
            int stmt2 = stoi(arg2.argumentName);
            CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt2);
            // next(_, s2) is always true unless s2 is the first statement in the procedure
            if (!cfgHeadPtr->isFirstStatementInCFG(stmt2)) {
                resultTable->setTrueTable();
            } else {
                std::unordered_set<std::string> whiles = QPS_Interface::getAllEntity(new Argument("", Argument::WHILE_SYNONYM));
                if (whiles.find(std::to_string(stmt2)) != whiles.end()) {
                    resultTable->setTrueTable();
                } else {
                    resultTable->setFalseTable();
                }
            }
            return;
        }
        // WILDCARD, SYNONYM
        std::unordered_set<Procedure*> procList = QPS_Interface::getProcList();
        std::vector<std::string> synonyms = {arg2.argumentName};
        std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
        std::unordered_set<std::string> actualNames = QPS_Interface::getAllEntity(&arg2);
        for (auto proc : procList) {
            CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(proc->startingStmtNo);
            // next(_, s2) is always true unless s2 is the first statement in the procedure
            for (int stmt2 = proc->startingStmtNo; stmt2 <= proc->endingStmtNo; stmt2++) {
                if (actualNames.find(std::to_string(stmt2)) == actualNames.end()) {
                    continue;
                }
                if (!cfgHeadPtr->isFirstStatementInCFG(stmt2)) {
                    lines.insert(std::vector<std::string> {std::to_string(stmt2)});
                } else {
                    std::unordered_set<std::string> whiles = QPS_Interface::getAllEntity(new Argument("", Argument::WHILE_SYNONYM));
                    if (whiles.find(std::to_string(stmt2)) != whiles.end()) {
                        lines.insert(std::vector<std::string> {std::to_string(stmt2)});
                    }
                }
            }
        }
        resultTable->replace(new ResultTable(synonyms, lines));
        return;
    }
    // SYNONYM, WILDCARD
    std::unordered_set<Procedure*> procList = QPS_Interface::getProcList();
    std::vector<std::string> synonyms = {arg1.argumentName};
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
    std::unordered_set<std::string> actualNames = QPS_Interface::getAllEntity(&arg1);
    if (arg2.argumentType == Argument::WILDCARD) {
        for (auto proc : procList) {
            for (int i = proc->startingStmtNo; i <= proc->endingStmtNo; i++) {
                if (actualNames.find(std::to_string(i))== actualNames.end()) {
                    continue;
                }
                if (!QPS_Interface::runtimeExtractor->getNextNodes(proc->cfg, i).empty()) {
                    lines.insert(std::vector<std::string> {std::to_string(i)});
                }
            }
        }
        resultTable->replace(new ResultTable(synonyms, lines));
        return;
    }
    // SYNONYM, ACTUAL_NAME
    if (arg2.argumentType == Argument::NUMBER) {
        int stmt2 = stoi(arg2.argumentName);
        for (auto proc : procList) {
            for (int i = proc->startingStmtNo; i <= proc->endingStmtNo; i++) {
                if (actualNames.find(std::to_string(i)) == actualNames.end()) {
                    continue;
                }
                if (QPS_Interface::runtimeExtractor->isNext(proc->cfg, i, stmt2)) {
                    lines.insert(std::vector<std::string> {std::to_string(i)});
                }
            }
        }
        resultTable->replace(new ResultTable(synonyms, lines));
        return;
    }
    // SYNONYM, SYNONYM
    synonyms.push_back(arg2.argumentName);
    std::unordered_set<std::string> actualNames2 = QPS_Interface::getAllEntity(&arg2);
    for (auto proc : procList) {
        for (int i = proc->startingStmtNo; i <= proc->endingStmtNo; i++) {
            if (actualNames.find(std::to_string(i)) == actualNames.end()) {
                continue;
            }
            for (auto stmt2 : QPS_Interface::runtimeExtractor->getNextNodes(proc->cfg, i)) {
                if (actualNames2.find(std::to_string(stmt2)) == actualNames2.end()) {
                    continue;
                }
                lines.insert(std::vector<std::string> {std::to_string(i), std::to_string(stmt2)});
            }
        }
    }
    resultTable->replace(new ResultTable(synonyms, lines));
};

void RelationClauseEvaluator::evaluateNextT(QPS::ResultTable *resultTable) {
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();
    if (arg1.argumentType == Argument::NUMBER) {
        int stmt1 = stoi(arg1.argumentName);
        std::unordered_set<STMT_NUM> nextStarSet = QPS_Interface::getNextStar(stmt1);
        // ACTUAL_NAME, ACTUAL_NAME
        if (arg2.argumentType == Argument::NUMBER) {
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
        std::unordered_set<std::string> actualNames = QPS_Interface::getAllEntity(&arg2);
        for (auto stmt2 : nextStarSet) {
            if (actualNames.find(std::to_string(stmt2)) == actualNames.end()) {
                continue;
            }
            lines.insert(std::vector<std::string> {std::to_string(stmt2)});
        }
        resultTable->replace(new ResultTable(synonyms, lines));
        return;
    }
    if (arg1.argumentType == Argument::WILDCARD) {
        // WILDCARD, WILDCARD
        if (arg2.argumentType == Argument::WILDCARD) {
            std::unordered_set<Procedure*> procList = QPS_Interface::getProcList();
            // If there exist a procedure with more than 1 statements, next*(_, _) is always true
            for (auto proc: procList) {
                if (proc->endingStmtNo - proc->startingStmtNo > 0) {
                    resultTable->setTrueTable();
                    return;
                }
            }
            resultTable->setFalseTable();
            return;
        }
        // WILDCARD, ACTUAL_NAME
        if (arg2.argumentType == Argument::NUMBER) {
            int stmt2 = stoi(arg2.argumentName);
            CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt2);
            // next*(_, s2) is always true unless s2 is the first statement in the procedure
            if (!cfgHeadPtr->isFirstStatementInCFG(stmt2)) {
                resultTable->setTrueTable();
            } else {
                std::unordered_set<std::string> whiles = QPS_Interface::getAllEntity(new Argument("", Argument::WHILE_SYNONYM));
                if (whiles.find(std::to_string(stmt2)) != whiles.end()) {
                    resultTable->setTrueTable();
                } else {
                    resultTable->setFalseTable();
                }
            }
            return;
        }
        // WILDCARD, SYNONYM
        std::unordered_set<Procedure*> procList = QPS_Interface::getProcList();
        std::vector<std::string> synonyms = {arg2.argumentName};
        std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
        std::unordered_set<std::string> actualNames = QPS_Interface::getAllEntity(&arg2);
        for (auto proc : procList) {
            CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(proc->startingStmtNo);
            // next*(_, s2) is always true unless s2 is the first statement in the procedure
            for (int stmt2 = proc->startingStmtNo; stmt2 <= proc->endingStmtNo; stmt2++) {
                if (actualNames.find(std::to_string(stmt2)) == actualNames.end()) {
                    continue;
                }
                if (!cfgHeadPtr->isFirstStatementInCFG(stmt2)) {
                    lines.insert(std::vector<std::string> {std::to_string(stmt2)});
                } else {
                    std::unordered_set<std::string> whiles = QPS_Interface::getAllEntity(new Argument("", Argument::WHILE_SYNONYM));
                    if (whiles.find(std::to_string(stmt2)) != whiles.end()) {
                        lines.insert(std::vector<std::string> {std::to_string(stmt2)});
                    }
                }
            }
        }
        resultTable->replace(new ResultTable(synonyms, lines));
        return;
    }

    std::unordered_set<Procedure*> procList = QPS_Interface::getProcList();
    std::vector<std::string> synonyms = {arg1.argumentName};
    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
    std::unordered_set<std::string> actualNames = QPS_Interface::getAllEntity(&arg1);
    // SYNONYM, WILDCARD
    if (arg2.argumentType == Argument::WILDCARD) {
        for (auto proc : procList) {
            for (int i = proc->startingStmtNo; i <= proc->endingStmtNo; i++) {
                if (actualNames.find(std::to_string(i)) == actualNames.end()) {
                    continue;
                }
                std::unordered_set<STMT_NUM> nextStarSet = QPS_Interface::getNextStar(i);
                if (!nextStarSet.empty()) {
                    lines.insert(std::vector<std::string> {std::to_string(i)});
                }
            }
        }
        resultTable->replace(new ResultTable(synonyms, lines));
        return;
    }
    // SYNONYM, ACTUAL_NAME
    if (arg2.argumentType == Argument::NUMBER) {
        int stmt2 = stoi(arg2.argumentName);
        Procedure* proc = QPS_Interface::getProcByStmt(stmt2);
        int startingStmtNo = proc->startingStmtNo;
        int endingStmtNo = proc->endingStmtNo;
        for (int stmt1 = startingStmtNo; stmt1 <= endingStmtNo; stmt1++) {
            if (actualNames.find(std::to_string(stmt1)) == actualNames.end()) {
                continue;
            }
            std::unordered_set<STMT_NUM> nextStarSet = QPS_Interface::getNextStar(stmt1);
            if (nextStarSet.find(stmt2) != nextStarSet.end()) {
                lines.insert(std::vector<std::string> {std::to_string(stmt1)});
            }
        }
        resultTable->replace(new ResultTable(synonyms, lines));
        return;
    }
    // SYNONYM, SYNONYM
    synonyms.push_back(arg2.argumentName);
    std::unordered_set<std::string> actualNames2 = QPS_Interface::getAllEntity(&arg2);
    for (auto proc : procList) {
        for (int stmt1 = proc->startingStmtNo; stmt1 <= proc->endingStmtNo; stmt1++) {
            if (actualNames.find(std::to_string(stmt1)) == actualNames.end()) {
                continue;
            }
            std::unordered_set<STMT_NUM> nextStarSet = QPS_Interface::getNextStar(stmt1);
            for (auto stmt2 : nextStarSet) {
                if (actualNames2.find(std::to_string(stmt2)) == actualNames2.end()) {
                    continue;
                }
                lines.insert(std::vector<std::string> {std::to_string(stmt1), std::to_string(stmt2)});
            }
        }
    }
    resultTable->replace(new ResultTable(synonyms, lines));
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
    std::unordered_set<std::string> a1;
    std::unordered_set<std::string> a2;
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
            if (a1.find(r[0]) != a1.end()
            && a2.find(r[1]) != a2.end()) {
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
        } else if (isArg1Synonym && a1.find(r[0]) != a1.end() ) {
            tableRow.push_back(r[0]);
            filteredResult.insert(tableRow);
        } else if (isArg2Synonym && a2.find(r[1]) != a2.end()) {
            tableRow.push_back(r[1]);
            filteredResult.insert(tableRow);
        }

    }

    ResultTable* r = new ResultTable(synonyms, filteredResult);
    return r;
}

bool RelationClauseEvaluator::validateAffectsParameter(QPS::ResultTable *resultTable) {
    Argument assignArgument = {"", Argument::ASSIGN_SYNONYM};
    std::unordered_set<std::string> assigns = QPS_Interface::getAllEntity(&assignArgument);
    Argument arg1 = this->relationClause->getFirstArgument();
    Argument arg2 = this->relationClause->getSecondArgument();
    // ensure both synonyms are assigns
    if (arg1.argumentType == Argument::NUMBER) {
        if (assigns.find(arg1.argumentName) == assigns.end()) {
            resultTable->setFalseTable();
            return false;
        }
    }
    if (arg2.argumentType == Argument::NUMBER) {
        if (assigns.find(arg2.argumentName) == assigns.end()) {
            resultTable->setFalseTable();
            return false;
        }
    }
    if (Argument::isSynonym(arg1.argumentType) && arg1.argumentType != Argument::ASSIGN_SYNONYM
    && arg1.argumentType != Argument::STMT_SYNONYM) {
        resultTable->setFalseTable();
        return false;
    }
    if (Argument::isSynonym(arg2.argumentType) && arg2.argumentType != Argument::ASSIGN_SYNONYM
    && arg2.argumentType != Argument::STMT_SYNONYM) {
        resultTable->setFalseTable();
        return false;
    }
    return true;
}
