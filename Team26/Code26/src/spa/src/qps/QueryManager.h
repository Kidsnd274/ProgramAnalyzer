#ifndef SPA_QUERYMANAGER_H
#define SPA_QUERYMANAGER_H

#include "Tokenizer.h"
#include "QueryStruct.h"
#include "pkb/PKBInterface.h"
#include "QueryProcessorTypes.h"
#include <list>
#include <vector>
#include <string>

namespace QPS {
    enum Status{
        INITIALIZED,
        START_PARSE_DECLARATION,
        FINISH_PARSE_DECLARATION,
        START_PARSE_SELECT,
        FINISH_PARSE_SELECT,
        START_PARSE_SUCH,
        FINISH_PARSE_SUCH,
    };

    class Container {
    private:
        std::vector<QPS::Token> tokens;
        QueryStruct queryStruct;
        Status status;

    public:
        Container() = default;

        explicit Container(std::vector<QPS::Token>& tokens) {
            DECLARED_SYNONYM_MAP declaredSynonymMap;
            SUCH_THAT_LIST suchThatList;
            CANDIDATE_LIST candidateList;
            PATTERN_LIST patternList;
            this->tokens = tokens;
            this->queryStruct = QueryStruct(declaredSynonymMap, suchThatList, patternList, candidateList);
            this->status = INITIALIZED;
        }

        Status getStatus() {
            return this->status;
        }

        void setStatus(Status status1) {
            this->status = status1;
        }

        void addDeclaration(EntityType entityType, std::string s) {
            this->queryStruct.addSynonym(entityType, s);
        }

        void addCandidateList(EntityType entityType, std::string s) {
            CandidateType candidateType = mapEntityToCandidate(entityType);
            this->queryStruct.addCandidateList(candidateType, std::move(s), entityType);
        }

        void addSuchThatClause(RelationType relationType, ArgumentStruct ARG1, ArgumentStruct ARG2) {
            RelationStruct relationStruct = {relationType, std::move(ARG1), std::move(ARG2)};
            this->queryStruct.addSuchThatClause(relationStruct);
        }

        void addPatternClause(PatternType typeOfPattern, std::string assign_syn, ArgumentStruct arg1, ArgumentStruct arg2) {
            PatternStruct patternStruct = {typeOfPattern, std::move(assign_syn),std::move(arg1),std::move(arg2)};
            this->queryStruct.addPatternClause(patternStruct);
        }

        DECLARED_SYNONYM_MAP getDeclarationMap() {
            return this->queryStruct.getDeclaredSynonymMap();
        }

        CANDIDATE_LIST  getCandidateList(){
            return this->queryStruct.getCandidateList();
        }

        SUCH_THAT_LIST getSuchThatList() {
            return this->queryStruct.getSuchThatList();
        }

        PATTERN_LIST getPatternList() {
            return this->queryStruct.getPatternList();
        }

        QueryStruct getQueryStruct() {
            return this->queryStruct;
        }
    };

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
        static std::shared_ptr<TNode> getAssignTNode(std::string assignRef) {
//            return QueryManager::pkb->getAssignTNode(assignRef);
        }

        /**
         * Call PKB interface to check whether a certain relation is present in the SIMPLE source code.
         *
         * @param relationStruct The given relation to check.
         * @return bool.
         */
        static bool isRelationExist(RelationStruct relationStruct) {
//            return QueryManager::pkb->isRelationExist(relationStruct);
        }
    };

}

#endif //SPA_QUERYMANAGER_H
