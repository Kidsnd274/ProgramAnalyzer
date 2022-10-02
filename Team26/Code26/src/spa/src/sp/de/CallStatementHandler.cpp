#include "CallStatementHandler.h"

void CallStatementHandler::handleCalls(PKBInterface *pkb) {
    for(int i = 0; i < callList.size(); ++i) {
        dfs(i, pkb);
    }
}

void CallStatementHandler::dfs(int i, PKBInterface *pkb) {
    //if procedure has been processed can return
    if(nameToIndex[indexToName[i]].second == 2) return;

    //if there are no call statements then can return
    if(callList[i].size() == 0) {
        //mark procedure as done
        nameToIndex[indexToName[i]].second = 2;
        return;
    }

    nameToIndex[indexToName[i]].second = 1;

    for(int j = 0; j < callList[i].size(); ++j) {
        string procedureCalled = callList[i][j].getProcedureCalled();

        if(nameToIndex.find(procedureCalled) == nameToIndex.end()) {
            throw SemanticErrorException("Call to non-existent procedure " + procedureCalled);
        }

        if (nameToIndex[procedureCalled].second == 1) {
            throw SemanticErrorException("Cyclic procedure calls in " + procedureCalled);
        }

        if(nameToIndex[procedureCalled].second == 0) {
            dfs(nameToIndex[procedureCalled].first, pkb);
        }

        //now add all modified and used variable to procedure and parent*
        std::unordered_set<std::string> modified = pkb->getAllVariablesModified(callList[i][j].getProcedureCalled());
        std::unordered_set<std::string> used = pkb->getAllVariablesUsed(callList[i][j].getProcedureCalled());
        std::unordered_set<int> parentStar = pkb->getParentStar(callList[i][j].getStatementNumber());
        //std::unordered_set<int> callStar = pkb->getCallStar(callList[i][j].getProcedureCalled());

        for(auto &var : modified) {
            pkb->addModifies(indexToName[i], var);
            for(auto p : parentStar) {
                pkb->addModifies(p, var);
            }
        }

        for(auto &var : used) {
            pkb->addUses(indexToName[i], var);
            for(auto p : parentStar) {
                pkb->addUses(p, var);
            }
        }

//        for(auto &proc : callStar) {
//            pkb->addCallStar(indexToName[i], proc);
//        }
        //pkb->addCallStar(indexToName[i], procedureCalled);
        //pkb->addCalls(indexToName[i], procedureCalled);
    }
    nameToIndex[indexToName[i]].second = 2;
    return;
}
