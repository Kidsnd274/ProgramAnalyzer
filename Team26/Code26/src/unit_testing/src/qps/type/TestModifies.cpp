#include "qps/type/Modifies.h"
#include "catch.hpp"

TEST_CASE("Modifies Validation Test - modifies(assign, var) - valid") {
    Argument arg1 = Argument("arg1", Argument::ASSIGN_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    Modifies modifies1 = Modifies(arg1, arg2);
    REQUIRE(modifies1.isValid() == true);
}
