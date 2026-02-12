/*
author          Oliver Blaser
date            12.02.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "util/version.h"

#include "catch2/catch.hpp"



TEST_CASE("version.h UTIL_semver_clear()")
{
    UTIL_semver_t ___v;
    UTIL_semver_t* v = &___v;

    v->major = 1;
    v->minor = 2;
    v->patch = 3;
    v->prCount = 4;
    v->buildCount = 5;

    UTIL_semver_clear(v);

    CHECK(v->major == 0);
    CHECK(v->minor == 0);
    CHECK(v->patch == 0);
    CHECK(v->prCount == 0);
    CHECK(v->buildCount == 0);
}
