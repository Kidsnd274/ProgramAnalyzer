#include "CFGLogic.h"

bool CFGLogic::isStatementInCFG(STMT_NUM stmt1) {
    return adjList->find(stmt1) != adjList->end();
}
