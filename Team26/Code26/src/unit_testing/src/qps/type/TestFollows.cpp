#include "qps/type/Follows.h"
#include "catch.hpp"

bool isSameArg(Argument arg1, Argument arg2) {
    if (arg1.argumentType != arg2.argumentType) {
        return false;
    }
    if (arg1.argumentName != arg2.argumentName) {
        return false;
    }
    return true;
}

TEST_CASE("Basic Follows Test - get first argument") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::IF_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(isSameArg(follows1.getFirstArgument(), arg1) == true);
}

TEST_CASE("Basic Follows Test - get second argument") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::IF_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(isSameArg(follows1.getSecondArgument(), arg2) == true);
}

TEST_CASE("Basic Follows Test - set first argument") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::IF_SYNONYM);
    Argument arg3 = Argument("s3", Argument::WHILE_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    follows1.setFirstArgument(arg3);
    REQUIRE(isSameArg(follows1.getFirstArgument(), arg1) == false);
    REQUIRE(isSameArg(follows1.getFirstArgument(), arg3) == true);
}

TEST_CASE("Basic Follows Test - set second argument") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::IF_SYNONYM);
    Argument arg3 = Argument("s3", Argument::WHILE_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    follows1.setSecondArgument(arg3);
    REQUIRE(isSameArg(follows1.getSecondArgument(), arg1) == false);
    REQUIRE(isSameArg(follows1.getSecondArgument(), arg3) == true);
}

// follows(stmt, _)
TEST_CASE("Follows Validation Test - follows(stmt, stmt) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == true);
}

TEST_CASE("Follows Validation Test - follows(stmt, if) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::IF_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == true);
}

TEST_CASE("Follows Validation Test - follows(stmt, while) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::WHILE_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == true);
}

TEST_CASE("Follows Validation Test - follows(stmt, read) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::READ_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == true);
}

TEST_CASE("Follows Validation Test - follows(stmt, print) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::PRINT_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == true);
}

TEST_CASE("Follows Validation Test - follows(stmt, call) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::CALL_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == true);
}

TEST_CASE("Follows Validation Test - follows(stmt, assign) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::ASSIGN_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == true);
}

TEST_CASE("Follows Validation Test - follows(stmt, number) - valid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::NUMBER);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == true);
}

// Negative testcases
TEST_CASE("Follows Validation Test - follows(stmt, var) - invalid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::VAR_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == false);
}

TEST_CASE("Follows Validation Test - follows(stmt, prod) - invalid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::PROCEDURE_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == false);
}

TEST_CASE("Follows Validation Test - follows(stmt, const) - invalid") {
    Argument arg1 = Argument("s1", Argument::STMT_SYNONYM);
    Argument arg2 = Argument("s2", Argument::CONST_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == false);
}

TEST_CASE("Follows Validation Test - follows(var, stmt) - invalid") {
    Argument arg1 = Argument("s1", Argument::VAR_SYNONYM);
    Argument arg2 = Argument("s2", Argument::STMT_SYNONYM);
    Follows follows1 = Follows(arg1, arg2);
    REQUIRE(follows1.isValid() == false);
}