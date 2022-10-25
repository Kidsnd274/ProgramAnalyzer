#include "QPS_PKB_Interface.h"

PKBInterface* QPS_PKB_Interface::pkbInterface = nullptr;

void QPS_PKB_Interface::setPKBInterface(PKBInterface *myPKBInterface) {
    QPS_PKB_Interface::pkbInterface = myPKBInterface;
}

std::shared_ptr<AssignNode> getAssignTNode(std::string assignRef) {
    return QPS_PKB_Interface::pkbInterface->getAssignTNode(assignRef);
}


// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::unordered_map<int, int> QPS_PKB_Interface::getAllFollowsRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllFollow();
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::unordered_map<int, vector<int>> QPS_PKB_Interface::getAllParentRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllParent();
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::unordered_map<int, vector<int>> QPS_PKB_Interface::getAllParentTRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllParentStar();
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllCallRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllCall();
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllCallTRelations() {
        return QPS_PKB_Interface::pkbInterface->getAllCallStar();
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::unordered_map<int, std::vector<std::string>> QPS_PKB_Interface::getAllUsesRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllUseByStmt();
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllUsesProcRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllUseByProc();
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::unordered_map<int, std::vector<std::string>> QPS_PKB_Interface::getAllModifiesRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllModifyByStmt();
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllModifiesProcRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllModifyByProc();
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::vector<pair<int, int>> QPS_PKB_Interface::getAllAffectsRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllAffects();
    return {};
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::vector<pair<int, int>> QPS_PKB_Interface::getAllAffectsProcRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllAffectsProc();
    return {};
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::unordered_map<int, std::vector<int>> QPS_PKB_Interface::getAllNextRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllNext();
}

// S1 (Major): DRY - code structure is similar to other get-all-relationship methods
std::vector<pair<int, int>> QPS_PKB_Interface::getAllNextProcRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllNextProc();
    return {};
}

std::vector<std::string> QPS_PKB_Interface::getAllAssigns() {
    return QPS_PKB_Interface::pkbInterface->getAllAssigns();
}

std::vector<std::vector<Statement>> QPS_PKB_Interface::getAllStmtLists() {
    return QPS_PKB_Interface::pkbInterface->getAllStmtLists();
}

std::shared_ptr<AssignNode> QPS_PKB_Interface::getAssignTNode(std::string assignRef) {
    return pkbInterface->getAssignTNode(assignRef);
}

std::vector<std::string> QPS_PKB_Interface::getAllEntity(Argument *argument) {
    switch (argument->argumentType) {
        case Argument::STMT_SYNONYM:
            return pkbInterface->getAllStmts();
        case Argument::READ_SYNONYM:
            return pkbInterface->getAllReads();
        case Argument::PRINT_SYNONYM:
            return pkbInterface->getAllPrints();
        case Argument::CALL_SYNONYM:
            return pkbInterface->getAllCalls();
        case Argument::WHILE_SYNONYM:
            return pkbInterface->getAllWhiles();
        case Argument::IF_SYNONYM:
            return pkbInterface->getAllIfs();
        case Argument::ASSIGN_SYNONYM:
            return pkbInterface->getAllAssigns();
        case Argument::VAR_SYNONYM:
            return pkbInterface->getAllVariables();
        case Argument::CONST_SYNONYM:
            return pkbInterface->getAllConstants();
        case Argument::PROCEDURE_SYNONYM:
            return pkbInterface->getAllProcedures();
        default:
            return {};
    }
}

std::string QPS_PKB_Interface::getProcLineNumberByName(std::string procName) {
    return pkbInterface->getProcLineNumberByName(procName);
}

std::string QPS_PKB_Interface::getCallProcName(std::string callLineNumber) {
    return pkbInterface->getCallProcName(callLineNumber);
}

std::string QPS_PKB_Interface::getReadVarName(std::string readLineNumber) {
    return pkbInterface->getReadVarName(readLineNumber);
}

std::string QPS_PKB_Interface::getPrintVarName(std::string printLineNumber) {
    return pkbInterface->getPrintVarName(printLineNumber);
}

std::vector<std::string> QPS_PKB_Interface::getConditionVarNameByStmtNum(std::string containerLineNumber) {
    return pkbInterface->getConditionVar(containerLineNumber);
}

std::string QPS_PKB_Interface::getAttrName(std::string value, WithClause::WithClauseArgument candidate) {
    if (candidate.attributeType == AttributeType::STMT_LINE_NUMBER
        && candidate.argument.argumentType == Argument::PROCEDURE_SYNONYM) {
        string temp = QPS_PKB_Interface::getProcLineNumberByName(value);
        return QPS_PKB_Interface::getProcLineNumberByName(value);
    }
    if (candidate.attributeType == AttributeType::PROC_NAME
        && candidate.argument.argumentType == Argument::CALL_SYNONYM) {
        return QPS_PKB_Interface::getCallProcName(value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::READ_SYNONYM) {
        return QPS_PKB_Interface::getReadVarName(value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::PRINT_SYNONYM) {
        return QPS_PKB_Interface::getPrintVarName(value);
    }
    return value;
}

std::string QPS_PKB_Interface::getAttrName(std::string value, Query::CandidateStruct candidate) {
    if (candidate.attributeType == AttributeType::STMT_LINE_NUMBER
        && candidate.argument.argumentType == Argument::PROCEDURE_SYNONYM) {
        string temp = QPS_PKB_Interface::getProcLineNumberByName(value);
        return QPS_PKB_Interface::getProcLineNumberByName(value);
    }
    if (candidate.attributeType == AttributeType::PROC_NAME
        && candidate.argument.argumentType == Argument::CALL_SYNONYM) {
        return QPS_PKB_Interface::getCallProcName(value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::READ_SYNONYM) {
        return QPS_PKB_Interface::getReadVarName(value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::PRINT_SYNONYM) {
        return QPS_PKB_Interface::getPrintVarName(value);
    }
    return value;
}