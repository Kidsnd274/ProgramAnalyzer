#include "qps/type/Uses.h"
#include "catch.hpp"

TEST_CASE("Uses Validation Test - uses(assign, var) - valid") {
    Argument arg1 = Argument("arg1", Argument::ASSIGN_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(assign, \"varName\") - valid") {
    Argument arg1 = Argument("arg1", Argument::ASSIGN_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::ACTUAL_NAME);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(print, var) - valid") {
    Argument arg1 = Argument("arg1", Argument::PRINT_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(print, \"varName\") - valid") {
    Argument arg1 = Argument("arg1", Argument::PRINT_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::ACTUAL_NAME);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(if, var) - valid") {
    Argument arg1 = Argument("arg1", Argument::IF_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(if, \"varName\") - valid") {
    Argument arg1 = Argument("arg1", Argument::IF_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::ACTUAL_NAME);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(while, var) - valid") {
    Argument arg1 = Argument("arg1", Argument::WHILE_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(while, \"varName\") - valid") {
    Argument arg1 = Argument("arg1", Argument::WHILE_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::ACTUAL_NAME);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(call, var) - valid") {
    Argument arg1 = Argument("arg1", Argument::CALL_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(call, \"varName\") - valid") {
    Argument arg1 = Argument("arg1", Argument::CALL_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::ACTUAL_NAME);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(procedure, var) - valid") {
    Argument arg1 = Argument("arg1", Argument::PROCEDURE_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(procedure, \"varName\") - valid") {
    Argument arg1 = Argument("arg1", Argument::PROCEDURE_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::ACTUAL_NAME);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(\"procedureName\", var) - valid") {
    Argument arg1 = Argument("arg1", Argument::ACTUAL_NAME);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(\"procedureName\", \"varName\") - valid") {
    Argument arg1 = Argument("arg1", Argument::ACTUAL_NAME);
    Argument arg2 = Argument("arg2", Argument::ACTUAL_NAME);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(number, var) - valid") {
    Argument arg1 = Argument("arg1", Argument::NUMBER);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

TEST_CASE("Uses Validation Test - uses(number, \"varName\") - valid") {
    Argument arg1 = Argument("arg1", Argument::NUMBER);
    Argument arg2 = Argument("arg2", Argument::ACTUAL_NAME);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == true);
}

// Negative testcases
// uses(_, var) or uses(_, "varName")
TEST_CASE("Uses Validation Test - uses(stmt, var) - invalid") {
    Argument arg1 = Argument("arg1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == false);
}

TEST_CASE("Uses Validation Test - uses(stmt, \"varName\") - invalid") {
    Argument arg1 = Argument("arg1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::ACTUAL_NAME);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == false);
}

TEST_CASE("Uses Validation Test - uses(var, var) - invalid") {
    Argument arg1 = Argument("arg1", Argument::VAR_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == false);
}

TEST_CASE("Uses Validation Test - uses(var, \"varName\") - invalid") {
    Argument arg1 = Argument("arg1", Argument::VAR_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::ACTUAL_NAME);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == false);
}

// Negative testcases
// uses(_, stmt)
TEST_CASE("Uses Validation Test - uses(stmt, if) - invalid") {
    Argument arg1 = Argument("arg1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::IF_SYNONYM);
    Uses uses1 = Uses(arg1, arg2);
    REQUIRE(uses1.isValid() == false);
}
