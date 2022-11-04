#include "qps/QueryEvaluator.h"
#include "catch.hpp"

#define N (20)

TEST_CASE("UFDS TEST - Positive 1") {
    UnionFindDisjointSet* ufds = new UnionFindDisjointSet(N);
    ufds->initialize();
    for (int i = 0; i < N; i++) {
        REQUIRE(ufds->find(i) == i);
    }
    REQUIRE(ufds->getNumberOfGroups() == N);
}

TEST_CASE("UFDS TEST - Positive 2") {
    UnionFindDisjointSet* ufds = new UnionFindDisjointSet(N);
    ufds->initialize();
    for (int i = 0; i < N; i++) {
        ufds->merge(0, i);
    }
    for (int i = 0; i < N; i++) {
        REQUIRE(ufds->find(i) == 0);
    }
    REQUIRE(ufds->getNumberOfGroups() == 1);
}

TEST_CASE("UFDS TEST - Positive 3") {
    UnionFindDisjointSet* ufds = new UnionFindDisjointSet(N);
    ufds->initialize();
    for (int i = 1; i < N; i++) {
        ufds->merge(i - 1, i);
    }
    for (int i = 0; i < N; i++) {
        REQUIRE(ufds->find(i) == 0);
    }
    REQUIRE(ufds->getNumberOfGroups() == 1);
}
