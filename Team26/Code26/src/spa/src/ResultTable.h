#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>


namespace pql {
    /**
 * The hashing method of a pair of strings
 */
    struct StringVectorHash {
        size_t operator()(const std::vector<std::string>& s) const {
            std::hash<std::string> h;
            size_t seed = 0;
            for (auto& i : s) {
                seed ^= h(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            }
            return seed;
        }
    };
    class ResultTable {
    private:
        bool isInitialized;
        int colNum, rowNum;
        std::unordered_map<std::string, int> synonymColRef;
        std::vector <std::vector<std::string> > table;
    public:
        ResultTable(){
            isInitialized = false;
            colNum = 0;
            rowNum = 0;
        }
        ResultTable(const std::vector<std::string>& sNames, const std::unordered_set<std::vector<std::string>, StringVectorHash>& entries);
        bool deleteColFromTable(const std::string& sName);
        void deleteRowFromTable(const int row);
        bool isSynonymPresent(const std::string& sName);
        bool getSynonymValue(const std::string& sName, std::vector<std::string>& values);
        bool getSynonymsValues(const std::vector<std::string>& sNames, std::unordered_set<std::vector<std::string>, StringVectorHash>& values);
        //for debug purpose
        void printTable();
        void printStringVector(std::vector<std::string> v);
    };

    void suspendExecution(const std::string& errorMsg);
}