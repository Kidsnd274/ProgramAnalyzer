#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "CallStruct.h"
#include "pkb/PKBInterface.h"
#include "sp/SemanticErrorException.h"

#ifndef SPA_CALLSTATEMENTHANDLER_H
#define SPA_CALLSTATEMENTHANDLER_H

class CallStatementHandler {
private:
    std::vector<std::vector<CallStruct>> callList;
    std::unordered_map<std::string, std::pair<int, int>> nameToIndex;
    std::unordered_map<int, std::string> indexToName;

public:
    CallStatementHandler(std::vector<std::vector<CallStruct>> &cl,
                         std::unordered_map<std::string, std::pair<int, int>> &ni,
                         std::unordered_map<int, std::string> &in) {
        callList = cl;
        nameToIndex = ni;
        indexToName = in;
    }

    void handleCalls(PKBInterface *pkb);
    void dfs(int i, PKBInterface *pkb);
};


#endif  // SPA_CALLSTATEMENTHANDLER_H
