#include "DesignExtractor.h"

bool DesignExtractor::doesProcedureAlreadyExist(std::string name) {
    if(nameToIndex.find(name) != nameToIndex.end()) {
        return true;
    } else {
        return false;
    }
}

void DesignExtractor::addProcedure(std::string name) {
    if(doesProcedureAlreadyExist(name)) {
        throw SemanticErrorException("Duplicate procedure name: " + name);
    }

    nameToIndex[name] = {callList.size(), 0};
    indexToName[callList.size()] = name;

    std::vector<CallStruct> v;
    this->callList.push_back(v);
}

void DesignExtractor::addCallStatement(CallStruct &c) {
    if(callList.size() > 0 && indexToName[callList.size()-1] == c.getProcedureCalled()) {
        throw SemanticErrorException("Recursive call to procedure " + c.getProcedureCalled());
    }

    this->callList.back().push_back(c);
}

void DesignExtractor::extract(std::vector<std::shared_ptr<ProcedureNode>> procedures) {
    for(auto p : procedures) {
        for (auto &e: extractorList) {
            travers_pointer_cast<IfNode>(ptr);
        e->extractFromIf(t);

        std::vector<std::shared_ptr<StatementNode>> stmtList = t->getIfStatementList();
        for(int i = 0; i < stmtList.size(); ++i) {
            traverse(stmtList[i], e);
        }

        stmtList = t->getElseStatementList();
        for(int i = 0; i < stmtList.size(); ++i) {
            traverse(stmtList[i], e);
        }

        e->popFromStack();
    } else if (ptr->getStatementType() == statementType::WHILE) {
        shared_ptr<WhileNode> t = std::static_pointer_cast<WhileNode>(ptr);
        e->extractFromWhile(t);

        std::vector<std::shared_ptr<StatementNode>> stmtList = t->getStatementList();
        for(int i = 0; i < stmtList.size(); ++i) {
            traverse(stmtList[i], e);
        }

        e->popFromStack();
    } else if (ptr->getStatementType() == statementType::ASSIGN) {
        e->extractFromAssign(std::static_pointer_cast<AssignNode>(ptr));
    } else if (ptr->getStatementType() == statementType::READ) {
        e->extractFromRead(std::static_pointer_cast<ReadNode>(ptr));
    } else if (ptr->getStatementType() == statementType::PRINT) {
        e->extractFromPrint(std::static_pointer_cast<PrintNode>(ptr));
    } else {
        e->extractFromCall(std::static_pointer_cast<CallNode>(ptr));
    }

}