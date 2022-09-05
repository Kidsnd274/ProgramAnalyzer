#include "SPAWrapperClass.h"

#include <utility>
#include "sp/SourceProcessor.h"

void processSIMPLE (std::string sourcefile) {
    auto *pkbInterface = new PKBInterface();
    auto sourceProcessor = SourceProcessor(pkbInterface);
    sourceProcessor.processSIMPLE(std::move(sourcefile));
    QPS::QueryManager queryManager = QPS::QueryManager();
    queryManager.handleQuery(pkbInterface);
}

int main () {
    auto *pkbInterface = new PKBInterface();
    auto sourceProcessor = SourceProcessor(pkbInterface);
    QPS::QueryManager queryManager = QPS::QueryManager();
    queryManager.handleQuery(pkbInterface);
}