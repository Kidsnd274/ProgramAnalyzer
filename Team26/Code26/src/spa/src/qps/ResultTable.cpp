#include "ResultTable.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>


namespace QPS {
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
        rowNum--;
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


    bool ResultTable::isSynonymPresent(const std::string &sName) const{
        return synonymColRef.find(sName) != synonymColRef.end();
    }

    void suspendExecution(const std::string& errorMsg) {
        throw errorMsg;
    }

    void ResultTable::mergeTable(const QPS::ResultTable &otherTable) {
        if (!otherTable.isInitialized) {
            return;
        }
        if (!this->isInitialized) {
            this->colNum = otherTable.colNum;
            this->rowNum = otherTable.rowNum;
            this->synonymColRef = std::move(otherTable.synonymColRef);
            this->table = std::move(otherTable.table);
            this->isInitialized = otherTable.isInitialized;
        }
        std::vector<int> otherUniqueCols, thisUniqueCols, otherCommonCols, thisCommonCols;
        std::vector<std::string> commonSynonyms, otherUniqueSynonyms;
        this->compareTableSynonyms(otherTable, commonSynonyms, otherUniqueCols, otherCommonCols, thisCommonCols, otherUniqueSynonyms);
        //No common synonyms
        if (commonSynonyms.size() == 0) {
            mergeWithoutSameSynonym(otherTable, otherUniqueCols);
            updateSynonymColRef(otherUniqueSynonyms);
            return;
        }
        //Got common synonyms
        //Categorize values of the common synonyms into groups and then compare with the other table to be merged with
        std::unordered_map<std::vector<std::string>, std::vector<int>, StringVectorHash> resultSet;
        this->commonSynonymValueSet(thisCommonCols, resultSet);
        mergeWithSameSynonyms(resultSet, otherTable, otherUniqueCols, otherCommonCols);
        updateSynonymColRef(otherUniqueSynonyms);
        return;
    }

    void ResultTable::commonSynonymValueSet(const std::vector<int> &commonSynonymCols,
                                            std::unordered_map<std::vector<std::string>, std::vector<int>, StringVectorHash> &resultSet) {
        int rowNum = 0;
        for (auto &row: this->table) {
            std::vector<std::string> newValue;
            for (auto &col: commonSynonymCols) {
                newValue.push_back(row[col]);
            }
            if (resultSet.find(newValue) == resultSet.end()) {
                std::vector<int> v;
                resultSet[newValue] = v;
            }
            resultSet[newValue].push_back(rowNum);
            rowNum++;
        }
        return;
    }

    void ResultTable::updateSynonymColRef(const std::vector<std::string> &otherUniqueSynonyms) {
        for (auto &synonym: otherUniqueSynonyms) {
            synonymColRef[synonym] = colNum;
            colNum++;
        }
        return;
    }

    void ResultTable::mergeWithSameSynonyms(
            std::unordered_map<std::vector<std::string>, std::vector<int>, StringVectorHash> &resultSet,
            const QPS::ResultTable &otherTable, std::vector<int> &otherUniqueCols, std::vector<int> &otherCommonCols) {
        std::vector<std::vector<std::string>> newTable;
        for (auto &otherRow: otherTable.table) {
            std::vector<std::string> newValue;
            for (auto &col: otherCommonCols) {
                newValue.push_back(otherRow[col]);
            }
            if (resultSet.find(newValue) != resultSet.end()) {
                for (auto &sameValueRow: resultSet.at(newValue)) {
                    std::vector<std::string> newRow;
                    newRow.insert(newRow.end(), table[sameValueRow].begin(), table[sameValueRow].end());
                    for (auto &diffSynonymCol: otherUniqueCols) {
                        newRow.push_back(otherRow[diffSynonymCol]);
                    }
                    newTable.push_back(newRow);
                }
            }
        }
        table = std::move(newTable);
        rowNum = newTable.size();
        return;
    }

    void ResultTable::mergeWithoutSameSynonym(const QPS::ResultTable &otherTable, const std::vector<int>& otherUniqueCols) {
        std::vector<std::vector<std::string>> newTable;
        for (const auto &thisRow: table) {
            for (const auto &otherRow: otherTable.table) {
                std::vector<std::string> newRow;
                newRow.insert(newRow.end(), thisRow.begin(), thisRow.end());
                for (const auto &col: otherUniqueCols) {
                    newRow.push_back(otherRow[col]);
                }
                newTable.push_back(newRow);
            }
        }
        table = std::move(newTable);
        rowNum = newTable.size();
        return;
    }

    void ResultTable::compareTableSynonyms(const QPS::ResultTable &otherTable, std::vector<std::string> &commonSynonyms,
                                           std::vector<int> &otherUniqueCols, std::vector<int> &otherCommonCols,
                                           std::vector<int> &thisCommonCols,
                                           std::vector<std::string> &otherUniqueSynonyms) {
        for (const auto& synonym: synonymColRef) {
            if (otherTable.isSynonymPresent(synonym.first)) {
                commonSynonyms.push_back(synonym.first);
                thisCommonCols.push_back(synonym.second);
                otherCommonCols.push_back(otherTable.synonymColRef.at(synonym.first));
            }
        }
        for (auto &synonym: otherTable.synonymColRef) {
            bool otherSynonymNotPresent = std::find(commonSynonyms.begin(), commonSynonyms.end(), synonym.first) == commonSynonyms.end();
            if (otherSynonymNotPresent) {
                otherUniqueCols.push_back(synonym.second);
                otherUniqueSynonyms.push_back(synonym.first);
            }
        }
        return;
    }

