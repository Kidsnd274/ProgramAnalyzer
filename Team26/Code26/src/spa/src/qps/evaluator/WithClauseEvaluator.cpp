#include "WithClauseEvaluator.h"

//void WithClauseEvaluator::evaluate2(QPS::ResultTable *resultTable) {
//    std::vector<std::vector<std::string>> table = resultTable->getTable();
//    WithClause::WithClauseArgument arg1 = this->withClause->arg1;
//    WithClause::WithClauseArgument arg2 = this->withClause->arg2;
//
//    if (arg1.argument.argumentType == Argument::ACTUAL_NAME || arg1.argument.argumentType == Argument::NUMBER) {
//        arg1 = this->withClause->arg2;
//        arg2 = this->withClause->arg1;
//    }
//
//    if (arg2.argument.argumentType == Argument::ACTUAL_NAME || arg2.argument.argumentType == Argument::NUMBER) { // a.attribute = "x"
//        if (arg1.argument.argumentType == Argument::ACTUAL_NAME || arg1.argument.argumentType == Argument::NUMBER) {
//            for (int i = table.size() - 1; i >= 0; i--) {
//                if (arg1.argument.argumentName != arg2.argument.argumentName) {
//                    resultTable->deleteRowFromTable(i);
//                }
//            }
//            return;
//        }
//        auto iter = resultTable->getSynonymColRef().find(arg1.argument.argumentName);
//        if (iter == resultTable->getSynonymColRef().end()) {
//            return;
//        }
//        int col = iter->second;
//        for (int i = table.size() - 1; i >= 0; i--) {
//            std::string attrName = QPS_Interface::getAttrName(table.at(i).at(col), arg1);
//            if (attrName != arg2.argument.argumentName) {
//                resultTable->deleteRowFromTable(i);
//            }
//        }
//    } else { // a.attribute = b.attribute
//        auto map = resultTable->getSynonymColRef();
//        auto iter1 = map.find(arg1.argument.argumentName);
//        if (iter1 == map.end()) {
//            return;
//        }
//        int col1 = iter1->second;
//        auto iter2 = map.find(arg2.argument.argumentName);
//        if (iter2 == map.end()) {
//            return;
//        }
//        int col2 = iter2->second;
//        for (int i = table.size() - 1; i >= 0; i--) {
//            std::string attrName1 = QPS_Interface::getAttrName(table.at(i).at(col1), arg1);
//            std::string attrName2 = QPS_Interface::getAttrName(table.at(i).at(col2), arg2);
//            if (attrName1 != attrName2) {
//                resultTable->deleteRowFromTable(i);
//            }
//        }
//    }
//}

void WithClauseEvaluator::evaluate(QPS::ResultTable *resultTable) {
    WithClause::WithClauseArgument arg1 = this->withClause->arg1;
    WithClause::WithClauseArgument arg2 = this->withClause->arg2;
    // If arg1 is not a synonym, swap(arg1, arg2)
    if (arg1.argument.argumentType == Argument::ACTUAL_NAME || arg1.argument.argumentType == Argument::NUMBER) {
        arg1 = this->withClause->arg2;
        arg2 = this->withClause->arg1;
    }
    if (arg1.argument.argumentType == Argument::ACTUAL_NAME) {
        // ACTUAL_NAME, ACTUAL_NAME
        if (arg2.argument.argumentType == Argument::ACTUAL_NAME
            && arg1.argument.argumentName == arg2.argument.argumentName) {
            resultTable->setTrueTable();
            return;
        }
        resultTable->setFalseTable();
        return;
    }
    if (arg1.argument.argumentType == Argument::NUMBER) {
        // NUMBER, NUMBER
        if (arg2.argument.argumentType == Argument::NUMBER
            && arg1.argument.argumentName == arg2.argument.argumentName) {
            resultTable->setTrueTable();
            return;
        }
        resultTable->setFalseTable();
        return;
    }
    if (Argument::isSynonym(arg1.argument.argumentType)) {
        std::vector<std::string> synonyms = {arg1.argument.argumentName};
        std::unordered_set<std::vector<std::string>, QPS::StringVectorHash> lines;
        std::unordered_set<std::string> valuesList1 = QPS_Interface::getAllEntity(&arg1.argument);
        // SYNONYM, SYNONYM
        if (Argument::isSynonym(arg2.argument.argumentType)) {
            synonyms.push_back(arg2.argument.argumentName);
            std::unordered_set<std::string> valuesList2 = QPS_Interface::getAllEntity(&arg2.argument);
            for (auto value1 : valuesList1) {
                for (auto value2 : valuesList2) {
                    if (QPS_Interface::getAttrName(value1, arg1) == QPS_Interface::getAttrName(value2, arg2)) {
                        lines.insert(std::vector<std::string> {value1, value2});
                    }
                }
            }
            resultTable->replace(new ResultTable(synonyms, lines));
            return;
        }
        // SYNONYM, ACTUAL_NAME or NUMBER
        for (auto value1 : valuesList1) {
            if (QPS_Interface::getAttrName(value1, arg1) == arg2.argument.argumentName) {
                lines.insert(std::vector<std::string> {value1});
            }
        }
        resultTable->replace(new ResultTable(synonyms, lines));
        return;
    }
}