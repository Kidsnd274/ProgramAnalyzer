#include "ResultTable.h"

namespace QPS {
    ResultTable::ResultTable(const std::vector<std::string>& sNames, const std::unordered_set<std::vector<std::string>, StringVectorHash >& entries) {
        type = ResultTable::NORMAL;
        colNum = 0;
        for (const std::string& sName : sNames) {
            if (isSynonymPresent(sName)) {
                suspendExecution("ResultTable: Try to insert duplicate synonym name to the table.");
            }
            synonymColRef[sName] = colNum;
            colNum++;
        }
        for (const std::vector<std::string>& entry : entries) {
            if (entry.size() != colNum) {
                suspendExecution("ResultTable: entry inserted to the table is of incompatible length.");
            }
            table.push_back(entry);
        }
        rowNum = entries.size();
        isInitialized = true;
    }

    bool ResultTable::deleteColFromTable(const std::vector<std::string> &sNames) {
        std::vector <std::vector<std::string>> newTable;
        std::vector <int> positions;
        std::unordered_set<std::string> addedRows;
        for (auto s : sNames) {
            if (synonymColRef.find(s) != synonymColRef.end()) {
                synonymColRef.erase(s);
            }
        }
        int colPos = 0;
        std::unordered_map<std::string, int> newSynonymColRef;
        for (auto synonym : synonymColRef) {
            positions.push_back(synonym.second);
            newSynonymColRef[synonym.first] = colPos;
            colPos++;
        }
        for (auto& entry : table) {
            std::vector<std::string> newRow;
            std::string addedRow;
            for (auto pos : positions) {
                newRow.push_back(entry[pos]);
                addedRow = addedRow + "|" + entry[pos];
            }
            if (addedRows.find(addedRow) == addedRows.end()) {
                newTable.push_back(newRow);
                addedRows.insert(addedRow);
            }
        }
        colNum = newSynonymColRef.size();
        this->synonymColRef = newSynonymColRef;
        this->table = newTable;
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
        for (const auto& entry : table) {
            values.push_back(entry[pos]);
        }
        return true;
    }

    bool ResultTable::getSynonymsValues(const std::vector<std::string>& sNames, std::unordered_set<std::vector<std::string>, StringVectorHash>& values) {
        std::vector<int> positions;
        for (const auto& sName : sNames) {
            if (!isSynonymPresent(sName)) {
                return false;
            } else {
                positions.push_back(synonymColRef.at(sName));
            }
        }
        values.clear();
        for (auto& entry : table) {
            std::vector<std::string> returnValue;
            for (int i : positions) {
                returnValue.push_back(entry[i]);
            }
            values.insert(returnValue);
        }
        return true;
    }


    bool ResultTable::isSynonymPresent(const std::string &sName) const {
        return synonymColRef.find(sName) != synonymColRef.end();
    }

    void suspendExecution(const std::string& errorMsg) {
        throw errorMsg;
    }

    ResultTable* ResultTable::mergeTable(QPS::ResultTable* const t1, QPS::ResultTable* const t2) {
        if (t1->isFalseTable() || t2 ->isTrueTable()) {
            return t1;
        }
        if (t1->isTrueTable() || t2->isFalseTable()) {
            return t2;
        }

        ResultTable* resultTable = new ResultTable();
        resultTable->colNum = t1->colNum;
        resultTable->rowNum = t1->rowNum;
        resultTable->synonymColRef = t1->synonymColRef;
        resultTable->table = t1->table;
        resultTable->isInitialized = t1->isInitialized;
        resultTable->type = t1->type;
        resultTable->mergeTable(*t2);
        return resultTable;
    }

    int ResultTable::getColNum() {
        return this->synonymColRef.size();
    }

    bool ResultTable::isEmptyTable() {
        return this->table.size() == 0;
    }
    void ResultTable::emptyTable() {
        this->table = {};
    }
    void ResultTable::mergeTable(const QPS::ResultTable& otherTable) {
        if (!otherTable.isInitialized || this->isFalseTable()) {
            return;
        }
        if (!this->isInitialized) {
            this->colNum = otherTable.colNum;
            this->rowNum = otherTable.rowNum;
            this->synonymColRef = otherTable.synonymColRef;
            this->table = otherTable.table;
            this->isInitialized = otherTable.isInitialized;
        }
        std::vector<int> otherUniqueCols, thisUniqueCols, otherCommonCols, thisCommonCols;
        std::vector<std::string> commonSynonyms, otherUniqueSynonyms;
        this->compareTableSynonyms(otherTable, commonSynonyms, otherUniqueCols, otherCommonCols, thisCommonCols, otherUniqueSynonyms);
        // No common synonyms
        if (commonSynonyms.empty()) {
            mergeWithoutSameSynonym(otherTable, otherUniqueCols);
            updateSynonymColRef(otherUniqueSynonyms);
            return;
        }
        // Got common synonyms
        // Categorize values of the common synonyms into groups and then compare with the other table to be merged with
        std::unordered_map<std::vector<std::string>, std::vector<int>, StringVectorHash> resultSet;
        this->commonSynonymValueSet(thisCommonCols, resultSet);
        mergeWithSameSynonyms(resultSet, otherTable, otherUniqueCols, otherCommonCols);
        updateSynonymColRef(otherUniqueSynonyms);
    }

