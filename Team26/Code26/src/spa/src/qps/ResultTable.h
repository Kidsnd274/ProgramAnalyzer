#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include "qps/QueryManager.h"

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

        /**
         * Delete a row indicated by row number.
         * @param row the row number of the row to delete.
         */
        void deleteRowFromTable(const int row);

        /**
         * Check whether a synonym is present in the table using the synonym name.
         * Return true if present.
         *
         * @param sName The given synonym name in string.
         * @return bool
         */
        bool isSynonymPresent(const std::string& sName) const;

        /**
         * Get the values of a given synonym name present in the table.
         *
         * @param sName The given synonym name in string.
         * @param values A vector of string to store the values of this synonym.
         * @return True if the synonym is present, false otherwise.
         */
        bool getSynonymValue(const std::string& sName, std::vector<std::string>& values);

        /**
         * Get the values of multiple given synonym names present in the table.
         *
         * @param sName The given synonym names in a vector of string.
         * @param values A vector of string vectors to store the values of the synonyms.
         * @return True if all synonyms are present, false otherwise.
         */
        bool getSynonymsValues(const std::vector<std::string>& sNames, std::unordered_set<std::vector<std::string>, StringVectorHash>& values);

        /**
         * Merge this table with another table.
         * If there are no common synonyms, perform cartesian product on these two tables. For example, if Table A has
         * m rows and Table b has n rows, the result would be m*n rows.
         * If there exist common synonyms as set C, find rows in both tables that have the same values for all the synonyms
         * in set C and then perform cartesian product.
         *
         * @param otherTable The other table this table is to be merged with.
         */
        void mergeTable(const ResultTable& otherTable);
        void compareTableSynonyms(const ResultTable& otherTable, std::vector<std::string>& commonSynonyms, std::vector<int>& otherUniqueCols, std::vector<int>& otherCommonCols, std::vector<int>& thisCommonCols, std::vector<std::string> &otherUniqueSynonyms);
        void mergeWithoutSameSynonym(const ResultTable &otherTable, const std::vector<int>& otherUniqueCols);
        void updateSynonymColRef(const std::vector<std::string> &otherUniqueSynonyms);
        void commonSynonymValueSet(const std::vector<int> &commonSynonymCols, std::unordered_map<std::vector<std::string>, std::vector<int>, StringVectorHash> &resultSet);
        void mergeWithSameSynonyms(std::unordered_map<std::vector<std::string>, std::vector<int>, StringVectorHash> &resultSet, const ResultTable& otherTable, std::vector<int>& otherUniqueCols, std::vector<int>& otherCommonCols);

        /**
         * Delete duplicate rows in the table. Two rows are duplicate if the values of the selected synonym
         * are the same.
         *
         * @param sNames selected synonyms to compare.
         */
        void deleteDuplicateRows(const std::vector<std::string>& sNames);

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
         * This method checks whether each row in result table follows to the given type.
         * If a row does not follow the list of type, delete that row.
         *
         * @param suchThatList List of given type.
         */
        void filterRowsBySuchThatList(const SUCH_THAT_LIST& suchThatList);

        /**
         * Checks whether each row in result table follows to the given patterns.
         * If a row does not follow the list of patterns, delete that row.
         *
         * @param patternList List of given patterns.
         */
        void filterRowsByPatternList(const PATTERN_LIST& patternList);

        /**
         * Checks whether the given row follows the given type.
         *
         * @param row The given row.
         * @param relation The given type.
         * @return bool
         */
        bool followsRelation(std::vector<std::string>& row, const QPS::RelationStruct& relation);

        /**
         * Checks whether the given row follows the given pattern.
         *
         * @param row The given row.
         * @param pattern The given pattern.
         * @return bool
         */
        bool followsPattern(std::vector<std::string> &row, QPS::PatternStruct pattern);
        static bool isPatternMatched(QPS::PatternStruct pattern);

        //for debug purpose
        void printTable();
        std::vector<std::vector<std::string>> getTable();
        std::unordered_map<std::string, int> getSynonymColRef();
        static void printStringVector(const std::vector<std::string>& v);
        void printIntVector(const std::vector<int>& v);
    };

    void suspendExecution(const std::string& errorMsg);
}