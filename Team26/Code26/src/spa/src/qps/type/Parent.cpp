#include "Parent.h"

const std::unordered_set<ArgumentType> StmtSet {
        STMT_SYNONYM,
        IF_SYNONYM,
        WHILE_SYNONYM,
        READ_SYNONYM,
        PRINT_SYNONYM,
        CALL_SYNONYM,
        ASSIGN_SYNONYM,
        NUMBER
};

const std::unordered_map<ArgumentType, std::unordered_set<ArgumentType>> Parent::validationTable {
        {STMT_SYNONYM, StmtSet},
        {IF_SYNONYM, StmtSet},
        {WHILE_SYNONYM, StmtSet},
        {READ_SYNONYM, StmtSet},
        {PRINT_SYNONYM, StmtSet},
        {CALL_SYNONYM, StmtSet},
        {ASSIGN_SYNONYM, StmtSet},
        {NUMBER, StmtSet}
};