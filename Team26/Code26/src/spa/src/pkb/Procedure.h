//
// Created by QMS on 4/9/2022.
//

#ifndef SPA_PROCEDURE_H
#define SPA_PROCEDURE_H

#include <stdio.h>
#include <string>
#include "Statement.h"

using namespace std;

//class Statement;

class Procedure {
public:
    string name;
    Statement startingStmt;
    Statement endingStmt;
};

#endif //SPA_PROCEDURE_H
