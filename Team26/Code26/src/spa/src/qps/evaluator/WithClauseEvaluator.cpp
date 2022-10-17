#include "WithClauseEvaluator.h"

void WithClauseEvaluator::evaluate(QPS::ResultTable *resultTable) {
    std::vector<std::vector<std::string>> table = resultTable->getTable();
    WithClause::WithClauseArgument arg1 = this->withClause->arg1;
    WithClause::WithClauseArgument arg2 = this->withClause->arg2;

    if (arg1.argument.argumentType == Argument::ACTUAL_NAME || arg1.argument.argumentType == Argument::NUMBER) {
        arg1 = this->withClause->arg2;
        arg2 = this->withClause->arg1;
    }

    if (arg2.argument.argumentType == Argument::ACTUAL_NAME || arg2.argument.argumentType == Argument::NUMBER) { // a.attribute = "x"
        if (arg1.argument.argumentType == Argument::ACTUAL_NAME || arg1.argument.argumentType == Argument::NUMBER) {
            for (int i = table.size() - 1; i >= 0; i--) {
                if (arg1.argument.argumentName != arg2.argument.argumentName) {
                    resultTable->deleteRowFromTable(i);
                }
            }
            return;
        }
        if (!resultTable->getSynonymColRef().count(arg1.argument.argumentName)) {
            return;
        }
        auto iter = resultTable->getSynonymColRef().find(arg1.argument.argumentName);
        int col = iter->second;
        for (int i = table.size() - 1; i >= 0; i--) {
            std::string attrName = QPS_PKB_Interface::getAttrName(table.at(i).at(col), arg1);
            if (attrName != arg2.argument.argumentName) {
                resultTable->deleteRowFromTable(i);
            }
        }
    } else { // a.attribute = b.attribute
        if (!resultTable->getSynonymColRef().count(arg1.argument.argumentName)) {
            return;
        }
        auto iter1 = resultTable->getSynonymColRef().find(arg1.argument.argumentName);
        int col1= iter1->second;

        if (!resultTable->getSynonymColRef().count(arg2.argument.argumentName)) {
            return;
        }
        auto iter2 = resultTable->getSynonymColRef().find(arg2.argument.argumentName);
        int col2 = iter2->second;
        for (int i = table.size() - 1; i >= 0; i--) {
            std::string attrName1 = QPS_PKB_Interface::getAttrName(table.at(i).at(col1), arg1);
            std::string attrName2 = QPS_PKB_Interface::getAttrName(table.at(i).at(col2), arg2);
            if (attrName1 != attrName2) {
                resultTable->deleteRowFromTable(i);
            }
        }
    }
}