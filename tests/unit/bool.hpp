/*
author          Oliver Blaser
date            03.12.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_TEST_UNIT_BOOL_HPP
#define IG_TEST_UNIT_BOOL_HPP

#include <typeinfo>

#include "util/bool.h"

#include "bool.h"
#include "catch2/catch.hpp"



TEST_CASE("bool.h constants/literals")
{
    CHECK(getValue_UTIL_false() == 0);
    CHECK(getValue_UTIL_true() == 1);
    CHECK(getValue_false() == 0);
    CHECK(getValue_true() == 1);

    CHECK_FALSE(getValue_UTIL_false());
    CHECK_FALSE(getValue_false());

    CHECK(getValue_UTIL_true());
    CHECK(getValue_true());
}

TEST_CASE("bool.h types")
{
    CHECK(typeid(UTIL_bool_t) == typeid(int));
    CHECK(typeid(bool_t) == typeid(int));

    bool_t r;



    const int64_t offset = INT64_MIN + INT32_MAX;
    int64_t line = (offset + __LINE__);
    line += 2;
    r = (line == (offset + __LINE__));

    CHECK(r);
    CHECK_FALSE(!r);



    uint8_t a = 0xAA;
    uint8_t b = 0x55;

    r = (a & 0x08);
    CHECK((bool)r == true);
    CHECK(r == 0x08);
    if (r) { CHECK(true); }
    else { CHECK(false); }
    if (!r) { CHECK(false); }
    else { CHECK(true); }

    r = (a & b);
    CHECK((bool)r == false);
    CHECK(r == 0);
    if (r) { CHECK(false); }
    else { CHECK(true); }
    if (!r) { CHECK(true); }
    else { CHECK(false); }
}



#endif // IG_TEST_UNIT_BOOL_HPP
