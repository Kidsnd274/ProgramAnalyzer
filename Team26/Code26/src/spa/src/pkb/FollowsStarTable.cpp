#include <algorithm>
#include "FollowsStarTable.h"

using namespace std;

void FollowsStarTable::insertFollowsStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int,int> followsStar (frontStmtLineNumber, backStmtLineNumber);
    this->followsStarList.insert(followsStar);
}
