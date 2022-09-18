#ifndef SPA_UTIL_AST_STATEMENTNODE_H
#define SPA_UTIL_AST_STATEMENTNODE_H

enum statementType {
    IF,
    WHILE,
    CALL,
    READ,
    PRINT,
    ASSIGN
};

class StatementNode {
private:
    int statementNumber;
    statementType stmtType;
public:
    StatementNode(int statementNumber, statementType stmtType) {
        this->statementNumber = statementNumber;
        this->stmtType = stmtType;
    }

    int getStatementNumber();
    int getStatementType();
};
#endif
