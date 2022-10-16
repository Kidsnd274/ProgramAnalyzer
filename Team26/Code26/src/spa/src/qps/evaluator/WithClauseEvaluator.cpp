#include "WithClauseEvaluator.h"

void WithClauseEvaluator::evaluate(QPS::ResultTable *resultTable) {
    std::vector<std::vector<std::string>> table = resultTable->getTable();
    WithClause::WithClauseArgument arg1 = this->withClause->arg1;
    WithClause::WithClauseArgument arg2 = this->withClause->arg2;
    if (arg2.argument.argumentType == Argument::ACTUAL_NAME || arg2.argument.argumentType == Argument::NUMBER) { // a.attribute = "x"
        auto iter = resultTable->getSynonymColRef().find(arg1.argument.argumentName);
        if (iter == resultTable->getSynonymColRef().end()) {
            return;
        }
        int col = iter->second;
        for (int i = table.size() - 1; i >= 0; i--) {
            if (table.at(i).at(col) != arg2.argument.argumentName) {
                resultTable->deleteRowFromTable(i);
            }
        }
    } else { // a.attribute = b.attribute
        auto iter1 = resultTable->getSynonymColRef().find(arg1.argument.argumentName);
        if (iter1 == resultTable->getSynonymColRef().end()) {
            return;
        }
        int col1 = iter1->second;
        auto iter2 = resultTable->getSynonymColRef().find(arg2.argument.argumentName);
        if (iter2 == resultTable->getSynonymColRef().end()) {
            return;
        }
        int col2 = iter2->second;
        for (int i = table.size() - 1; i >= 0; i--) {
            if (table.at(i).at(col1) != table.at(i).at(col2)) {
                resultTable->deleteRowFromTable(i);
            }
        }
    }
}