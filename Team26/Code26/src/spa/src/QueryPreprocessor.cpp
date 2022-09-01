#include <map>
#include <utility>
#include "Tokenizer.h"
#include "QueryProcessorTypes.h"
#include "QueryPreprocessor.h"
#include "QueryStruct.h"
#include "QueryProcessorTypes.h"

namespace QueryPreprocessor{
    class Container {
        std::vector<Tokenization::Token> tokens;
//        QueryProcessorTypes::DECLARED_SYNONYM_MAP declaredSynonymMap;
//        QueryProcessorTypes::SUCH_THAT_LIST suchThatList;
//        QueryProcessorTypes::CANDIDATE_LIST candidateList;
//        QueryProcessorTypes::PATTERN_LIST patternList;
        QueryStruct queryStruct;



    public:
        Container() = default;
        explicit Container(std::vector<Tokenization::Token>& tokens) {
            QueryProcessorTypes::DECLARED_SYNONYM_MAP declaredSynonymMap;
            QueryProcessorTypes::SUCH_THAT_LIST suchThatList;
            QueryProcessorTypes::CANDIDATE_LIST candidateList;
            QueryProcessorTypes::PATTERN_LIST patternList;
            this->tokens = tokens;
            this->queryStruct = QueryStruct(declaredSynonymMap, suchThatList, patternList, candidateList);
        }
    };
    void parseToken(std::vector<Tokenization::Token> &tokens) {
        Container container = Container(tokens);

        for (Tokenization::Token token : tokens) {
            std::pair<QueryProcessorTypes::EntityType, bool> entityMappingResult = mapEntity(token);
            std::pair<QueryProcessorTypes::RelationType, bool> relationMappingResult = mapRelation(token);
            if (entityMappingResult.second) {
                // Valid entity
                switch (entityMappingResult.first) {
                    case QueryProcessorTypes::STATEMENT:
                    case QueryProcessorTypes::READ:
                    case QueryProcessorTypes::PRINT:
                    case QueryProcessorTypes::CALL:
                    case QueryProcessorTypes::WHILE:
                    case QueryProcessorTypes::IF:
                    case QueryProcessorTypes::ASSIGN:
                    case QueryProcessorTypes::VARIABLE:

                        break;
                    case QueryProcessorTypes::CONSTANT:
                    case QueryProcessorTypes::PROCEDURE:
                    case QueryProcessorTypes::INVALID_ENTITY_TYPE:
                        return ;
                }
            } else if (relationMappingResult.second) {
                // Valid entity
                switch (relationMappingResult.first) {
                    case QueryProcessorTypes::FOLLOWS:
                    case QueryProcessorTypes::FOLLOWS_T:
                    case QueryProcessorTypes::PARENT:
                    case QueryProcessorTypes::PARENT_T:
                    case QueryProcessorTypes::USES_S:
                    case QueryProcessorTypes::MODIFIES_S:
                    case QueryProcessorTypes::INVALID_RELATION_TYPE:
                        return;
                }

            } else {
                // Invalid entity

            }

        }
    }


    std::pair<QueryProcessorTypes::EntityType, bool> mapEntity(Tokenization::Token token) {
        if (QueryProcessorTypes::entityMap.find(token.nameValue) == QueryProcessorTypes::entityMap.end()) {
            // not found
            return {QueryProcessorTypes::INVALID_ENTITY_TYPE, false};
        } else {
            // found
            return {QueryProcessorTypes::entityMap.at(token.nameValue), true};
        }
    }

    std::pair<QueryProcessorTypes::RelationType, bool> mapRelation(Tokenization::Token token) {
        if (QueryProcessorTypes::relationMap.find(token.nameValue) == QueryProcessorTypes::relationMap.end()) {
            // not found
            return {QueryProcessorTypes::INVALID_RELATION_TYPE, false};
        } else {
            // found
            return {QueryProcessorTypes::relationMap.at(token.nameValue), true};
        }
    }




}



