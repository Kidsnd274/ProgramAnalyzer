//
// Created by Samuel Tee on 26/8/2022.
//
#include <iostream>
#include "StringTest.h"

using namespace std;

int main() {
    cout << "Hello World!";
    string test = "This is a   test   to se if delimiter works!";
    vector<string> output = StringTest::delimitBySpace(test);
    for (int i = 0; i < output.size(); ++i) {
        cout << output[i];
    }
    return 0;
}