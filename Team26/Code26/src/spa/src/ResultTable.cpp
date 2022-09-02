#include "ResultTable.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <iostream>


namespace pql {
    ResultTable::ResultTable(const std::vector<std::string>& sNames, const std::unordered_set<std::vector<std::string>, StringVectorHash >& entries) {
        colNum = 0;
        for (const std::string& sName: sNames) {
            if (isSynonymPresent(sName)) {
                suspendExecution("ResultTable: Try to insert duplicate synonym name to the table.");
            }
            synonymColRef[sName] = colNum;
            colNum++;
        }
        for (const std::vector<std::string>& entry: entries) {
            if (entry.size() != colNum) {
                suspendExecution("ResultTable: entry inserted to the table is of incompatible length.");
            }
            table.push_back(entry);
        }
        rowNum = entries.size();
        isInitialized = true;
    }


    bool ResultTable::deleteColFromTable(const std::string &sName) {
        if (!isSynonymPresent(sName)) {
            return false;
        }
        int pos = synonymColRef.at(sName);
        synonymColRef.erase(sName);
        for (auto& synonym: synonymColRef) {
            if (synonym.second > pos) {
                synonym.second --;
            }
        }
        for (auto& entry: table) {
            entry.erase(entry.begin() + pos);
        }
        colNum--;
        return true;
    }

    void ResultTable::deleteRowFromTable(const int row) {
        if (row >= table.size()) {
            suspendExecution("ResultTable: row not found.");
        }
        table.erase(table.begin() + row);
    }

    bool ResultTable::getSynonymValue(const std::string &sName, std::vector<std::string>& values) {
        if (!isSynonymPresent(sName)) {
            return false;
        }
        values.clear();
        int pos = synonymColRef.at(sName);
        for (const auto& entry: table) {
            values.push_back(entry[pos]);
        }
        return true;
    }

    bool ResultTable::getSynonymsValues(const std::vector<std::string>& sNames, std::unordered_set<std::vector<std::string>, StringVectorHash>& values) {
        std::vector<int> positions;
        for (const auto& sName: sNames) {
            if (!isSynonymPresent(sName)) {
                return false;
            } else {
                positions.push_back(synonymColRef.at(sName));
            }
        }
        values.clear();
        for (auto& entry: table) {
            std::vector<std::string> returnValue;
            for (int i: positions) {
                returnValue.push_back(entry[i]);
            }
            values.insert(returnValue);
        }
        return true;
    }

    void ResultTable::printTable() {
        std::cout << "Printing Table ... \n";
        std::string header = "| ";
        std::string content;
        std::vector<std::string> sortedName(5, "");
        for (auto& name: synonymColRef) {
            int i = name.second;
            std::string p = name.first;
            auto it = sortedName.begin() + i;
            sortedName.insert(it, p);
        }
        for (auto& sName: sortedName) {
            if (sName != "") {
                header += sName + " | ";
            }
        }
        header += "\n";
        std::cout << header;
        for (auto& entry: table) {
            std::stringstream ss;
            ss << "| ";
            for (auto& str: entry) {
                ss << str;
                ss << " | ";
            }
            std::cout << ss.str() << std::endl;
        }
    }

    void ResultTable::printStringVector(std::vector<std::string> v) {
        std::cout << "Printing vector ... \n";
        std::string s = "| ";
        for (auto& str: v) {
            s += str + " | ";
        }
        std::cout << s + "\n";
    }

    bool ResultTable::isSynonymPresent(const std::string &sName) {
        return synonymColRef.find(sName) != synonymColRef.end();
    }

    void suspendExecution(const std::string& errorMsg) {
        throw errorMsg;
    }
}

int main() {
    //std::cout << "test";
    std::vector<std::string> v = { "A", "B", "C" };
    std::vector<std::string> v1 = { "A", "B", "C" };
    std::vector<std::string> v2 = { "A", "B", "D" };
    std::vector<std::string> v3 = { "A", "B", "E" };
    std::unordered_set<std::vector<std::string>, pql::StringVectorHash> entries;
    entries.insert(v1);
    entries.insert(v2);
    entries.insert(v3);
    pql::ResultTable rt(v, entries);
    rt.printTable();
    rt.deleteColFromTable("A");
    rt.printTable();
//    rt.deleteRowFromTable(0);
//    rt.printTable();
//    rt.deleteColFromTable("C");
//    rt.printTable();
    std::vector<std::string> values;
    bool absent = rt.getSynonymValue("A", values);
    bool present = rt.getSynonymValue("B", values);
    rt.printStringVector(values);
    std::vector<std::string> names = {"B", "C"};
    std::vector<std::string> names2 = {"A", "B", "C"};
    std::vector<std::string> names3 = {"C", "B"};
    std::unordered_set<std::vector<std::string>, pql::StringVectorHash> values2;
    bool absent2 = rt.getSynonymsValues(names2, values2);
    bool present2 = rt.getSynonymsValues(names, values2);
    for (auto& pair: values2) {
        rt.printStringVector(pair);
    }
    bool present3 = rt.getSynonymsValues(names3, values2);
    for (auto& pair: values2) {
        rt.printStringVector(pair);
    }
    return 0;
}