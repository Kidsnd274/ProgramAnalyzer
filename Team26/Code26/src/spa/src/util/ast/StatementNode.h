#ifndef SPA_UTIL_AST_STATEMENTNODE_H
#define SPA_UTIL_AST_STATEMENTNODE_H

class StatementNode {
private:
    int statementNumber;
public:
    StatementNode(int statementNumber) {
        this->statementNumber = statementNumber;
    }

    int getStatementNumber();
};
#endif
