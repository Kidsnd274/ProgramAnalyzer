//
// Created by Samuel Tee on 26/8/2022.
//
#include "StringTest.h"

using namespace std;

std::vector<std::string> StringTest::delimitBySpace(std::string source) {
    std::stringstream stream(source);
    std::vector<std::string> result;
    std::string rawInput;

    while(std::getline(stream, rawInput, ' ')) {
        if(rawInput == "") continue;
        result.push_back(rawInput);
    }

    return result;
}