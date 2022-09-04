//
// Created by QMS on 4/9/2022.
//

#ifndef SPA_STATEMENT_H
#define SPA_STATEMENT_H

#include <stdio.h>
#include <string>

using namespace std;

enum StmtType {
    READ,
    ASSIGN,
    WHILE,
    IF,
    PRINT,
    CALL
};

class Statement {
public:
    StmtType type;
    int lineNumber;
};


#endif //SPA_STATEMENT_H
