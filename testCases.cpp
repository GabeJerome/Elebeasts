#include "header.h"
#include "catch.hpp"

TEST_CASE("random_device test")
{
    std::random_device hit;
    unsigned int min, max, val;
    bool pass = false;
    int i;

    min = 1;
    max = 100;

    for (i = 0; i < 100; i++)
    {
        val = hit() % 101;

        if (val <= max && val >= min)
            pass = true;

        REQUIRE(pass);
    }
}