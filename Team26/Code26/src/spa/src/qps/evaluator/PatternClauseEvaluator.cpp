#include "PatternClauseEvaluator.h"
void PatternClauseEvaluator::evaluate(ResultTable* resultTable) {
    //initialize result table
    if (this->patternClause->argument1.argumentType == Argument::IF_SYNONYM
    || this->patternClause->argument1.argumentType == Argument::WHILE_SYNONYM) {
        evaluateContainer(resultTable);
        return;
    }
    std::unordered_set<std::vector<std::string>, StringVectorHash> result;
    std::vector<std::string> synonyms = {this->patternClause->argument1.argumentName};
    if (patternClause->argument2.argumentType == Argument::VAR_SYNONYM) {
        synonyms.push_back(patternClause->argument2.argumentName);
    }
    //insert rows into table
    vector<string> allAssigns = QPS_Interface::getAllAssigns();
    WildcardPosition pos = getWildcardPosition();
    std::shared_ptr<TNode> patternNode = getPatternNode(pos);
    bool useActualName = this->patternClause->argument2.argumentType == Argument::ACTUAL_NAME;
    for (auto assign: allAssigns) {
        std::shared_ptr<AssignNode> assignNode = QPS_Interface::getAssignTNode(assign);
        if (useActualName && this->patternClause->argument2.argumentName != assignNode->getVariableName()) {
            continue;
        }
        bool isPatternMatched = this->patternClause->argument3.argumentType == Argument::WILDCARD
                                || TNode::matchSubTree(assignNode->getExpression(), patternNode, pos);
        if (isPatternMatched) {
            vector<string> tableRow = {assign};
            if (this->patternClause->argument2.argumentType == Argument::VAR_SYNONYM) {
                tableRow.push_back(assignNode->getVariableName());
            }
            result.insert(tableRow);
        }
    }
    ResultTable tableToReturn = ResultTable(synonyms, result);
    resultTable->replace(&tableToReturn);
}

WildcardPosition PatternClauseEvaluator::getWildcardPosition() {
    WildcardPosition pos;
    Argument arg2 = this->patternClause->argument3;
    std::string argumentName = arg2.argumentName;
    bool firstCharIsUnderscore = argumentName[0] == '_';
    bool lastCharIsUnderscore = argumentName[argumentName.length() - 1] == '_';
    if (firstCharIsUnderscore) {
        if (lastCharIsUnderscore) {
            pos = WildcardPosition::BOTH;
        } else {
            pos = WildcardPosition::LEFT;
        }
    } else {
        if (lastCharIsUnderscore) {
            pos = WildcardPosition::RIGHT;
        } else {
            pos = WildcardPosition::NONE;
        }
    }
    return pos;
}

void PatternClauseEvaluator::evaluateContainer(QPS::ResultTable *resultTable) {
    vector<string> stmtNumbers = QPS_Interface::getAllEntity(&this->patternClause->argument1);
    unordered_set<vector<string>, StringVectorHash> result;
    for (auto s: stmtNumbers) {
        std::vector<string> varNames = QPS_Interface::getConditionVarNameByStmtNum(s);
        for (auto varName: varNames) {
            if (this->patternClause->argument2.argumentType == Argument::ACTUAL_NAME) {
                if (varName != this->patternClause->argument2.argumentName) {
                    continue;
                }
                result.insert({s});
            } else if (this->patternClause->argument2.argumentType == Argument::VAR_SYNONYM) {
                result.insert({s, varName});
            } else { //wildcard
                result.insert({s});
            }
        }
    }
    vector<string> synonyms;
    synonyms.push_back(this->patternClause->argument1.argumentName);
    if (this->patternClause->argument2.argumentType == Argument::VAR_SYNONYM) {
        synonyms.push_back(this->patternClause->argument2.argumentName);
    }
    ResultTable tableToReturn = ResultTable(synonyms, result);
    resultTable->replace(&tableToReturn);
}

shared_ptr<TNode> PatternClauseEvaluator::getPatternNode(WildcardPosition pos) {
    std::string trimmedString;
    Argument arg2 = this->patternClause->argument3;
    std::string argumentName = arg2.argumentName;
    switch (pos) {
        case (WildcardPosition::BOTH): {
            trimmedString = argumentName.substr(1, arg2.argumentName.length() - 2);
            break;
        }
        case (WildcardPosition::LEFT): {
            trimmedString = argumentName.substr(1, arg2.argumentName.length() - 1);
            break;
        }
        case (WildcardPosition::RIGHT): {
            trimmedString = argumentName.substr(0, argumentName.length() - 1);
            break;
        }
        case (WildcardPosition::NONE): {
            trimmedString = argumentName;
            break;
        }
    }
    shared_ptr<TNode> node = nullptr;
    if (trimmedString != "") {
        node = SourceProcessor::parseExpressionFromString(trimmedString);
    }
    return node;
}