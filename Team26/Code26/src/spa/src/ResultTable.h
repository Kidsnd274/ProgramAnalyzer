#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include "QueryProcessorTypes.h"

namespace QPS {
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
            rowNum = 1;
            std::vector<std::string> emptyRow;
            this->table.emplace_back(emptyRow);
        }
        ResultTable(const std::vector<std::string>& sNames, const std::unordered_set<std::vector<std::string>, StringVectorHash>& entries);
        bool deleteColFromTable(const std::string& sName);
        void deleteRowFromTable(const int row);
        bool isSynonymPresent(const std::string& sName) const;
        bool getSynonymValue(const std::string& sName, std::vector<std::string>& values);
        bool getSynonymsValues(const std::vector<std::string>& sNames, std::unordered_set<std::vector<std::string>, StringVectorHash>& values);
        void mergeTable(const ResultTable& otherTable);
        void compareTableSynonyms(const ResultTable& otherTable, std::vector<std::string>& commonSynonyms, std::vector<int>& otherUniqueCols, std::vector<int>& otherCommonCols, std::vector<int>& thisCommonCols, std::vector<std::string> &otherUniqueSynonyms);
        void mergeWithoutSameSynonym(const ResultTable &otherTable, const std::vector<int>& otherUniqueCols);
        void updateSynonymColRef(const std::vector<std::string> &otherUniqueSynonyms);
        void commonSynonymValueSet(const std::vector<int> &commonSynonymCols, std::unordered_map<std::vector<std::string>, std::vector<int>, StringVectorHash> &resultSet);
        void mergeWithSameSynonyms(std::unordered_map<std::vector<std::string>, std::vector<int>, StringVectorHash> &resultSet, const ResultTable& otherTable, std::vector<int>& otherUniqueCols, std::vector<int>& otherCommonCols);
        void deleteDuplicateRows();
        /**
         * Add a new column to the result table. This new column is all the entities of a new synonym.
         * This method will take the cartesian product of set A and B, where set A is the set of original rows and
         * set B is the set of rows in the new column.
         *
         * @param nameOfSynonym Name of the new synonym.
         * @param entities All the entities of this new synonym.
         */
        void addColumnAndMerge(std::string nameOfSynonym, std::vector<std::string> entities);

        /**
         * Each row in result table is a set of possible bindings of synonyms to entities.
         * This method checks whether each row in result table follows to the given relation.
         * If a row does not follow the list of relation, delete that row.
         *
         * @param suchThatList List of given relation.
         */
        void filterRows(SUCH_THAT_LIST suchThatList);

        /**
         * Check whether the given row follows the list of relation.
         *
         * @param row The given row.
         * @param suchThatList The given list of relation.
         * @return bool
         */
        bool followsRelation(std::vector<std::string>& row, SUCH_THAT_LIST suchThatList);
        //for debug purpose
        void printTable();
        std::vector<std::vector<std::string>> getTable();
        std::unordered_map<std::string, int> getSynonymColRef();
        void printStringVector(std::vector<std::string> v);
        void printIntVector(std::vector<int> v);
    };

    void suspendExecution(const std::string& errorMsg);
}