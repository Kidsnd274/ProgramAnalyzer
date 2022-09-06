#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>
#include <fstream>

// include your other headers here
#include "AbstractWrapper.h"
#include "sp/SourceProcessor.h"
#include "pkb/PKBInterface.h"

class TestWrapper : public AbstractWrapper {public:
    PKBInterface *pkbInterface;
    // default constructor
    TestWrapper();
  
    // destructor
    ~TestWrapper();
  
    // method for parsing the SIMPLE source
    virtual void parse(std::string filename);
  
    // method for evaluating a query
    virtual void evaluate(std::string query, std::list<std::string>& results);
};

#endif
