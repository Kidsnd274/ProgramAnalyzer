#ifndef SPA_QUERYMANAGER_H
#define SPA_QUERYMANAGER_H

#include "Tokenizer.h"
#include "pkb/PKBInterface.h"
#include "QueryProcessorTypes.h"
#include "util/ast/AssignNode.h"
#include "util/ast/StatementNode.h"
#include "util/ast/TNode.h"
#include <list>
#include <vector>
#include <string>

namespace QPS {
    class QueryManager {
    public:
        static PKBInterface* pkb;
        void handleQuery(PKBInterface* pkb, std::string queryString, std::list<std::string>& results);

        static void setPKBInterface(PKBInterface *pkb) {
            QueryManager::pkb = pkb;
        }

        /**
         * Call PKB interface to get all the names of entity of a certain type.
         *
         * @return A vector of string.
         */
        static std::vector<std::string> getAllEntitiesFromPKB(QPS::EntityType entityType) {
            return QueryManager::pkb->getAllEntity(entityType);
        }

        /**
         * Call PKB interface to get the AST TNode of a certain assign statement.
         *
         * @param assignRef The statement reference.
         * @return A pointer of AST TNode.
         */
        static std::shared_ptr<AssignNode> getAssignTNode(std::string assignRef) {
            return QueryManager::pkb->getAssignTNode(assignRef);
        }

        /**
         * Call PKB interface to check whether a certain type is present in the SIMPLE source code.
         * @param relationStruct The given type to check.
         * @return bool.
         */
        static bool isRelationExist(const RelationStruct& relationStruct) {
            return QueryManager::pkb->existRelation(relationStruct);
        }

        static vector<string> getAllAssigns() {
            return {};
        }

    };

}

#endif //SPA_QUERYMANAGER_H