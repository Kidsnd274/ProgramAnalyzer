#ifndef SPA_CONTAINER_H
#define SPA_CONTAINER_H

#include "Tokenizer.h"
#include "qps/query.h"
#include "qps/type/Entity.h"
#include "qps/type/PatternClause.h"
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

        void addPatternClause(Argument::ArgumentType typeOfPattern, std::string pattern_syn, Argument arg1, Argument arg2) {
            Argument arg = Argument(pattern_syn, typeOfPattern);
            PatternClause patternClause = PatternClause(arg, arg1, arg2);
            this->queryStruct.addClause(patternClause);
        }

        void addWithClause (const WithStruct& withStruct) {
            this->queryStruct.addWithClause(withStruct);
        }

        unordered_map<std::string, Argument> getDeclarationMap() {
            return this->queryStruct.getSynonymMap();
        }

        Argument::ArgumentType getSynonymType(std::string synonym) {
            return this->queryStruct.getSynonymType(synonym);
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
