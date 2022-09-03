//
// Created by QMS on 30/8/2022.
//

#ifndef SPA_VARIABLETABLE_H
#define SPA_VARIABLETABLE_H

#pragma once
#include <string>

using namespace std;

class VariableTable {
private:
    unordered_set<string> varNames;

public:
    void insertVar(String var);
    // Var getVar(string varName);
    int getSize();
};

#endif //SPA_VARIABLETABLE_H
