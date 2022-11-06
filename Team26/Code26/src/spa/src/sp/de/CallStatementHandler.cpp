#include "CallStatementHandler.h"

void CallStatementHandler::checkIfProcedureExist(std::string& procedureCalled) {
    if (nameToIndex.find(procedureCalled) == nameToIndex.end()) {
        throw SemanticErrorException("Call to non-existent procedure " + procedureCalled);
    }
}

void CallStatementHandler::checkCyclicProcedureCall(std::string& procedureCalled) {
    if (nameToIndex[procedureCalled].second == 1) {
        throw SemanticErrorException("Cyclic procedure calls in " + procedureCalled);
    }
}

void CallStatementHandler::addToPkb(CallStruct& cs, PKBInterface *pkb, std::string& procedureName) {
    // now add all modified and used variable to procedure and parent*
    std::unordered_set<std::string> modified = pkb->getAllVariablesModified(cs.getProcedureCalled());
    std::unordered_set<std::string> used = pkb->getAllVariablesUsed(cs.getProcedureCalled());
    std::unordered_set<int> parentStar = pkb->getParentStar(cs.getStatementNumber());
    std::unordered_set<std::string> callStar = pkb->getCallStar(cs.getProcedureCalled());

    for (auto &var : modified) {
        pkb->addModifies(procedureName, var);
        pkb->addModifies(cs.getStatementNumber(), var);
        for (auto p : parentStar) {
            pkb->addModifies(p, var);
        }
    }

    for (auto &var : used) {
        pkb->addUses(procedureName, var);
        pkb->addUses(cs.getStatementNumber(), var);
        for (auto p : parentStar) {
            pkb->addUses(p, var);
        }
    }

    // handle calls and callstar
    for (auto &proc : callStar) {
        pkb->addCallStar(procedureName, proc);
    }

    pkb->addCallStar(procedureName, cs.getProcedureCalled());
    pkb->addCall(procedureName, cs.getProcedureCalled());
}

void CallStatementHandler::handleCalls(PKBInterface *pkb) {
    for (int i = 0; i < callList.size(); ++i) {
        dfs(i, pkb);
    }
}

void CallStatementHandler::dfs(int i, PKBInterface *pkb) {
    // if procedure has been processed can return
    if (nameToIndex[indexToName[i]].second == 2) return;

    // if there are no call statements then can return
    if (callList[i].size() == 0) {
        // mark procedure as done
        nameToIndex[indexToName[i]].second = 2;
        return;
    }

    nameToIndex[indexToName[i]].second = 1;

    for (int j = 0; j < callList[i].size(); ++j) {
        std::string procedureCalled = callList[i][j].getProcedureCalled();

        checkIfProcedureExist(procedureCalled);
        checkCyclicProcedureCall(procedureCalled);

        if (nameToIndex[procedureCalled].second == 0) {
            dfs(nameToIndex[procedureCalled].first, pkb);
        }

        addToPkb(callList[i][j], pkb, indexToName[i]);
    }

    nameToIndex[indexToName[i]].second = 2;
}
