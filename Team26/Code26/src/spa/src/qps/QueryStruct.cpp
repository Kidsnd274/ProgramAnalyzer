#include "QueryStruct.h"

namespace QPS {
    QueryStruct::QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                             SUCH_THAT_LIST &suchThatList,
                             PATTERN_LIST &patternList,
                             CANDIDATE_LIST &candidateList,
                             WITH_LIST & withList) :
            declaredSynonymMap(declaredSynonymMap),
            patternList(patternList),
            candidateList(candidateList) {
                this->generateUsedSynonymList();
            }


    QueryStruct::QueryStruct() {
        this->declaredSynonymMap = DECLARED_SYNONYM_MAP();
        this->suchThatList = SUCH_THAT_LIST();
        this->patternList = PATTERN_LIST();
        this->candidateList = CANDIDATE_LIST();
        this->withList = WITH_LIST();
    }

    DECLARED_SYNONYM_MAP QueryStruct::getDeclaredSynonymMap() {
        return this->declaredSynonymMap;
    }

    SUCH_THAT_LIST QueryStruct::getSuchThatList() {
        return this->suchThatList;
    }

    PATTERN_LIST QueryStruct::getPatternList() {
        return this->patternList;
    }

    CANDIDATE_LIST QueryStruct::getCandidateList() {
        return this->candidateList;
    }

    WITH_LIST QueryStruct::getWithList() {
        return this->withList;
    }

    void QueryStruct::addSynonym(EntityType entityType, const std::string& nameOfEntity) {
        if (this->declaredSynonymMap.find(nameOfEntity) != this->declaredSynonymMap.end()) {
            this->queryStatus = SEMANTIC_ERROR;
        } else {
            this->declaredSynonymMap.insert(std::make_pair(nameOfEntity, entityType));
        }
    }

    void QueryStruct::addWithClause(const WithStruct& withStruct) {
        this->withList.emplace_back(withStruct);
        this->addUsedSynonym(withStruct.first_name);
        this->addUsedSynonym(withStruct.second_name);
    }

    void QueryStruct::addSuchThatClause(const RelationStruct& relationToAdd) {
        this->suchThatList.emplace_back(relationToAdd);
        if (QPS::isArgumentTypeSynonym(relationToAdd.arg1.typeOfArgument)) {
            this->addUsedSynonym(relationToAdd.arg1.nameOfArgument);
        }
        if (QPS::isArgumentTypeSynonym(relationToAdd.arg2.typeOfArgument)) {
            this->addUsedSynonym(relationToAdd.arg2.nameOfArgument);
        }
    }

    void QueryStruct::addPatternClause(const PatternStruct& patternToAdd) {
        this->patternList.emplace_back(patternToAdd);
        this->addUsedSynonym(patternToAdd.assign_syn);
        if (QPS::isArgumentTypeSynonym(patternToAdd.arg1.typeOfArgument)) {
            this->addUsedSynonym(patternToAdd.arg1.nameOfArgument);
        }
        if (QPS::isArgumentTypeSynonym(patternToAdd.arg2.typeOfArgument)) {
            this->addUsedSynonym(patternToAdd.arg2.nameOfArgument);
        }
    }

    void QueryStruct::addCandidate(const CandidateStruct& candidateToAdd) {
        this->candidateList.emplace_back(candidateToAdd);
        this->addUsedSynonym(candidateToAdd.entityOfCandidate.nameOfEntity);
    }

    void QueryStruct::addUsedSynonym(const std::string& nameOfSynonym) {
        this->usedSynonymList.insert(nameOfSynonym);
    }

    void QueryStruct::generateUsedSynonymList() {
        for (const auto& candidate : this->candidateList) {
            this->addUsedSynonym(candidate.entityOfCandidate.nameOfEntity);
        }
        for (const auto& relation: this->suchThatList) {
            if (QPS::isArgumentTypeSynonym(relation.arg1.typeOfArgument)) {
                this->addUsedSynonym(relation.arg1.nameOfArgument);
            }
            if (QPS::isArgumentTypeSynonym(relation.arg2.typeOfArgument)) {
                this->addUsedSynonym(relation.arg2.nameOfArgument);
            }
        }
        for (const auto& pattern: this->patternList) {
            this->addUsedSynonym(pattern.assign_syn);
            if (QPS::isArgumentTypeSynonym(pattern.arg1.typeOfArgument)) {
                this->addUsedSynonym(pattern.arg1.nameOfArgument);
            }
            if (QPS::isArgumentTypeSynonym(pattern.arg2.typeOfArgument)) {
                this->addUsedSynonym(pattern.arg2.nameOfArgument);
            }
        }
    }

    bool QueryStruct::isSynonymUsed(const std::string& nameOfSynonym) {
        if (this->usedSynonymList.find(nameOfSynonym) != this->usedSynonymList.end()) {
            return true;
        } else {
            return false;
        }
    }

}
