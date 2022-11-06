#include "qps/type/ModifiesUses.h"
#include "catch.hpp"

TEST_CASE("Modifies Validation Test - modifies(assign, var) - valid") {
    Argument arg1 = Argument("arg1", Argument::ASSIGN_SYNONYM);
    Argument arg2 = Argument("arg2", Argument::VAR_SYNONYM);
    ModifiesUses modifies1 = ModifiesUses(arg1, arg2, MODIFIES_S);
    REQUIRE(modifies1.isValid() == true);
}
