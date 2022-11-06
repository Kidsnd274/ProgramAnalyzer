#include "QPS_Interface.h"

PKBInterface* QPS_Interface::pkbInterface = nullptr;
RuntimeExtractor* QPS_Interface::runtimeExtractor = nullptr;

void QPS_Interface::setPKBInterface(PKBInterface *myPKBInterface) {
    QPS_Interface::pkbInterface = myPKBInterface;
}


void QPS_Interface::createRuntimeExtractor() {
    QPS_Interface::runtimeExtractor = new RuntimeExtractor(QPS_Interface::pkbInterface);
}

void QPS_Interface::clearRuntimeExtractor() {
    QPS_Interface::runtimeExtractor->clearCache();
}

std::shared_ptr<AssignNode> getAssignTNode(std::string assignRef) {
    return QPS_Interface::pkbInterface->getAssignTNode(assignRef);
}


std::unordered_map<int, int> QPS_Interface::getAllFollowsRelations() {
    return QPS_Interface::pkbInterface->getAllFollow();
}

std::unordered_map<int, std::vector<std::string>> QPS_Interface::getAllUsesRelations() {
    return QPS_Interface::pkbInterface->getAllUseByStmt();
}

std::unordered_map<int, std::vector<std::string>> QPS_Interface::getAllModifiesRelations() {
    return QPS_Interface::pkbInterface->getAllModifyByStmt();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_Interface::getAllCallRelations() {
    return QPS_Interface::pkbInterface->getAllCall();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_Interface::getAllCallTRelations() {
    return QPS_Interface::pkbInterface->getAllCallStar();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_Interface::getAllUsesProcRelations() {
    return QPS_Interface::pkbInterface->getAllUseByProc();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_Interface::getAllModifiesProcRelations() {
    return QPS_Interface::pkbInterface->getAllModifyByProc();
}


std::vector<std::string> QPS_Interface::getAllAssigns() {
    return QPS_Interface::pkbInterface->getAllAssigns();
}

std::vector<std::vector<Statement>> QPS_Interface::getAllStmtLists() {
    return QPS_Interface::pkbInterface->getAllStmtLists();
}

std::shared_ptr<AssignNode> QPS_Interface::getAssignTNode(std::string assignRef) {
    return pkbInterface->getAssignTNode(assignRef);
}

std::unordered_set<std::string> QPS_Interface::getAllEntity(Argument *argument) {
    std::vector<std::string> result;
    std::unordered_set<std::string> resultSet;
    switch (argument->argumentType) {
        case Argument::STMT_SYNONYM:
            result = pkbInterface->getAllStmts();
            break;
        case Argument::READ_SYNONYM:
            result = pkbInterface->getAllReads();
            break;
        case Argument::PRINT_SYNONYM:
            result = pkbInterface->getAllPrints();
            break;
        case Argument::CALL_SYNONYM:
            result = pkbInterface->getAllCalls();
            break;
        case Argument::WHILE_SYNONYM:
            result = pkbInterface->getAllWhiles();
            break;
        case Argument::IF_SYNONYM:
            result = pkbInterface->getAllIfs();
            break;
        case Argument::ASSIGN_SYNONYM:
            result = pkbInterface->getAllAssigns();
            break;
        case Argument::VAR_SYNONYM:
            result = pkbInterface->getAllVariables();
            break;
        case Argument::CONST_SYNONYM:
            result = pkbInterface->getAllConstants();
            break;
        case Argument::PROCEDURE_SYNONYM:
            result = pkbInterface->getAllProcedures();
            break;
        default:
            return {};
    }
    for (auto i : result) {
        resultSet.insert(i);
    }
    return resultSet;
}



std::vector<std::string> QPS_Interface::getConditionVarNameByStmtNum(std::string containerLineNumber) {
    return pkbInterface->getConditionVar(containerLineNumber);
}

std::string QPS_Interface::getAttrName(std::string value, ArgAttrStruct candidate) {
    if (candidate.attributeType == AttributeType::STMT_LINE_NUMBER
        && candidate.argument.argumentType == Argument::PROCEDURE_SYNONYM) {
        return pkbInterface->getProcLineNumberByName(value);
    }
    if (candidate.attributeType == AttributeType::PROC_NAME
        && candidate.argument.argumentType == Argument::CALL_SYNONYM) {
        return pkbInterface->getCallProcName(value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::READ_SYNONYM) {
        return pkbInterface->getReadVarName(value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::PRINT_SYNONYM) {
        return pkbInterface->getPrintVarName(value);
    }
    return value;
}

CFGHeadPtr QPS_Interface::getCFGHeadPtrByProc(STMT_NUM stmt) {
    return QPS_Interface::pkbInterface->getCFGHeadPtrByProc(stmt);
}

Procedure* QPS_Interface::getProcByStmt(STMT_NUM stmt) {
    return QPS_Interface::pkbInterface->getProcByStmt(stmt);
}

std::vector<Procedure> QPS_Interface::getProcList() {
    return QPS_Interface::pkbInterface->getProcList();
}

bool QPS_Interface::hasNextStar(STMT_NUM stmt) {
    return QPS_Interface::pkbInterface->hasNextStar(stmt);
}

std::unordered_set<STMT_NUM> QPS_Interface::getNextStar(STMT_NUM stmt) {
    if (!QPS_Interface::hasNextStar(stmt)) {
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt);
        QPS_Interface::runtimeExtractor->computeNextStar(cfgHeadPtr, stmt);
    }
    return QPS_Interface::pkbInterface->getNextStar(stmt);
}

std::unordered_set<STMT_NUM> QPS_Interface::getAffects(STMT_NUM stmt) {
    bool hasAffects = QPS_Interface::pkbInterface->hasAffects(stmt);
    if (!hasAffects) {
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt);
        runtimeExtractor->computeAffects(cfgHeadPtr, stmt);
    }
    return QPS_Interface::pkbInterface->getAffects(stmt);
}

std::unordered_set<STMT_NUM> QPS_Interface::getAffectsStar(STMT_NUM stmt) {
    bool hasAffectsStar = QPS_Interface::pkbInterface->hasAffectsStar(stmt);
    if (!hasAffectsStar) {
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt);
        runtimeExtractor->computeAffectsStar(cfgHeadPtr, stmt);
    }
    return QPS_Interface::pkbInterface->getAffectsStar(stmt);
}

std::unordered_map<int, std::vector<int>> QPS_Interface::getAllParentRelations(RelationType relationType) {
    if (relationType == PARENT) {
        return QPS_Interface::pkbInterface->getAllParent();
    } else if (relationType == PARENT_T) {
        return QPS_Interface::pkbInterface->getAllParentStar();
    } else {
        return {};
    }
}