    void ResultTable::commonSynonymValueSet(const std::vector<int> &commonSynonymCols,
                                            std::unordered_map<std::vector<std::string>, std::vector<int>, StringVectorHash> &resultSet) {
        int currRowNum = 0;
        for (auto &row : this->table) {
            std::vector<std::string> newValue;
            for (auto &col : commonSynonymCols) {
                newValue.push_back(row[col]);
            }
            if (resultSet.find(newValue) == resultSet.end()) {
                std::vector<int> v;
                resultSet[newValue] = v;
            }
            resultSet[newValue].push_back(currRowNum);
            currRowNum++;
        }
    }

    void ResultTable::updateSynonymColRef(const std::vector<std::string> &otherUniqueSynonyms) {
        for (auto &synonym : otherUniqueSynonyms) {
            synonymColRef[synonym] = colNum;
            colNum++;
        }
    }

    void ResultTable::mergeWithSameSynonyms(
            std::unordered_map<std::vector<std::string>, std::vector<int>, StringVectorHash> &resultSet,
            const QPS::ResultTable &otherTable, std::vector<int> &otherUniqueCols, std::vector<int> &otherCommonCols) {
        std::vector<std::vector<std::string>> newTable;
        for (auto &otherRow : otherTable.table) {
            std::vector<std::string> newValue;
            for (auto &col : otherCommonCols) {
                newValue.push_back(otherRow[col]);
            }
            if (resultSet.find(newValue) != resultSet.end()) {
                for (auto &sameValueRow : resultSet.at(newValue)) {
                    std::vector<std::string> newRow;
                    newRow.insert(newRow.end(), table[sameValueRow].begin(), table[sameValueRow].end());
                    for (auto &diffSynonymCol : otherUniqueCols) {
                        newRow.push_back(otherRow[diffSynonymCol]);
                    }
                    newTable.push_back(newRow);
                }
            }
        }
        rowNum = newTable.size();
        table = std::move(newTable);
    }

    void ResultTable::mergeWithoutSameSynonym(const QPS::ResultTable &otherTable, const std::vector<int>& otherUniqueCols) {
        std::vector<std::vector<std::string>> newTable;
        for (const auto &thisRow : table) {
            for (const auto &otherRow : otherTable.table) {
                std::vector<std::string> newRow;
                newRow.insert(newRow.end(), thisRow.begin(), thisRow.end());
                for (const auto &col : otherUniqueCols) {
                    newRow.push_back(otherRow[col]);
                }
                newTable.push_back(newRow);
            }
        }
        rowNum = newTable.size();
        table = std::move(newTable);
    }

    void ResultTable::compareTableSynonyms(const QPS::ResultTable &otherTable, std::vector<std::string> &commonSynonyms,
                                           std::vector<int> &otherUniqueCols, std::vector<int> &otherCommonCols,
                                           std::vector<int> &thisCommonCols,
                                           std::vector<std::string> &otherUniqueSynonyms) {
        for (const auto& synonym : synonymColRef) {
            if (otherTable.isSynonymPresent(synonym.first)) {
                commonSynonyms.push_back(synonym.first);
                thisCommonCols.push_back(synonym.second);
                otherCommonCols.push_back(otherTable.synonymColRef.at(synonym.first));
            }
        }
        for (auto &synonym : otherTable.synonymColRef) {
            bool otherSynonymNotPresent = std::find(commonSynonyms.begin(), commonSynonyms.end(), synonym.first) == commonSynonyms.end();
            if (otherSynonymNotPresent) {
                otherUniqueCols.push_back(synonym.second);
                otherUniqueSynonyms.push_back(synonym.first);
            }
        }
    }

    void ResultTable::deleteDuplicateRows(const std::vector<std::string> &sNames) {
        std::unordered_set<std::string> presentRows;
        std::vector<int> sPos;
        bool sNamesSelected = false;
        if (!sNames.empty()) {
            for (const auto& sName : sNames) {
                sPos.push_back(synonymColRef.find(sName)->second);
            }
            sNamesSelected = true;
        }
        int rows = table.size();
        for (int row = rows - 1; row >= 0; row--) {
            std::string s;
            if (sNamesSelected) {
                for (auto col : sPos) {
                    s += table[row][col] + "|";
                }
            } else {
                for (auto &entry : table[row]) {
                    s += entry + "|";
                }
            }
            if (presentRows.find(s) != presentRows.end()) {
                deleteRowFromTable(row);
            } else {
                presentRows.insert(s);
            }
        }
    }

    void ResultTable::replace(QPS::ResultTable *otherTable) {
        this->table = otherTable->table;
        this->synonymColRef = otherTable->synonymColRef;
        this->colNum = otherTable->colNum;
        this->rowNum = otherTable->rowNum;
        this->isInitialized = otherTable->isInitialized;
        this->type = otherTable->type;
    }

    std::vector<std::vector<std::string>> ResultTable::getTable() {
        return this->table;
    }

    std::unordered_map<std::string, int> ResultTable::getSynonymColRef() {
        return this->synonymColRef;
    }

    void ResultTable::setTable(std::vector<std::vector<std::string>>& newTable) {
        this->table = newTable;
    }
}  // namespace QPS
