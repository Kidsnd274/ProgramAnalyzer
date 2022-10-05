#include "CFGManager.h"

void CFGManager::createNewCFG() {
    currentCFG = CFGHead::createNewCFG();
}

CFGHeadPtr CFGManager::getCurrentCFG() {
    return currentCFG;
}
