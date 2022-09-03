#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "QueryProcessorTypes.h"

using namespace std;
typedef short PROC;

class PKBQueryInterface {
public:
	//static bool getModifies (/* Stmt stmtlineno, Var var */);
    vector<string> getAllEntity(EntityType);
};