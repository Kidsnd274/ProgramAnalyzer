#ifndef SPA_CONTAINER_H
#define SPA_CONTAINER_H

#include "Tokenizer.h"
#include "qps/Query.h"
#include "qps/type/Entity.h"
#include "qps/type/PatternClause.h"
#include "qps/type/RelationClause.h"
#include "qps/type/WithClause.h"
#include "qps/type/Follows.h"
#include "qps/type/FollowStar.h"
#include "qps/type/Parent.h"
#include "qps/type/ParentStar.h"
#include "qps/type/Uses.h"
#include "qps/type/ParentStar.h"
#include "qps/type/Modifies.h"
#include "qps/type/Calls.h"
#include "qps/type/CallsStar.h"
#include "qps/type/Next.h"
#include "qps/type/NextStar.h"
#include "qps/type/Affects.h"
#include "qps/type/AffectsStar.h"
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

        explicit Container(std::vector<QPS::Token> &tokens) : queryStruct(Query()) {
            this->tokens = tokens;
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
            Argument argument = Argument("boolean", Argument::BOOLEAN_ARG);
            this->queryStruct.addCandidate(argument);
        }

        void addSuchThatClause(RelationType relationType, Argument arg1, Argument arg2) {
            switch (relationType) {
                case FOLLOWS: {
                    Follows* clause = new Follows(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case FOLLOWS_T:{
                    FollowStar* clause = new FollowStar(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case PARENT:{
                    Parent* clause = new Parent(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case PARENT_T:{
                    ParentStar* clause = new ParentStar(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case USES_S:{
                    Uses* clause = new Uses(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case MODIFIES_S:{
                    Modifies* clause = new Modifies(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case USES_P:{
                    Uses* clause = new Uses(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case MODIFIES_P:{
                    Modifies* clause = new Modifies(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case CALLS:{
                    Calls* clause = new Calls(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case CALLS_T:{
                    CallsStar* clause = new CallsStar(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case NEXT:{
                    Next* clause = new Next(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case NEXT_T:{
                    NextStar* clause = new NextStar(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case AFFECTS:{
                    Affects* clause = new Affects(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case AFFECTS_T:{
                    AffectsStar* clause = new AffectsStar(arg1, arg2);
                    this->queryStruct.addClause(clause);
                    break;
                }
                case INVALID_RELATION_TYPE:
                    break;
            }

        }

        void addPatternClause(Argument::ArgumentType typeOfPattern, std::string pattern_syn, Argument arg1, Argument arg2) {
            Argument arg = Argument(pattern_syn, typeOfPattern);
            PatternClause* patternClause = new PatternClause(arg, arg1, arg2);
            this->queryStruct.addClause(patternClause);
        }

        void addWithClause (WithClause::WithClauseArgument arg1, WithClause::WithClauseArgument arg2) {
            WithClause* withClause = new WithClause(arg1, arg2);
            this->queryStruct.addClause(withClause);
        }

        std::unordered_map<std::string, Argument> getDeclarationMap() {
            return this->queryStruct.getSynonymMap();
        }

        Argument::ArgumentType getSynonymType(std::string synonym) {
            return this->queryStruct.getSynonymType(synonym);
        }


        Query getQueryStruct() {
            return this->queryStruct;
        }
    };
}


#endif //SPA_CONTAINER_H
