#include "PKBStub.h"
#include <unordered_map>

namespace QPSTests{
    unordered_map<std::string,std::string> relationshipMap = relationshipMap::create_map();
    bool PKBStub::existRelation(QPS::RelationStruct relation){
        relationshipMap.find(relation.arg1.nameOfArgument);
        std::unordered_map<std::string, std::string>::const_iterator got = relationshipMap.find(relation.arg1.nameOfArgument);
        if (got != relationshipMap.end() && got->second == relation.arg2.nameOfArgument) {
            return true;
        }
    }
}
