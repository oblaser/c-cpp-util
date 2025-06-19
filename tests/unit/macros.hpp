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
#include <vector>

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

TEST_CASE("macros.h BIT")
{
    CHECK(BIT(0) == 1);
    CHECK(BIT(1) == 0x02);
    CHECK(BIT(7) == 0x80);
    CHECK(BIT(31) == 0x80000000);

    CHECK(BIT64(0) == 1);
    CHECK(BIT64(1) == 0x02);
    CHECK(BIT64(7) == 0x80);
    CHECK(BIT64(31) == 0x80000000);
    CHECK(BIT64(32) == 0x100000000);
    CHECK(BIT64(63) == 0x8000000000000000);
}

TEST_CASE("macros.h CLAMP MAX MIN")
{
    using value_type = int;
    constexpr size_t n = 7;
    constexpr value_type lo = 1;
    constexpr value_type hi = 5;
    const value_type input[n] = { -5, 12, -2, 0, 1, 6, 3 };
    std::vector<value_type> result_clamp(n);
    std::vector<value_type> result_max(n);
    std::vector<value_type> result_min(n);
    const std::vector<value_type> expected_clamp{ 1, 5, 1, 1, 1, 5, 3 };
    const std::vector<value_type> expected_max{ 1, 12, 1, 1, 1, 6, 3 };
    const std::vector<value_type> expected_min{ -5, 1, -2, 0, 1, 1, 1 };

    REQUIRE(((SIZEOF_ARRAY(input) == n) &&                                                             //
             (result_clamp.size() == n) && (result_max.size() == n) && (result_min.size() == n) &&     //
             (expected_clamp.size() == n) && (expected_max.size() == n) && (expected_min.size() == n)) //
            == true);

    for (size_t i = 0; i < n; ++i)
    {
        result_clamp[i] = UTIL_CLAMP(input[i], lo, hi);
        result_max[i] = UTIL_MAX(input[i], lo);
        result_min[i] = UTIL_MIN(input[i], lo);
    }

    CHECK(result_clamp == expected_clamp);
    CHECK(result_max == expected_max);
    CHECK(result_min == expected_min);
}

TEST_CASE("macros.h ROUND")
{
    CHECK(UTIL_ROUND(uint8_t, 0) == 0);
    CHECK(UTIL_ROUND(uint8_t, 12.1) == 12);
    CHECK(UTIL_ROUND(uint8_t, 12.49) == 12);
    CHECK(UTIL_ROUND(uint8_t, 12.5) == 13);
    CHECK(UTIL_ROUND(uint8_t, 12.8) == 13);

    CHECK(UTIL_ROUND(int, 0) == 0);
    CHECK(UTIL_ROUND(int, 12.1) == 12);
    CHECK(UTIL_ROUND(int, 12.49) == 12);
    CHECK(UTIL_ROUND(int, 12.5) == 13);
    CHECK(UTIL_ROUND(int, 12.8) == 13);

    CHECK(UTIL_ROUND(int, -0.0) == 0);
    CHECK(UTIL_ROUND(int, -3.1) == -3);
    CHECK(UTIL_ROUND(int, -3.49) == -3);
    CHECK(UTIL_ROUND(int, -3.5) == -4);
    CHECK(UTIL_ROUND(int, -3.8) == -4);
}

TEST_CASE("macros.h ROUNDF")
{
    CHECK(UTIL_ROUNDF(uint8_t, 0) == 0);
    CHECK(UTIL_ROUNDF(uint8_t, 12.1f) == 12);
    CHECK(UTIL_ROUNDF(uint8_t, 12.49f) == 12);
    CHECK(UTIL_ROUNDF(uint8_t, 12.5f) == 13);
    CHECK(UTIL_ROUNDF(uint8_t, 12.8f) == 13);

    CHECK(UTIL_ROUNDF(int, 0) == 0);
    CHECK(UTIL_ROUNDF(int, 12.1f) == 12);
    CHECK(UTIL_ROUNDF(int, 12.49f) == 12);
    CHECK(UTIL_ROUNDF(int, 12.5f) == 13);
    CHECK(UTIL_ROUNDF(int, 12.8f) == 13);

    CHECK(UTIL_ROUNDF(int, -0.0f) == 0);
    CHECK(UTIL_ROUNDF(int, -3.1f) == -3);
    CHECK(UTIL_ROUNDF(int, -3.49f) == -3);
    CHECK(UTIL_ROUNDF(int, -3.5f) == -4);
    CHECK(UTIL_ROUNDF(int, -3.8f) == -4);
}

#endif // IG_TEST_UNIT_MACROS_H
