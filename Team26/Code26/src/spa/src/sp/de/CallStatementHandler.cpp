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
    std::unordered_set<std::string> modified = pkb->getAllUsedOrCalled(RelationType::MODIFIES_S, cs.getProcedureCalled());
    std::unordered_set<std::string> used = pkb->getAllUsedOrCalled(RelationType::USES_S, cs.getProcedureCalled());
    std::unordered_set<int> parentStar = pkb->getParentStar(cs.getStatementNumber());
    std::unordered_set<std::string> callStar = pkb->getAllUsedOrCalled(RelationType::CALLS_T, cs.getProcedureCalled());

    for (auto &var : modified) {
        pkb->addRelation(RelationType::MODIFIES_S, procedureName, var);
        pkb->addRelation(RelationType::MODIFIES_S, cs.getStatementNumber(), var);
        for (auto p : parentStar) {
            pkb->addRelation(RelationType::MODIFIES_S, p, var);
        }
    }

    for (auto &var : used) {
        pkb->addRelation(RelationType::USES_S, procedureName, var);
        pkb->addRelation(RelationType::USES_S, cs.getStatementNumber(), var);
        for (auto p : parentStar) {
            pkb->addRelation(RelationType::USES_S, p, var);
        }
    }

    // handle calls and callstar
    for (auto &proc : callStar) {
        pkb->addRelation(RelationType::CALLS_T, procedureName, proc);
    }

    pkb->addRelation(RelationType::CALLS_T, procedureName, cs.getProcedureCalled());
    pkb->addRelation(RelationType::CALLS, procedureName, cs.getProcedureCalled());
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
