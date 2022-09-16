#include "QueryStruct.h"

namespace QPS {
    QueryStruct::QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                             SUCH_THAT_LIST &suchThatList,
                             PATTERN_LIST &patternList,
                             CANDIDATE_LIST &candidateList) :
            declaredSynonymMap(declaredSynonymMap),
            suchThatList(suchThatList),
            patternList(patternList),
            candidateList(candidateList) {
        this->generateUsedSynonymList();
    }

    QueryStruct::QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                             SUCH_THAT_LIST &suchThatList,
                             CANDIDATE_LIST &candidateList) :
            declaredSynonymMap(declaredSynonymMap),
            suchThatList(suchThatList),
            candidateList(candidateList) {
        this->generateUsedSynonymList();
    }

    QueryStruct::QueryStruct(DECLARED_SYNONYM_MAP &declaredSynonymMap,
                             PATTERN_LIST &patternList,
                             CANDIDATE_LIST &candidateList) :
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

    void QueryStruct::addSynonym(EntityType entityType, std::string nameOfEntity) {
        if (this->declaredSynonymMap.find(nameOfEntity) != this->declaredSynonymMap.end()) {
            if (this->declaredSynonymMap.find(nameOfEntity)->second != entityType) {
                this->queryStatus = EVALUATION_ERROR;
                throw std::invalid_argument("QueryStruct::addSynonym: Synonym "
                                            + nameOfEntity
                                            + "already exists and the type is different.");
            }
        } else {
            this->declaredSynonymMap.insert(std::make_pair(nameOfEntity, entityType));
        }
    }

    void QueryStruct::addSuchThatClause(RelationStruct relationToAdd) {
        this->suchThatList.emplace_back(relationToAdd);
        if (QPS::isArgumentTypeSynonym(relationToAdd.arg1.typeOfArgument)) {
            this->addUsedSynonym(relationToAdd.arg1.nameOfArgument);
        }
        if (QPS::isArgumentTypeSynonym(relationToAdd.arg2.typeOfArgument)) {
            this->addUsedSynonym(relationToAdd.arg2.nameOfArgument);
        }
    }

    void QueryStruct::addPatternClause(PatternStruct patternToAdd) {
        this->patternList.emplace_back(patternToAdd);
        this->addUsedSynonym(patternToAdd.assign_syn);
        if (QPS::isArgumentTypeSynonym(patternToAdd.arg1.typeOfArgument)) {
            this->addUsedSynonym(patternToAdd.arg1.nameOfArgument);
        }
        if (QPS::isArgumentTypeSynonym(patternToAdd.arg2.typeOfArgument)) {
            this->addUsedSynonym(patternToAdd.arg2.nameOfArgument);
        }
    }

    void QueryStruct::addCandidate(CandidateStruct candidateToAdd) {
        this->candidateList.emplace_back(candidateToAdd);
        this->addUsedSynonym(candidateToAdd.entityOfCandidate.nameOfEntity);
    }

    void QueryStruct::addUsedSynonym(std::string nameOfSynonym) {
        this->usedSynonymList.insert(nameOfSynonym);
    }

    void QueryStruct::generateUsedSynonymList() {
        for (auto candidate : this->candidateList) {
            this->addUsedSynonym(candidate.entityOfCandidate.nameOfEntity);
        }
        for (auto relation: this->suchThatList) {
            if (QPS::isArgumentTypeSynonym(relation.arg1.typeOfArgument)) {
                this->addUsedSynonym(relation.arg1.nameOfArgument);
            }
            if (QPS::isArgumentTypeSynonym(relation.arg2.typeOfArgument)) {
                this->addUsedSynonym(relation.arg2.nameOfArgument);
            }
        }
        for (auto pattern: this->patternList) {
            this->addUsedSynonym(pattern.assign_syn);
            if (QPS::isArgumentTypeSynonym(pattern.arg1.typeOfArgument)) {
                this->addUsedSynonym(pattern.arg1.nameOfArgument);
            }
            if (QPS::isArgumentTypeSynonym(pattern.arg2.typeOfArgument)) {
                this->addUsedSynonym(pattern.arg2.nameOfArgument);
            }
        }
    }

    bool QueryStruct::isSynonymUsed(std::string nameOfSynonym) {
        if (this->usedSynonymList.find(nameOfSynonym) != this->usedSynonymList.end()) {
            return true;
        } else {
            return false;
        }
    }
}
