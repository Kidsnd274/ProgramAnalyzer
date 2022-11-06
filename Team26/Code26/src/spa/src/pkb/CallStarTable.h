#ifndef SPA_CALLSTARTABLE_H
#define SPA_CALLSTARTABLE_H

#include <algorithm>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>

class CallStarTable {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> callStarList;
public:
    void insertCallStar(std::string procedureName, std::string procedureCalled);
    bool existCallStar(std::string procedureName, std::string procedureCalled);
    std::unordered_set<std::string> getProcsStarCalled(std::string procedureName);
    std::unordered_map<std::string, std::unordered_set<std::string>> getAllCallStars();
    void clear();
};

#endif  // SPA_CALLSTARTABLE_H
