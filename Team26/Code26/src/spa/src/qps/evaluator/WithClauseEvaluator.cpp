#include "WithClauseEvaluator.h"


void WithClauseEvaluator::evaluate(QPS::ResultTable *resultTable) {
    ArgAttrStruct arg1 = this->withClause->arg1;
    ArgAttrStruct arg2 = this->withClause->arg2;
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
