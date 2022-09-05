#include "SPAWrapperClass.h"

#include <utility>
#include "sp/SourceProcessor.h"

//void processSIMPLE (std::string sourcefile) {
//    auto *pkbInterface = new PKBInterface();
//    auto sourceProcessor = SourceProcessor(pkbInterface);
//    sourceProcessor.processSIMPLE(std::move(sourcefile));
//    vector<string> entities = pkbInterface->getAllEntity(EntityType::CONSTANT);
//    for (int i = 0; i < entities.size(); ++i) {
//        std::cout << entities[i] << endl;
//    }
//    QPS::QueryManager queryManager = QPS::QueryManager();
//    queryManager.handleQuery(pkbInterface);
//}