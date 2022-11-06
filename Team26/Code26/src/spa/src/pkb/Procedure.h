#ifndef SPA_PROCEDURE_H
#define SPA_PROCEDURE_H

#include <memory>
#include <string>
#include <utility>
#include "util/cfg/CFGHead.h"

class Procedure {
public:
    std::string name;
    STMT_NUM startingStmtNo;
    STMT_NUM endingStmtNo;
    std::shared_ptr<CFGHead> cfg;
};

#endif  // SPA_PROCEDURE_H
