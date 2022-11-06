#include "qps/type/Parent.h"
#include "catch.hpp"

// parent(stmt, _)
TEST_CASE("Parent Validation Test - parent(stmt, stmt) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(stmt, if) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::IF_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(stmt, while) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::WHILE_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(stmt, read) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::READ_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(stmt, call) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::CALL_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(stmt, assign) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::ASSIGN_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(stmt, number) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::NUMBER);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

// parent(if, _)
TEST_CASE("Parent Validation Test - parent(if, stmt) - valid") {
    Argument arg1 = Argument("s1", Argument::IF_SYNONYM);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(if, if) - valid") {
    Argument arg1 = Argument("s1", Argument::IF_SYNONYM);
    Argument arg2 = Argument("s2", Argument::IF_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(if, while) - valid") {
    Argument arg1 = Argument("s1", Argument::IF_SYNONYM);
    Argument arg2 = Argument("s2", Argument::WHILE_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(if, read) - valid") {
    Argument arg1 = Argument("s1", Argument::IF_SYNONYM);
    Argument arg2 = Argument("s2", Argument::READ_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(if, print) - valid") {
    Argument arg1 = Argument("s1", Argument::IF_SYNONYM);
    Argument arg2 = Argument("s2", Argument::PRINT_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(if, call) - valid") {
    Argument arg1 = Argument("s1", Argument::IF_SYNONYM);
    Argument arg2 = Argument("s2", Argument::CALL_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(if, assign) - valid") {
    Argument arg1 = Argument("s1", Argument::IF_SYNONYM);
    Argument arg2 = Argument("s2", Argument::ASSIGN_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(if, number) - valid") {
    Argument arg1 = Argument("s1", Argument::IF_SYNONYM);
    Argument arg2 = Argument("s2", Argument::NUMBER);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

// parent(while, _)
TEST_CASE("Parent Validation Test - parent(while, stmt) - valid") {
    Argument arg1 = Argument("s1", Argument::WHILE_SYNONYM);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

// parent(read, _)
TEST_CASE("Parent Validation Test - parent(read, stmt) - valid") {
    Argument arg1 = Argument("s1", Argument::READ_SYNONYM);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

// parent(print, _)
TEST_CASE("Parent Validation Test - parent(print, stmt) - valid") {
    Argument arg1 = Argument("s1", Argument::PRINT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

// parent(call, _)
TEST_CASE("Parent Validation Test - parent(call, stmt) - valid") {
    Argument arg1 = Argument("s1", Argument::CALL_SYNONYM);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

// parent(assign, _)
TEST_CASE("Parent Validation Test - parent(assign, stmt) - valid") {
    Argument arg1 = Argument("s1", Argument::ASSIGN_SYNONYM);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

// parent(number, _)
TEST_CASE("Parent Validation Test - parent(number, stmt) - valid") {
    Argument arg1 = Argument("s1", Argument::NUMBER);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

TEST_CASE("Parent Validation Test - parent(number, number) - valid") {
    Argument arg1 = Argument("s1", Argument::NUMBER);
    Argument arg2 = Argument("s2", Argument::NUMBER);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == true);
}

// Negative testcases
TEST_CASE("Parent Validation Test - parent(stmt, var) - invalid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::VAR_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == false);
}

TEST_CASE("Parent Validation Test - parent(stmt, prod) - invalid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::PROCEDURE_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == false);
}

TEST_CASE("Parent Validation Test - parent(stmt, const) - invalid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::CONST_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == false);
}

TEST_CASE("Parent Validation Test - parent(var, stmt) - invalid") {
    Argument arg1 = Argument("s1", Argument::VAR_SYNONYM);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Parent parent1 = Parent(arg1, arg2, PARENT);
    REQUIRE(parent1.isValid() == false);
}