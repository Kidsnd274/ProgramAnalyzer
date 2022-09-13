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
            {"10", "x"},
            {"11", "z"},
            {"14", "z"}};

            return m;
        }
        static unordered_map<int,std::string> myMap;
    };

    class PKBStub {
    public:
        static bool existRelation(QPS::RelationStruct relation);
    };

};


#endif //SPA_PKBSTUB_H