    void ResultTable::deleteDuplicateRows() {
        std::unordered_set<std::string> presentRows;
        for (int row = 0; row < table.size(); row++) {
            std::string s = "";
            for (auto &entry: table[row]) {
                s += entry + "|";
            }
            if (presentRows.find(s) != presentRows.end()) {
                deleteRowFromTable(row);
            } else {
                presentRows.insert(s);
            }
        }
    }

    //The following methods are to print out a table or a vector for testing purpose.
    void ResultTable::printTable() {
        std::cout << "Printing Table ... \n";
        std::string header = "| ";
        std::string content;
        struct {
            bool operator()(std::pair<std::string, int> a, std::pair<std::string, int> b) const { return a.second < b.second; }
        } customLess;
        std::vector<std::pair<std::string, int>> sorted(synonymColRef.begin(), synonymColRef.end());
        std::sort(sorted.begin(), sorted.end(), customLess);
        for (auto& sName: sorted) {
            if (sName.first != "") {
                header += sName.first + " | ";
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

    void ResultTable::printIntVector(std::vector<int> v) {
        std::cout << "Printing vector ... \n";
        std::string s = "| ";
        for (auto& str: v) {
            s += std::to_string(str) + " | ";
        }
        std::cout << s + "\n";
    }

    void ResultTable::addColumnAndMerge(std::string nameOfSynonym, std::vector<std::string> entities) {
        this->rowNum = this->rowNum * entities.size();
        this->synonymColRef.insert(std::make_pair(nameOfSynonym, colNum));
        this->colNum++;
        std::vector<std::vector<std::string>> newTable;
        for (auto iter1 = this->table.begin(); iter1 != this->table.end(); iter1++) { // iter1: row of original table
            for (auto iter2 = entities.begin(); iter2 != entities.end(); iter2++) { // iter2: row of new column
                std::vector<std::string> newRow = *iter1;
                newRow.emplace_back(*iter2);
                newTable.emplace_back(newRow);
            }
        }
        this->table = newTable;
    }

    void ResultTable::filterRowsBySuchThatList(QPS::SUCH_THAT_LIST suchThatList) {
        std::vector<std::vector<std::string>> newTable;
        for (auto row_iter = this->table.begin(); row_iter != this->table.end(); row_iter++) {
            if (followsRelation(*row_iter, suchThatList)) {
                newTable.emplace_back(*row_iter);
            }
        }
        this->table = newTable;
    }

    bool ResultTable::followsRelation(std::vector<std::string> &row, QPS::SUCH_THAT_LIST suchThatList) {
        for (auto relation : suchThatList) {
            RelationStruct realRelation;
            realRelation.typeOfRelation = relation.typeOfRelation;
            realRelation.arg1 = {
                    relation.arg1.typeOfArgument,
                    row.at(this->synonymColRef.find(relation.arg1.nameOfArgument)->second)
            };

            if (PKB.existRelation(realRelation)) { // TODO: Add method to PKB-QPS API.
                continue;
            } else {
                return false;
            }
        }
        return true;
    }

    std::vector<std::vector<std::string>> ResultTable::getTable() {
        return this->table;
    }

    std::unordered_map<std::string, int> ResultTable::getSynonymColRef() {
        return this->synonymColRef;
    }
}
//
//int main() {
//    //get table
//    std::vector<std::string> v = { "A0", "B0", "C0" };
//    std::vector<std::string> vOther = { "A0", "E0", "C0", "F0"};
//    std::vector<std::string> v1 = { "A2", "B1", "C1" };
//    std::vector<std::string> v2 = { "A1", "B2", "C2" };
//    std::vector<std::string> v3 = { "A1", "B3", "C3" };
//    std::vector<std::string> v4 = { "A2", "E1", "C1", "F1" };
//    std::vector<std::string> v5 = { "A2", "E2", "C1", "F2" };
//    std::vector<std::string> v6 = { "A1", "E3", "C3", "F3" };
//    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> entries;
//    std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> entries2;
//    entries.insert(v1);
//    entries.insert(v2);
//    entries.insert(v3);
//    entries2.insert(v4);
//    entries2.insert(v5);
//    entries2.insert(v6);
//    QPS::ResultTable rt(v, entries);
//    QPS::ResultTable rtOther(vOther, entries2);
//    rt.mergeTable(rtOther);
//    rt.printTable();
//    rt.deleteColFromTable("F0");
//    rt.deleteColFromTable("E0");
//    rt.deleteDuplicateRows();
//    rt.printTable();
//    std::vector<std::string> values;
//    rt.getSynonymValue("F0", values);
//    rt.printStringVector(values);
//
//}