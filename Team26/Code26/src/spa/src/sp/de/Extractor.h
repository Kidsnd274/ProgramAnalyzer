#ifndef SPA_SP_DE_EXTRACTOR_H
#define SPA_SP_DE_EXTRACTOR_H
#include <stack>
#include <string>
#include "util/ast/IfNode.h"
#include "util/ast/AssignNode.h"
#include "util/ast/WhileNode.h"
#include "util/ast/ReadNode.h"
#include "util/ast/PrintNode.h"
#include "util/ast/CallNode.h"
#include "util/ast/ProcedureNode.h"
#include "pkb/PKBInterface.h"
class Extractor {
private:
    std::stack<int> callStack;
    std::string procName;
public:
    PKBInterface* pkb;
    Extractor(PKBInterface *pkb) {
        this->pkb = pkb;
    }
    virtual ~Extractor() = default;

    std::string getProcedureName() {
        return procName;
    }

    void setProcedureName(std::string name) {
        procName = name;
    }
    void setStack(std::stack<int> &s) {
        callStack = s;
    }

    void pushToStack(int s) {
        callStack.push(s);
    }

    int popFromStack() {
        int val = callStack.top();
        callStack.pop();
        return val;
    }

    std::vector<int> getAllItemsInStack() {
        std::stack<int> temp;
        vector<int> ans;
        while(!callStack.empty()) {
            int t = popFromStack();
            ans.push_back(t);
            temp.push(t);
        }
        while(!temp.empty()) {
            pushToStack(temp.top());
            temp.pop();
        }
        return ans;
    }

    virtual void extractFromProcedure(std::shared_ptr<ProcedureNode> ptr) = 0;
    virtual void extractFromIf(std::shared_ptr<IfNode> ptr) = 0;
    virtual void extractFromWhile(std::shared_ptr<WhileNode> ptr) = 0;
    virtual void extractFromRead(std::shared_ptr<ReadNode> ptr) = 0;
    virtual void extractFromPrint(std::shared_ptr<PrintNode> ptr) = 0;
    virtual void extractFromAssign(std::shared_ptr<AssignNode> ptr) = 0;

    //Does nothing for Milestone 1
    void extractFromCall(std::shared_ptr<CallNode> ptr) {}
};
#endif