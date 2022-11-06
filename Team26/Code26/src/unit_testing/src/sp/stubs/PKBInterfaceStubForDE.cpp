#include "PKBInterfaceStubForDE.h"

void PKBInterfaceStubForDE::addFollows(int stmt1Number, int stmt2Number) {
    this->followsMap[stmt1Number] = stmt2Number;
}

void PKBInterfaceStubForDE::addParent(int parentStmtNumber, int stmtNumber) {
    this->parentMapIntInt[stmtNumber] = parentStmtNumber;
}

void PKBInterfaceStubForDE::addParentStar(int parentStmtNumber, int stmtNumber) {
    this->parentStarMapIntInt.insert({parentStmtNumber, stmtNumber});
}

void PKBInterfaceStubForDE::addModifies(int stmtNumber, std::string varModified) {
    auto newPair = std::pair<int, std::string>(stmtNumber, varModified);
    this->modifiesMapIntString.insert(newPair);
}

void PKBInterfaceStubForDE::addModifies(std::string procedureName, std::string varModified) {
    auto newPair = std::pair<std::string, std::string>(procedureName, varModified);
    this->modifiesMapStringString.insert(newPair);
}

void PKBInterfaceStubForDE::addUses(int stmtNumber, std::string variableUsed) {
    auto newPair = std::pair<int, std::string>(stmtNumber, variableUsed);
    this->usesMapIntString.insert(newPair);
}

void PKBInterfaceStubForDE::addUses(std::string procedureName, std::string variableUsed) {
    auto newPair = std::pair<std::string, std::string>(procedureName, variableUsed);
    this->usesMapStringString.insert(newPair);
}

void PKBInterfaceStubForDE::addReadStatement(int statementNumber, int stmtListNum) {
    this->statements.insert({statementNumber, stmtListNum});
    statementTypeMap.insert({statementNumber, StmtType::READ});
}

void PKBInterfaceStubForDE::addAssignStatement(int statementNumber, int stmtListNum, std::shared_ptr<TNode> ptr) {
    this->statements.insert({statementNumber, stmtListNum});
    statementTypeMap.insert({statementNumber, StmtType::ASSIGN});
}

void PKBInterfaceStubForDE::addWhileStatement(int statementNumber, int stmtListNum) {
    this->statements.insert({statementNumber, stmtListNum});
    statementTypeMap.insert({statementNumber, StmtType::WHILE});
}

void PKBInterfaceStubForDE::addIfStatement(int statementNumber, int stmtListNum) {
    this->statements.insert({statementNumber, stmtListNum});
    statementTypeMap.insert({statementNumber, StmtType::IF});
}

void PKBInterfaceStubForDE::addPrintStatement(int statementNumber, int stmtListNum) {
    this->statements.insert({statementNumber, stmtListNum});
    statementTypeMap.insert({statementNumber, StmtType::PRINT});
}

void PKBInterfaceStubForDE::addCallStatement(int statementNumber, int statementListNumber, std::string calleeProcName) {
    this->statements.insert({statementNumber, statementListNumber});
    statementTypeMap.insert({statementNumber, StmtType::CALL});
}

void PKBInterfaceStubForDE::addCall(std::string procedureName, std::string procedureCalled) {
    this->callMapStringString.insert({ procedureName, procedureCalled });
}

void PKBInterfaceStubForDE::addCallStar(std::string procedureName, std::string procedureCalled) {
    this->callStarMapStringString.insert({ procedureName, procedureCalled });
}

std::unordered_set<std::string> PKBInterfaceStubForDE::getAllVariablesModified(std::string procedureName) {
    std::unordered_set<std::string> result;
    auto variables = this->modifiesMapStringString.equal_range(procedureName);

    for (auto it = variables.first; it != variables.second; ++it) {
        result.insert(it->second);
    }
    return result;
}

std::unordered_set<std::string> PKBInterfaceStubForDE::getAllVariablesUsed(std::string procedureName) {
    std::unordered_set<std::string> result;
    auto variables = this->usesMapStringString.equal_range(procedureName);

    for (auto it = variables.first; it != variables.second; ++it) {
        result.insert(it->second);
    }
    return result;
}

