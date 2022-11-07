#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H

#include "Argument.h"

class Clause {
public:
    virtual bool isValid();

    virtual Argument getFirstArgument();
    virtual Argument getSecondArgument();
};


#endif  // SPA_CLAUSE_H
