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
    PKBInterface pkb;
    Extractor(PKBInterface &pkb) {
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
        callStack.pop();
    }

    virtual void extractFromIf(std::shared_ptr<IfNode> ptr) = 0;
    virtual void extractFromWhile(std::shared_ptr<WhileNode> ptr) = 0;
    virtual void extractFromRead(std::shared_ptr<ReadNode> ptr) = 0;
    virtual void extractFromPrint(std::shared_ptr<PrintNode> ptr) = 0;
    virtual void extractFromAssign(std::shared_ptr<AssignNode> ptr) = 0;

    //Does nothing for Milestone 1
    void extractFromCall(std::shared_ptr<CallNode> ptr) {}
};
