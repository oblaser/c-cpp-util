/*
author          Oliver Blaser
date            18.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_TEST_UNIT_MACROS_H
#define IG_TEST_UNIT_MACROS_H

#include <cstddef>
#include <cstdint>
#include <ctime>
#include <string>

#include "util/macros.h"

#include "catch2/catch.hpp"



#define LITERAL_THREE         3
#define VALUE_IDX             1
#define VALUE1                (1)
#define VALUE1ABC             (2)
#define VALUE3                (3)
#define VALUE3ABC             (4)
#define VALUELITERAL_THREE    (5)
#define VALUELITERAL_THREEABC (6)

TEST_CASE("macros.h PP_CAT")
{
    int value;



    value = PP_CAT(VALUE, VALUE_IDX);
    CHECK(value == 1);

    value = PP_CAT3(VALUE, VALUE_IDX, ABC);
    CHECK(value == 2);

    value = PP_CAT4(VA, LUE, LITERAL_THREE, ABC);
    CHECK(value == 4);



    value = PP_CAT_NX(VALUE, LITERAL_THREE);
    CHECK(value == 5);

    value = PP_CAT3_NX(VALUE, LITERAL_THREE, ABC);
    CHECK(value == 6);

    value = PP_CAT4_NX(VA, L, UE, LITERAL_THREE);
    CHECK(value == 5);
}

TEST_CASE("macros.h PP_STR")
{
    std::string string;



    string = PP_STR(asdf);
    CHECK(string == "asdf");

    string = PP_STR(LITERAL_THREE);
    CHECK(string == "3");

    string = PP_STR(VALUE1);
    CHECK(string == "(1)");



    string = PP_STR_NX(qwertz);
    CHECK(string == "qwertz");

    string = PP_STR_NX(LITERAL_THREE);
    CHECK(string == "LITERAL_THREE");
}

#undef LITERAL_THREE
#undef VALUE_IDX
#undef VALUE1
#undef VALUE1ABC
#undef VALUE3
#undef VALUE3ABC
#undef VALUELITERAL_THREE
#undef VALUELITERAL_THREEABC



TEST_CASE("macros.h SIZEOF_ARRAY")
{
    constexpr size_t arraySize = 5;

    char c[arraySize];
    uint32_t ui32[arraySize];
    long long ll[arraySize];
    struct timespec ts[arraySize];

    CHECK(SIZEOF_ARRAY(c) == arraySize);
    CHECK(SIZEOF_ARRAY(ui32) == arraySize);
    CHECK(SIZEOF_ARRAY(ll) == arraySize);
    CHECK(SIZEOF_ARRAY(ts) == arraySize);
}



#endif // IG_TEST_UNIT_MACROS_H
