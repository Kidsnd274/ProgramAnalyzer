//
// Created by QMS on 4/9/2022.
//

#ifndef SPA_PROCEDURE_H
#define SPA_PROCEDURE_H

#include <stdio.h>
#include <string>
#include "util/cfg/CFGHead.h"

using namespace std;

class Procedure {
public:
    string name;
    int startingStmtNo;
    int endingStmtNo;
    std::shared_ptr<CFGHead> cfg;
};

#endif //SPA_PROCEDURE_H
