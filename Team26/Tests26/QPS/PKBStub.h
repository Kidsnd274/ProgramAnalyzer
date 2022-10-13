#ifndef SPA_PKBSTUB_H
#define SPA_PKBSTUB_H
#include "../../Code26/src/spa/src/qps/QueryProcessorTypes.h"
using namespace std;
#include <unordered_map>

namespace QPSTests{
    struct relationshipMap{
        static unordered_map<std::string,std::string> create_map()
        {
            unordered_map<std::string,std::string> m = {
            {"3",  "x"},
            {"5",  "x"},
            {"6",  "y"},
            {"7",  "z"},
            {"9", "x"},
            {"10", "z"},
            {"11", "z"}};

            return m;
        }
        static unordered_map<int,std::string> myMap;
    };

    class PKBStub {


};


#endif //SPA_PKBSTUB_H