std::unordered_set<int> PKBInterfaceStubForDE::getParentStar(int statementNumber) {
    std::unordered_set<int> result;
    for (auto it = this->parentStarMapIntInt.begin(); it != this->parentStarMapIntInt.end();) {
        auto const& key = it->first;
        auto variablesForKey = this->parentStarMapIntInt.equal_range(key);
        for (auto it2 = variablesForKey.first; it2 != variablesForKey.second; ++it2) {
            if (statementNumber == it->second) {
                result.insert(key);
                break;
            }
        }
        while (++it != this->parentStarMapIntInt.end() && it->first == key);
    }
    return result;
}

std::unordered_set<std::string> PKBInterfaceStubForDE::getCall(std::string procedure) {
    std::unordered_set<std::string> result;
    auto variables = this->callMapStringString.equal_range(procedure);

    for (auto it = variables.first; it != variables.second; ++it) {
        result.insert(it->second);
    }
    return result;
}

std::unordered_set<std::string> PKBInterfaceStubForDE::getCallStar(std::string procedure) {
    std::unordered_set<std::string> result;
    auto variables = this->callStarMapStringString.equal_range(procedure);

    for (auto it = variables.first; it != variables.second; ++it) {
        result.insert(it->second);
    }
    return result;
}

bool PKBInterfaceStubForDE::hasNextStar(STMT_NUM stmt) {
    return nextStarMap.find(stmt) != nextStarMap.end();
}

void PKBInterfaceStubForDE::addNextStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> nextStarSet) {
    nextStarMap[stmt] = nextStarSet;
}

bool PKBInterfaceStubForDE::isStatementContainer(STMT_NUM stmt) {
    return statementTypeMap[stmt] == StmtType::IF || statementTypeMap[stmt] == StmtType::WHILE;
}

bool PKBInterfaceStubForDE::doesStatementModify(STMT_NUM stmt, std::string varModified) {
    for(auto &[f,s] : modifiesMapIntString) {
        if(f == stmt && s == varModified) {
            return true;
        }
    }

    return false;
}

bool PKBInterfaceStubForDE::hasAffects(STMT_NUM stmt) {
    return affectsMap.find(stmt) != affectsMap.end();
}

std::string PKBInterfaceStubForDE::getModifiedVariable(STMT_NUM stmt) {
    for(auto &[f,s] : modifiesMapIntString) {
        if(f == stmt) {
            return s;
        }
    }

    return " ";
}

bool PKBInterfaceStubForDE::isStatementAssign(STMT_NUM stmt) {
    return statementTypeMap[stmt] == StmtType::ASSIGN;
}

bool PKBInterfaceStubForDE::doesStatementUse(STMT_NUM stmt, std::string varUsed) {
    for(auto &[f,s] : usesMapIntString) {
        if(f == stmt && s == varUsed) {
            return true;
        }
    }

    return false;
}

void PKBInterfaceStubForDE::addAffects(STMT_NUM stmt, STMT_NUM affectedStmt) {
    affectsMap[stmt].insert(affectedStmt);
}

void PKBInterfaceStubForDE::addProcedure(std::string name, int startingStmtNo, int endingStmtNo, std::shared_ptr<CFGHead> cfg) {
    procedureToCFG[name] = cfg;
    procToStmtNums[name] = {startingStmtNo, endingStmtNo};
}

std::string PKBInterfaceStubForDE::getProcedureNameOf(CFGHeadPtr cfg) {
    for(auto &[f, c] : procedureToCFG) {
        if(c == cfg) {
            return f;
        }
    }
    return "";
}

bool PKBInterfaceStubForDE::hasAffectsStar(STMT_NUM stmt) {
    return affectsStarMap.find(stmt) != affectsStarMap.end();
}

void PKBInterfaceStubForDE::addAffectsStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> affectsStarSet) {
    affectsStarMap[stmt] = affectsStarSet;
}

std::unordered_set<STMT_NUM> PKBInterfaceStubForDE::getAllAssignFromProcedure(std::string procName) {
    std::pair<STMT_NUM, STMT_NUM> toFrom = procToStmtNums[procName];
    std::unordered_set<STMT_NUM> ans;
    for(int i = toFrom.first; i <= toFrom.second; ++i) {
        if(statementTypeMap[i] == StmtType::ASSIGN) {
            ans.insert(i);
        }
    }

    return ans;
}

std::unordered_set<STMT_NUM> PKBInterfaceStubForDE::getAffects(STMT_NUM stmt) {
    return affectsMap[stmt];
}