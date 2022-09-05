#include "SPAWrapperClass.h"

int main () {
    auto *pkbInterface = new PKBInterface();
    QPS::QueryManager queryManager = QPS::QueryManager();
    queryManager.handleQuery(pkbInterface);
}