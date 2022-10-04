#include "CFGManager.h"

void CFGManager::createNewCFG() {
    currentCFG = CFGHead::createNewNodeHead();
    currentGenerator = CFGStandardNodeGenerator::createGenerator();
}
