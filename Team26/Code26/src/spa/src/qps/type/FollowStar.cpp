
#include "FollowStar.h"

// S1 (Major): DRY - class structure is the same as Follows.cpp -> perhaps generalise them into one single class

const std::unordered_set<Argument::ArgumentType> FollowStar::stmtSet {
        Argument::STMT_SYNONYM,
        Argument::IF_SYNONYM,
        Argument::WHILE_SYNONYM,
        Argument::READ_SYNONYM,
        Argument::PRINT_SYNONYM,
        Argument::CALL_SYNONYM,
        Argument::ASSIGN_SYNONYM,
        Argument::NUMBER,
        Argument::WILDCARD
};

const std::unordered_map<
        Argument::ArgumentType,
        std::unordered_set<Argument::ArgumentType>
> FollowStar::followStarValidationTable {
        {Argument::STMT_SYNONYM, stmtSet},
        {Argument::IF_SYNONYM, stmtSet},
        {Argument::WHILE_SYNONYM, stmtSet},
        {Argument::READ_SYNONYM, stmtSet},
        {Argument::PRINT_SYNONYM, stmtSet},
        {Argument::CALL_SYNONYM, stmtSet},
        {Argument::ASSIGN_SYNONYM, stmtSet},
        {Argument::NUMBER, stmtSet},
        {Argument::WILDCARD, stmtSet}
};

bool FollowStar::isValid() {
    auto iter = FollowStar::followStarValidationTable.find(this->argument1.argumentType);
    if (iter != FollowStar::followStarValidationTable.end()) {
        if (iter->second.find(this->argument2.argumentType) != iter->second.end()) {
            return true;
        }
    }
    return false;
}