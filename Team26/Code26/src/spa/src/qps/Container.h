#ifndef SPA_CONTAINER_H
#define SPA_CONTAINER_H

#include "Tokenizer.h"
#include "qps/query.h"
#include "qps/type/Entity.h"
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
        START_PARSE_SUCH_CLAUSE,
        FINISH_PARSE_SUCH_CLAUSE,
        START_PARSE_PATTERN_CLAUSE,
        FINISH_PARSE_PATTERN_CLAUSE,
        START_PARSE_WITH_CLAUSE,
        FINISH_PARSE_WITH_CLAUSE
    };

    class Container {
    private:
        std::vector<QPS::Token> tokens;
        Query queryStruct;
        Status status;

    public:
        Container() = default;

        explicit Container(std::vector<QPS::Token> &tokens) {
            DECLARED_SYNONYM_MAP declaredSynonymMap;
            SUCH_THAT_LIST suchThatList;
            CANDIDATE_LIST candidateList;
            PATTERN_LIST patternList;
            WITH_LIST withList;
            this->tokens = tokens;
            this->queryStruct = Query();
            this->status = INITIALIZED;
        }

        Status getStatus() {
            return this->status;
        }

        void setStatus(Status status1) {
            this->status = status1;
        }

        void addDeclaration(Entity::EntityType entityType, std::string s) {
            Argument::ArgumentType argumentType = Entity::mapToArgument(entityType);
            Argument argument = Argument(s, argumentType);
            this->queryStruct.addSynonym(argument);
        }

        void addCandidateList(Argument::ArgumentType argumentType, std::string s) {
            Argument argument = Argument(s, argumentType);
            this->queryStruct.addCandidate(argument);
        }

        void addCandidateListBoolean() {
            Argument argument = Argument("boolean", Argument::BOOLEAN);
            this->queryStruct.addCandidate(argument);
        }

        void addSuchThatClause(RelationType relationType, Argument ARG1, Argument ARG2) {
            RelationStruct relationStruct = {relationType, std::move(ARG1), std::move(ARG2)};

            this->queryStruct.addSuchThatClause(relationStruct);
        }

        void addPatternClause(PatternType typeOfPattern, std::string assign_syn, Argument arg1, Argument arg2) {
            PatternStruct patternStruct = {typeOfPattern, std::move(assign_syn), std::move(arg1), std::move(arg2)};
            this->queryStruct.addPatternClause(patternStruct);
        }

        void addWithClause (const WithStruct& withStruct) {
            this->queryStruct.addWithClause(withStruct);
        }

        DECLARED_SYNONYM_MAP getDeclarationMap() {
            return this->queryStruct.getDeclaredSynonymMap();
        }

        CANDIDATE_LIST getCandidateList() {
            return this->queryStruct.getCandidateList();
        }

        SUCH_THAT_LIST getSuchThatList() {
            return this->queryStruct.getSuchThatList();
        }

        PATTERN_LIST getPatternList() {
            return this->queryStruct.getPatternList();
        }

        Query getQueryStruct() {
            return this->queryStruct;
        }
    };
}


#endif //SPA_CONTAINER_H
