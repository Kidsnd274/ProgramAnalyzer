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



std::unordered_map<int, int> QPS_Interface::getAllFollowsRelations() {
    return QPS_Interface::pkbInterface->getAllFollow();
}

std::unordered_map<std::string, std::unordered_set<std::string>> QPS_Interface::getAllCallRelations() {
    return QPS_Interface::pkbInterface->getAllProcVarRelation(RelationType::CALLS);
}

std::unordered_map<std::string, std::unordered_set<std::string>> QPS_Interface::getAllCallTRelations() {
    return QPS_Interface::pkbInterface->getAllProcVarRelation(RelationType::CALLS_T);
}

std::unordered_map<int, std::unordered_set<std::string>> QPS_Interface::getAllUsesRelations() {
    return QPS_Interface::pkbInterface->getAllStmtVarRelation(RelationType::USES_S);
}

std::unordered_map<std::string, std::unordered_set<std::string>> QPS_Interface::getAllUsesProcRelations() {
    return QPS_Interface::pkbInterface->getAllProcVarRelation(RelationType::USES_S);
}

std::unordered_map<int, std::unordered_set<std::string>> QPS_Interface::getAllModifiesRelations() {
    return QPS_Interface::pkbInterface->getAllStmtVarRelation(RelationType::MODIFIES_S);
}

std::unordered_map<std::string, std::unordered_set<std::string>> QPS_Interface::getAllModifiesProcRelations() {
    return QPS_Interface::pkbInterface->getAllProcVarRelation(RelationType::MODIFIES_S);
}

std::unordered_set<string> QPS_Interface::getAllAssigns() {
    return QPS_Interface::pkbInterface->getAllEntity(Argument::ASSIGN_SYNONYM);
}

std::unordered_set<unordered_set<Statement*>*> QPS_Interface::getAllStmtLists() {
    return QPS_Interface::pkbInterface->getAllStmtLists();
}

std::shared_ptr<AssignNode> QPS_Interface::getAssignTNode(std::string assignRef) {
    return pkbInterface->getAssignTNode(assignRef);
}

std::unordered_set<std::string> QPS_Interface::getAllEntity(Argument *argument) {
    return pkbInterface->getAllEntity(argument->argumentType);
}

std::unordered_set<std::string> QPS_Interface::getConditionVarNameByStmtNum(std::string containerLineNumber) {
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
        return pkbInterface->getVarName(StatementType::READ, value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::PRINT_SYNONYM) {
        return pkbInterface->getVarName(StatementType::PRINT, value);
    }
    return value;
}

CFGHeadPtr QPS_Interface::getCFGHeadPtrByProc(STMT_NUM stmt) {
    return QPS_Interface::pkbInterface->getCFGHeadPtrByProc(stmt);
}

Procedure* QPS_Interface::getProcByStmt(STMT_NUM stmt) {
    return QPS_Interface::pkbInterface->getProcByStmt(stmt);
}

std::unordered_set<Procedure*> QPS_Interface::getProcList() {
    return QPS_Interface::pkbInterface->getProcList();
}

bool QPS_Interface::hasNextStar(STMT_NUM stmt) {
    return QPS_Interface::pkbInterface->hasRelation(RelationType::NEXT_T, stmt);
}

std::unordered_set<STMT_NUM> QPS_Interface::getNextStar(STMT_NUM stmt) {
    if (!QPS_Interface::hasNextStar(stmt)) {
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt);
        QPS_Interface::runtimeExtractor->computeNextStar(cfgHeadPtr, stmt);
    }
    return QPS_Interface::pkbInterface->getStmtSet(RelationType::NEXT_T, stmt);
}

std::unordered_set<STMT_NUM> QPS_Interface::getAffects(STMT_NUM stmt) {
    bool hasAffects = QPS_Interface::pkbInterface->hasRelation(RelationType::AFFECTS, stmt);
    if (!hasAffects) {
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt);
        runtimeExtractor->computeAffects(cfgHeadPtr, stmt);
    }
    return QPS_Interface::pkbInterface->getStmtSet(RelationType::AFFECTS, stmt);
}

std::unordered_set<STMT_NUM> QPS_Interface::getAffectsStar(STMT_NUM stmt) {
    bool hasAffectsStar = QPS_Interface::pkbInterface->hasRelation(RelationType::AFFECTS_T, stmt);
    if (!hasAffectsStar) {
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt);
        runtimeExtractor->computeAffectsStar(cfgHeadPtr, stmt);
    }
    return QPS_Interface::pkbInterface->getStmtSet(RelationType::AFFECTS_T, stmt);
}

std::unordered_map<int, std::unordered_set<int>> QPS_Interface::getAllParentRelations(RelationType relationType) {
    if (relationType == PARENT) {
        return QPS_Interface::pkbInterface->getAllStmtRelation(RelationType::PARENT);
    } else if (relationType == PARENT_T) {
        return QPS_Interface::pkbInterface->getAllStmtRelation(RelationType::PARENT_T);
    } else {
        return {};
    }
}


