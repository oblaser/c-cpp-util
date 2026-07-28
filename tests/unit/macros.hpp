/*
author          Oliver Blaser
date            26.03.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#ifndef IG_TEST_UNIT_MACROS_HPP
#define IG_TEST_UNIT_MACROS_HPP

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

TEST_CASE("macros.h SIZEOF_MEMBER")
{
    struct test
    {
        int8_t i8;
        int16_t i16;
        int32_t i32;
        int64_t i64;
        float f;
        double d;
        void* p;
    };

    CHECK(SIZEOF_MEMBER(struct test, i8) == 1);
    CHECK(SIZEOF_MEMBER(struct test, i16) == 2);
    CHECK(SIZEOF_MEMBER(struct test, i32) == 4);
    CHECK(SIZEOF_MEMBER(struct test, i64) == 8);
    CHECK(SIZEOF_MEMBER(struct test, f) == 4);
    CHECK(SIZEOF_MEMBER(struct test, d) == 8);
    CHECK(SIZEOF_MEMBER(struct test, p) == sizeof(ptrdiff_t));
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
    std::vector<value_type> result_max3(n - 1);
    std::vector<value_type> result_max4(n - 2);
    std::vector<value_type> result_min(n);
    std::vector<value_type> result_min3(n - 1);
    std::vector<value_type> result_min4(n - 2);
    const std::vector<value_type> expected_clamp{ 1, 5, 1, 1, 1, 5, 3 };
    const std::vector<value_type> expected_max{ 1, 12, 1, 1, 1, 6, 3 };
    const std::vector<value_type> expected_max3{ 12, 12, 1, 1, 6, 6 };
    const std::vector<value_type> expected_max4{ 12, 12, 1, 6, 6 };
    const std::vector<value_type> expected_min{ -5, 1, -2, 0, 1, 1, 1 };
    const std::vector<value_type> expected_min3{ -5, -2, -2, 0, 1, 1 };
    const std::vector<value_type> expected_min4{ -5, -2, -2, 0, 1 };

    REQUIRE(((SIZEOF_ARRAY(input) == n) &&                                                             //
             (result_clamp.size() == n) && (result_max.size() == n) && (result_min.size() == n) &&     //
             (expected_clamp.size() == n) && (expected_max.size() == n) && (expected_min.size() == n)) //
            == true);

    for (size_t i = 0; i < n; ++i)
    {
        result_clamp[i] = UTIL_CLAMP(input[i], lo, hi);

        result_max[i] = UTIL_MAX(input[i], lo);
        result_min[i] = UTIL_MIN(input[i], lo);

        if (i < (n - 1))
        {
            result_max3[i] = UTIL_MAX3(input[i], input[i + 1], lo);
            result_min3[i] = UTIL_MIN3(input[i], input[i + 1], lo);
        }

        if (i < (n - 2))
        {
            result_max4[i] = UTIL_MAX4(input[i], input[i + 1], input[i + 2], lo);
            result_min4[i] = UTIL_MIN4(input[i], input[i + 1], input[i + 2], lo);
        }
    }

    CHECK(result_clamp == expected_clamp);
    CHECK(result_max == expected_max);
    CHECK(result_max3 == expected_max3);
    CHECK(result_max4 == expected_max4);
    CHECK(result_min == expected_min);
    CHECK(result_min3 == expected_min3);
    CHECK(result_min4 == expected_min4);
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

TEST_CASE("macros.h DIV_UCEIL")
{
    CHECK(UTIL_DIV_UCEIL(0, 1) == 0);
    CHECK(UTIL_DIV_UCEIL(1, 1) == 1);
    CHECK(UTIL_DIV_UCEIL(2, 1) == 2);
    CHECK(UTIL_DIV_UCEIL(3, 1) == 3);
    CHECK(UTIL_DIV_UCEIL(12, 1) == 12);
    CHECK(UTIL_DIV_UCEIL(123, 1) == 123);
    CHECK(UTIL_DIV_UCEIL(1234, 1) == 1234);

    CHECK(UTIL_DIV_UCEIL(0, 2) == 0);
    CHECK(UTIL_DIV_UCEIL(1, 2) == 1);
    CHECK(UTIL_DIV_UCEIL(2, 2) == 1);
    CHECK(UTIL_DIV_UCEIL(3, 2) == 2);
    CHECK(UTIL_DIV_UCEIL(4, 2) == 2);
    CHECK(UTIL_DIV_UCEIL(5, 2) == 3);
    CHECK(UTIL_DIV_UCEIL(6, 2) == 3);

    CHECK(UTIL_DIV_UCEIL(0, 3) == 0);
    CHECK(UTIL_DIV_UCEIL(1, 3) == 1);
    CHECK(UTIL_DIV_UCEIL(2, 3) == 1);
    CHECK(UTIL_DIV_UCEIL(3, 3) == 1);
    CHECK(UTIL_DIV_UCEIL(4, 3) == 2);
    CHECK(UTIL_DIV_UCEIL(5, 3) == 2);
    CHECK(UTIL_DIV_UCEIL(6, 3) == 2);
    CHECK(UTIL_DIV_UCEIL(7, 3) == 3);
    CHECK(UTIL_DIV_UCEIL(8, 3) == 3);
    CHECK(UTIL_DIV_UCEIL(9, 3) == 3);
    CHECK(UTIL_DIV_UCEIL(10, 3) == 4);
    CHECK(UTIL_DIV_UCEIL(11, 3) == 4);
    CHECK(UTIL_DIV_UCEIL(12, 3) == 4);

    CHECK(UTIL_DIV_UCEIL(0, 4) == 0);
    CHECK(UTIL_DIV_UCEIL(1, 4) == 1);
    CHECK(UTIL_DIV_UCEIL(2, 4) == 1);
    CHECK(UTIL_DIV_UCEIL(3, 4) == 1);
    CHECK(UTIL_DIV_UCEIL(4, 4) == 1);
    CHECK(UTIL_DIV_UCEIL(5, 4) == 2);
    CHECK(UTIL_DIV_UCEIL(6, 4) == 2);
    CHECK(UTIL_DIV_UCEIL(7, 4) == 2);
    CHECK(UTIL_DIV_UCEIL(8, 4) == 2);
    CHECK(UTIL_DIV_UCEIL(9, 4) == 3);
    CHECK(UTIL_DIV_UCEIL(10, 4) == 3);
    CHECK(UTIL_DIV_UCEIL(11, 4) == 3);
    CHECK(UTIL_DIV_UCEIL(12, 4) == 3);
    CHECK(UTIL_DIV_UCEIL(13, 4) == 4);
    CHECK(UTIL_DIV_UCEIL(14, 4) == 4);
    CHECK(UTIL_DIV_UCEIL(15, 4) == 4);
    CHECK(UTIL_DIV_UCEIL(16, 4) == 4);
    CHECK(UTIL_DIV_UCEIL(17, 4) == 5);
    CHECK(UTIL_DIV_UCEIL(18, 4) == 5);
    CHECK(UTIL_DIV_UCEIL(19, 4) == 5);
    CHECK(UTIL_DIV_UCEIL(20, 4) == 5);
    CHECK(UTIL_DIV_UCEIL(21, 4) == 6);
    CHECK(UTIL_DIV_UCEIL(22, 4) == 6);
    CHECK(UTIL_DIV_UCEIL(23, 4) == 6);
    CHECK(UTIL_DIV_UCEIL(24, 4) == 6);
    CHECK(UTIL_DIV_UCEIL(25, 4) == 7);
    CHECK(UTIL_DIV_UCEIL(26, 4) == 7);
    CHECK(UTIL_DIV_UCEIL(27, 4) == 7);
    CHECK(UTIL_DIV_UCEIL(28, 4) == 7);
    CHECK(UTIL_DIV_UCEIL(29, 4) == 8);
    CHECK(UTIL_DIV_UCEIL(30, 4) == 8);

    CHECK(UTIL_DIV_UCEIL(0, 5) == 0);
    CHECK(UTIL_DIV_UCEIL(1, 5) == 1);
    CHECK(UTIL_DIV_UCEIL(2, 5) == 1);
    CHECK(UTIL_DIV_UCEIL(3, 5) == 1);
    CHECK(UTIL_DIV_UCEIL(4, 5) == 1);
    CHECK(UTIL_DIV_UCEIL(5, 5) == 1);
    CHECK(UTIL_DIV_UCEIL(6, 5) == 2);
    CHECK(UTIL_DIV_UCEIL(7, 5) == 2);
    CHECK(UTIL_DIV_UCEIL(8, 5) == 2);
    CHECK(UTIL_DIV_UCEIL(9, 5) == 2);
    CHECK(UTIL_DIV_UCEIL(10, 5) == 2);
    CHECK(UTIL_DIV_UCEIL(11, 5) == 3);
    CHECK(UTIL_DIV_UCEIL(12, 5) == 3);
    CHECK(UTIL_DIV_UCEIL(13, 5) == 3);
    CHECK(UTIL_DIV_UCEIL(14, 5) == 3);
    CHECK(UTIL_DIV_UCEIL(15, 5) == 3);
    CHECK(UTIL_DIV_UCEIL(16, 5) == 4);
    CHECK(UTIL_DIV_UCEIL(17, 5) == 4);
    CHECK(UTIL_DIV_UCEIL(18, 5) == 4);
    CHECK(UTIL_DIV_UCEIL(19, 5) == 4);
    CHECK(UTIL_DIV_UCEIL(20, 5) == 4);
    CHECK(UTIL_DIV_UCEIL(21, 5) == 5);
    CHECK(UTIL_DIV_UCEIL(22, 5) == 5);
    CHECK(UTIL_DIV_UCEIL(23, 5) == 5);
    CHECK(UTIL_DIV_UCEIL(24, 5) == 5);
    CHECK(UTIL_DIV_UCEIL(25, 5) == 5);
    CHECK(UTIL_DIV_UCEIL(26, 5) == 6);
    CHECK(UTIL_DIV_UCEIL(27, 5) == 6);
    CHECK(UTIL_DIV_UCEIL(28, 5) == 6);
    CHECK(UTIL_DIV_UCEIL(29, 5) == 6);
    CHECK(UTIL_DIV_UCEIL(30, 5) == 6);
}

TEST_CASE("macros.h DIV_UFLOOR")
{
    CHECK(UTIL_DIV_UFLOOR(0, 1) == 0);
    CHECK(UTIL_DIV_UFLOOR(1, 1) == 1);
    CHECK(UTIL_DIV_UFLOOR(2, 1) == 2);
    CHECK(UTIL_DIV_UFLOOR(3, 1) == 3);
    CHECK(UTIL_DIV_UFLOOR(12, 1) == 12);
    CHECK(UTIL_DIV_UFLOOR(123, 1) == 123);
    CHECK(UTIL_DIV_UFLOOR(1234, 1) == 1234);

    CHECK(UTIL_DIV_UFLOOR(0, 2) == 0);
    CHECK(UTIL_DIV_UFLOOR(1, 2) == 0);
    CHECK(UTIL_DIV_UFLOOR(2, 2) == 1);
    CHECK(UTIL_DIV_UFLOOR(3, 2) == 1);
    CHECK(UTIL_DIV_UFLOOR(4, 2) == 2);
    CHECK(UTIL_DIV_UFLOOR(5, 2) == 2);
    CHECK(UTIL_DIV_UFLOOR(6, 2) == 3);

    CHECK(UTIL_DIV_UFLOOR(0, 3) == 0);
    CHECK(UTIL_DIV_UFLOOR(1, 3) == 0);
    CHECK(UTIL_DIV_UFLOOR(2, 3) == 0);
    CHECK(UTIL_DIV_UFLOOR(3, 3) == 1);
    CHECK(UTIL_DIV_UFLOOR(4, 3) == 1);
    CHECK(UTIL_DIV_UFLOOR(5, 3) == 1);
    CHECK(UTIL_DIV_UFLOOR(6, 3) == 2);
    CHECK(UTIL_DIV_UFLOOR(7, 3) == 2);
    CHECK(UTIL_DIV_UFLOOR(8, 3) == 2);
    CHECK(UTIL_DIV_UFLOOR(9, 3) == 3);
    CHECK(UTIL_DIV_UFLOOR(10, 3) == 3);
    CHECK(UTIL_DIV_UFLOOR(11, 3) == 3);
    CHECK(UTIL_DIV_UFLOOR(12, 3) == 4);

    CHECK(UTIL_DIV_UFLOOR(0, 4) == 0);
    CHECK(UTIL_DIV_UFLOOR(1, 4) == 0);
    CHECK(UTIL_DIV_UFLOOR(2, 4) == 0);
    CHECK(UTIL_DIV_UFLOOR(3, 4) == 0);
    CHECK(UTIL_DIV_UFLOOR(4, 4) == 1);
    CHECK(UTIL_DIV_UFLOOR(5, 4) == 1);
    CHECK(UTIL_DIV_UFLOOR(6, 4) == 1);
    CHECK(UTIL_DIV_UFLOOR(7, 4) == 1);
    CHECK(UTIL_DIV_UFLOOR(8, 4) == 2);
    CHECK(UTIL_DIV_UFLOOR(9, 4) == 2);
    CHECK(UTIL_DIV_UFLOOR(10, 4) == 2);
    CHECK(UTIL_DIV_UFLOOR(11, 4) == 2);
    CHECK(UTIL_DIV_UFLOOR(12, 4) == 3);
    CHECK(UTIL_DIV_UFLOOR(13, 4) == 3);
    CHECK(UTIL_DIV_UFLOOR(14, 4) == 3);
    CHECK(UTIL_DIV_UFLOOR(15, 4) == 3);
    CHECK(UTIL_DIV_UFLOOR(16, 4) == 4);
    CHECK(UTIL_DIV_UFLOOR(17, 4) == 4);
    CHECK(UTIL_DIV_UFLOOR(18, 4) == 4);
    CHECK(UTIL_DIV_UFLOOR(19, 4) == 4);
    CHECK(UTIL_DIV_UFLOOR(20, 4) == 5);
    CHECK(UTIL_DIV_UFLOOR(21, 4) == 5);
    CHECK(UTIL_DIV_UFLOOR(22, 4) == 5);
    CHECK(UTIL_DIV_UFLOOR(23, 4) == 5);
    CHECK(UTIL_DIV_UFLOOR(24, 4) == 6);
    CHECK(UTIL_DIV_UFLOOR(25, 4) == 6);
    CHECK(UTIL_DIV_UFLOOR(26, 4) == 6);
    CHECK(UTIL_DIV_UFLOOR(27, 4) == 6);
    CHECK(UTIL_DIV_UFLOOR(28, 4) == 7);
    CHECK(UTIL_DIV_UFLOOR(29, 4) == 7);
    CHECK(UTIL_DIV_UFLOOR(30, 4) == 7);

    CHECK(UTIL_DIV_UFLOOR(0, 5) == 0);
    CHECK(UTIL_DIV_UFLOOR(1, 5) == 0);
    CHECK(UTIL_DIV_UFLOOR(2, 5) == 0);
    CHECK(UTIL_DIV_UFLOOR(3, 5) == 0);
    CHECK(UTIL_DIV_UFLOOR(4, 5) == 0);
    CHECK(UTIL_DIV_UFLOOR(5, 5) == 1);
    CHECK(UTIL_DIV_UFLOOR(6, 5) == 1);
    CHECK(UTIL_DIV_UFLOOR(7, 5) == 1);
    CHECK(UTIL_DIV_UFLOOR(8, 5) == 1);
    CHECK(UTIL_DIV_UFLOOR(9, 5) == 1);
    CHECK(UTIL_DIV_UFLOOR(10, 5) == 2);
    CHECK(UTIL_DIV_UFLOOR(11, 5) == 2);
    CHECK(UTIL_DIV_UFLOOR(12, 5) == 2);
    CHECK(UTIL_DIV_UFLOOR(13, 5) == 2);
    CHECK(UTIL_DIV_UFLOOR(14, 5) == 2);
    CHECK(UTIL_DIV_UFLOOR(15, 5) == 3);
    CHECK(UTIL_DIV_UFLOOR(16, 5) == 3);
    CHECK(UTIL_DIV_UFLOOR(17, 5) == 3);
    CHECK(UTIL_DIV_UFLOOR(18, 5) == 3);
    CHECK(UTIL_DIV_UFLOOR(19, 5) == 3);
    CHECK(UTIL_DIV_UFLOOR(20, 5) == 4);
    CHECK(UTIL_DIV_UFLOOR(21, 5) == 4);
    CHECK(UTIL_DIV_UFLOOR(22, 5) == 4);
    CHECK(UTIL_DIV_UFLOOR(23, 5) == 4);
    CHECK(UTIL_DIV_UFLOOR(24, 5) == 4);
    CHECK(UTIL_DIV_UFLOOR(25, 5) == 5);
    CHECK(UTIL_DIV_UFLOOR(26, 5) == 5);
    CHECK(UTIL_DIV_UFLOOR(27, 5) == 5);
    CHECK(UTIL_DIV_UFLOOR(28, 5) == 5);
    CHECK(UTIL_DIV_UFLOOR(29, 5) == 5);
    CHECK(UTIL_DIV_UFLOOR(30, 5) == 6);
}

TEST_CASE("macros.h DIV_ROUND")
{
    CHECK(UTIL_DIV_ROUND(-1234, 1) == -1234);
    CHECK(UTIL_DIV_ROUND(-123, 1) == -123);
    CHECK(UTIL_DIV_ROUND(-12, 1) == -12);
    CHECK(UTIL_DIV_ROUND(-3, 1) == -3);
    CHECK(UTIL_DIV_ROUND(-2, 1) == -2);
    CHECK(UTIL_DIV_ROUND(-1, 1) == -1);
    CHECK(UTIL_DIV_ROUND(0, 1) == 0);
    CHECK(UTIL_DIV_ROUND(1, 1) == 1);
    CHECK(UTIL_DIV_ROUND(2, 1) == 2);
    CHECK(UTIL_DIV_ROUND(3, 1) == 3);
    CHECK(UTIL_DIV_ROUND(12, 1) == 12);
    CHECK(UTIL_DIV_ROUND(123, 1) == 123);
    CHECK(UTIL_DIV_ROUND(1234, 1) == 1234);

    CHECK(UTIL_DIV_ROUND(-1234, -1) == 1234);
    CHECK(UTIL_DIV_ROUND(-123, -1) == 123);
    CHECK(UTIL_DIV_ROUND(-12, -1) == 12);
    CHECK(UTIL_DIV_ROUND(-3, -1) == 3);
    CHECK(UTIL_DIV_ROUND(-2, -1) == 2);
    CHECK(UTIL_DIV_ROUND(-1, -1) == 1);
    CHECK(UTIL_DIV_ROUND(0, -1) == 0);
    CHECK(UTIL_DIV_ROUND(1, -1) == -1);
    CHECK(UTIL_DIV_ROUND(2, -1) == -2);
    CHECK(UTIL_DIV_ROUND(3, -1) == -3);
    CHECK(UTIL_DIV_ROUND(12, -1) == -12);
    CHECK(UTIL_DIV_ROUND(123, -1) == -123);
    CHECK(UTIL_DIV_ROUND(1234, -1) == -1234);

    CHECK(UTIL_DIV_ROUND(-6, 2) == -3);
    CHECK(UTIL_DIV_ROUND(-5, 2) == -3);
    CHECK(UTIL_DIV_ROUND(-4, 2) == -2);
    CHECK(UTIL_DIV_ROUND(-3, 2) == -2);
    CHECK(UTIL_DIV_ROUND(-2, 2) == -1);
    CHECK(UTIL_DIV_ROUND(-1, 2) == -1);
    CHECK(UTIL_DIV_ROUND(0, 2) == 0);
    CHECK(UTIL_DIV_ROUND(1, 2) == 1);
    CHECK(UTIL_DIV_ROUND(2, 2) == 1);
    CHECK(UTIL_DIV_ROUND(3, 2) == 2);
    CHECK(UTIL_DIV_ROUND(4, 2) == 2);
    CHECK(UTIL_DIV_ROUND(5, 2) == 3);
    CHECK(UTIL_DIV_ROUND(6, 2) == 3);

    CHECK(UTIL_DIV_ROUND(-6, -2) == 3);
    CHECK(UTIL_DIV_ROUND(-5, -2) == 3);
    CHECK(UTIL_DIV_ROUND(-4, -2) == 2);
    CHECK(UTIL_DIV_ROUND(-3, -2) == 2);
    CHECK(UTIL_DIV_ROUND(-2, -2) == 1);
    CHECK(UTIL_DIV_ROUND(-1, -2) == 1);
    CHECK(UTIL_DIV_ROUND(0, -2) == 0);
    CHECK(UTIL_DIV_ROUND(1, -2) == -1);
    CHECK(UTIL_DIV_ROUND(2, -2) == -1);
    CHECK(UTIL_DIV_ROUND(3, -2) == -2);
    CHECK(UTIL_DIV_ROUND(4, -2) == -2);
    CHECK(UTIL_DIV_ROUND(5, -2) == -3);
    CHECK(UTIL_DIV_ROUND(6, -2) == -3);

    CHECK(UTIL_DIV_ROUND(-12, 3) == -4);
    CHECK(UTIL_DIV_ROUND(-11, 3) == -4);
    CHECK(UTIL_DIV_ROUND(-10, 3) == -3);
    CHECK(UTIL_DIV_ROUND(-9, 3) == -3);
    CHECK(UTIL_DIV_ROUND(-8, 3) == -3);
    CHECK(UTIL_DIV_ROUND(-7, 3) == -2);
    CHECK(UTIL_DIV_ROUND(-6, 3) == -2);
    CHECK(UTIL_DIV_ROUND(-5, 3) == -2);
    CHECK(UTIL_DIV_ROUND(-4, 3) == -1);
    CHECK(UTIL_DIV_ROUND(-3, 3) == -1);
    CHECK(UTIL_DIV_ROUND(-2, 3) == -1);
    CHECK(UTIL_DIV_ROUND(-1, 3) == 0);
    CHECK(UTIL_DIV_ROUND(0, 3) == 0);
    CHECK(UTIL_DIV_ROUND(1, 3) == 0);
    CHECK(UTIL_DIV_ROUND(2, 3) == 1);
    CHECK(UTIL_DIV_ROUND(3, 3) == 1);
    CHECK(UTIL_DIV_ROUND(4, 3) == 1);
    CHECK(UTIL_DIV_ROUND(5, 3) == 2);
    CHECK(UTIL_DIV_ROUND(6, 3) == 2);
    CHECK(UTIL_DIV_ROUND(7, 3) == 2);
    CHECK(UTIL_DIV_ROUND(8, 3) == 3);
    CHECK(UTIL_DIV_ROUND(9, 3) == 3);
    CHECK(UTIL_DIV_ROUND(10, 3) == 3);
    CHECK(UTIL_DIV_ROUND(11, 3) == 4);
    CHECK(UTIL_DIV_ROUND(12, 3) == 4);

    CHECK(UTIL_DIV_ROUND(-12, -3) == 4);
    CHECK(UTIL_DIV_ROUND(-11, -3) == 4);
    CHECK(UTIL_DIV_ROUND(-10, -3) == 3);
    CHECK(UTIL_DIV_ROUND(-9, -3) == 3);
    CHECK(UTIL_DIV_ROUND(-8, -3) == 3);
    CHECK(UTIL_DIV_ROUND(-7, -3) == 2);
    CHECK(UTIL_DIV_ROUND(-6, -3) == 2);
    CHECK(UTIL_DIV_ROUND(-5, -3) == 2);
    CHECK(UTIL_DIV_ROUND(-4, -3) == 1);
    CHECK(UTIL_DIV_ROUND(-3, -3) == 1);
    CHECK(UTIL_DIV_ROUND(-2, -3) == 1);
    CHECK(UTIL_DIV_ROUND(-1, -3) == 0);
    CHECK(UTIL_DIV_ROUND(0, -3) == 0);
    CHECK(UTIL_DIV_ROUND(1, -3) == 0);
    CHECK(UTIL_DIV_ROUND(2, -3) == -1);
    CHECK(UTIL_DIV_ROUND(3, -3) == -1);
    CHECK(UTIL_DIV_ROUND(4, -3) == -1);
    CHECK(UTIL_DIV_ROUND(5, -3) == -2);
    CHECK(UTIL_DIV_ROUND(6, -3) == -2);
    CHECK(UTIL_DIV_ROUND(7, -3) == -2);
    CHECK(UTIL_DIV_ROUND(8, -3) == -3);
    CHECK(UTIL_DIV_ROUND(9, -3) == -3);
    CHECK(UTIL_DIV_ROUND(10, -3) == -3);
    CHECK(UTIL_DIV_ROUND(11, -3) == -4);
    CHECK(UTIL_DIV_ROUND(12, -3) == -4);

    CHECK(UTIL_DIV_ROUND(-30, 4) == -8);
    CHECK(UTIL_DIV_ROUND(-29, 4) == -7);
    CHECK(UTIL_DIV_ROUND(-28, 4) == -7);
    CHECK(UTIL_DIV_ROUND(-27, 4) == -7);
    CHECK(UTIL_DIV_ROUND(-26, 4) == -7);
    CHECK(UTIL_DIV_ROUND(-25, 4) == -6);
    CHECK(UTIL_DIV_ROUND(-24, 4) == -6);
    CHECK(UTIL_DIV_ROUND(-23, 4) == -6);
    CHECK(UTIL_DIV_ROUND(-22, 4) == -6);
    CHECK(UTIL_DIV_ROUND(-21, 4) == -5);
    CHECK(UTIL_DIV_ROUND(-20, 4) == -5);
    CHECK(UTIL_DIV_ROUND(-19, 4) == -5);
    CHECK(UTIL_DIV_ROUND(-18, 4) == -5);
    CHECK(UTIL_DIV_ROUND(-17, 4) == -4);
    CHECK(UTIL_DIV_ROUND(-16, 4) == -4);
    CHECK(UTIL_DIV_ROUND(-15, 4) == -4);
    CHECK(UTIL_DIV_ROUND(-14, 4) == -4);
    CHECK(UTIL_DIV_ROUND(-13, 4) == -3);
    CHECK(UTIL_DIV_ROUND(-12, 4) == -3);
    CHECK(UTIL_DIV_ROUND(-11, 4) == -3);
    CHECK(UTIL_DIV_ROUND(-10, 4) == -3);
    CHECK(UTIL_DIV_ROUND(-9, 4) == -2);
    CHECK(UTIL_DIV_ROUND(-8, 4) == -2);
    CHECK(UTIL_DIV_ROUND(-7, 4) == -2);
    CHECK(UTIL_DIV_ROUND(-6, 4) == -2);
    CHECK(UTIL_DIV_ROUND(-5, 4) == -1);
    CHECK(UTIL_DIV_ROUND(-4, 4) == -1);
    CHECK(UTIL_DIV_ROUND(-3, 4) == -1);
    CHECK(UTIL_DIV_ROUND(-2, 4) == -1);
    CHECK(UTIL_DIV_ROUND(-1, 4) == 0);
    CHECK(UTIL_DIV_ROUND(0, 4) == 0);
    CHECK(UTIL_DIV_ROUND(1, 4) == 0);
    CHECK(UTIL_DIV_ROUND(2, 4) == 1);
    CHECK(UTIL_DIV_ROUND(3, 4) == 1);
    CHECK(UTIL_DIV_ROUND(4, 4) == 1);
    CHECK(UTIL_DIV_ROUND(5, 4) == 1);
    CHECK(UTIL_DIV_ROUND(6, 4) == 2);
    CHECK(UTIL_DIV_ROUND(7, 4) == 2);
    CHECK(UTIL_DIV_ROUND(8, 4) == 2);
    CHECK(UTIL_DIV_ROUND(9, 4) == 2);
    CHECK(UTIL_DIV_ROUND(10, 4) == 3);
    CHECK(UTIL_DIV_ROUND(11, 4) == 3);
    CHECK(UTIL_DIV_ROUND(12, 4) == 3);
    CHECK(UTIL_DIV_ROUND(13, 4) == 3);
    CHECK(UTIL_DIV_ROUND(14, 4) == 4);
    CHECK(UTIL_DIV_ROUND(15, 4) == 4);
    CHECK(UTIL_DIV_ROUND(16, 4) == 4);
    CHECK(UTIL_DIV_ROUND(17, 4) == 4);
    CHECK(UTIL_DIV_ROUND(18, 4) == 5);
    CHECK(UTIL_DIV_ROUND(19, 4) == 5);
    CHECK(UTIL_DIV_ROUND(20, 4) == 5);
    CHECK(UTIL_DIV_ROUND(21, 4) == 5);
    CHECK(UTIL_DIV_ROUND(22, 4) == 6);
    CHECK(UTIL_DIV_ROUND(23, 4) == 6);
    CHECK(UTIL_DIV_ROUND(24, 4) == 6);
    CHECK(UTIL_DIV_ROUND(25, 4) == 6);
    CHECK(UTIL_DIV_ROUND(26, 4) == 7);
    CHECK(UTIL_DIV_ROUND(27, 4) == 7);
    CHECK(UTIL_DIV_ROUND(28, 4) == 7);
    CHECK(UTIL_DIV_ROUND(29, 4) == 7);
    CHECK(UTIL_DIV_ROUND(30, 4) == 8);

    CHECK(UTIL_DIV_ROUND(-30, -4) == 8);
    CHECK(UTIL_DIV_ROUND(-29, -4) == 7);
    CHECK(UTIL_DIV_ROUND(-28, -4) == 7);
    CHECK(UTIL_DIV_ROUND(-27, -4) == 7);
    CHECK(UTIL_DIV_ROUND(-26, -4) == 7);
    CHECK(UTIL_DIV_ROUND(-25, -4) == 6);
    CHECK(UTIL_DIV_ROUND(-24, -4) == 6);
    CHECK(UTIL_DIV_ROUND(-23, -4) == 6);
    CHECK(UTIL_DIV_ROUND(-22, -4) == 6);
    CHECK(UTIL_DIV_ROUND(-21, -4) == 5);
    CHECK(UTIL_DIV_ROUND(-20, -4) == 5);
    CHECK(UTIL_DIV_ROUND(-19, -4) == 5);
    CHECK(UTIL_DIV_ROUND(-18, -4) == 5);
    CHECK(UTIL_DIV_ROUND(-17, -4) == 4);
    CHECK(UTIL_DIV_ROUND(-16, -4) == 4);
    CHECK(UTIL_DIV_ROUND(-15, -4) == 4);
    CHECK(UTIL_DIV_ROUND(-14, -4) == 4);
    CHECK(UTIL_DIV_ROUND(-13, -4) == 3);
    CHECK(UTIL_DIV_ROUND(-12, -4) == 3);
    CHECK(UTIL_DIV_ROUND(-11, -4) == 3);
    CHECK(UTIL_DIV_ROUND(-10, -4) == 3);
    CHECK(UTIL_DIV_ROUND(-9, -4) == 2);
    CHECK(UTIL_DIV_ROUND(-8, -4) == 2);
    CHECK(UTIL_DIV_ROUND(-7, -4) == 2);
    CHECK(UTIL_DIV_ROUND(-6, -4) == 2);
    CHECK(UTIL_DIV_ROUND(-5, -4) == 1);
    CHECK(UTIL_DIV_ROUND(-4, -4) == 1);
    CHECK(UTIL_DIV_ROUND(-3, -4) == 1);
    CHECK(UTIL_DIV_ROUND(-2, -4) == 1);
    CHECK(UTIL_DIV_ROUND(-1, -4) == 0);
    CHECK(UTIL_DIV_ROUND(0, -4) == 0);
    CHECK(UTIL_DIV_ROUND(1, -4) == 0);
    CHECK(UTIL_DIV_ROUND(2, -4) == -1);
    CHECK(UTIL_DIV_ROUND(3, -4) == -1);
    CHECK(UTIL_DIV_ROUND(4, -4) == -1);
    CHECK(UTIL_DIV_ROUND(5, -4) == -1);
    CHECK(UTIL_DIV_ROUND(6, -4) == -2);
    CHECK(UTIL_DIV_ROUND(7, -4) == -2);
    CHECK(UTIL_DIV_ROUND(8, -4) == -2);
    CHECK(UTIL_DIV_ROUND(9, -4) == -2);
    CHECK(UTIL_DIV_ROUND(10, -4) == -3);
    CHECK(UTIL_DIV_ROUND(11, -4) == -3);
    CHECK(UTIL_DIV_ROUND(12, -4) == -3);
    CHECK(UTIL_DIV_ROUND(13, -4) == -3);
    CHECK(UTIL_DIV_ROUND(14, -4) == -4);
    CHECK(UTIL_DIV_ROUND(15, -4) == -4);
    CHECK(UTIL_DIV_ROUND(16, -4) == -4);
    CHECK(UTIL_DIV_ROUND(17, -4) == -4);
    CHECK(UTIL_DIV_ROUND(18, -4) == -5);
    CHECK(UTIL_DIV_ROUND(19, -4) == -5);
    CHECK(UTIL_DIV_ROUND(20, -4) == -5);
    CHECK(UTIL_DIV_ROUND(21, -4) == -5);
    CHECK(UTIL_DIV_ROUND(22, -4) == -6);
    CHECK(UTIL_DIV_ROUND(23, -4) == -6);
    CHECK(UTIL_DIV_ROUND(24, -4) == -6);
    CHECK(UTIL_DIV_ROUND(25, -4) == -6);
    CHECK(UTIL_DIV_ROUND(26, -4) == -7);
    CHECK(UTIL_DIV_ROUND(27, -4) == -7);
    CHECK(UTIL_DIV_ROUND(28, -4) == -7);
    CHECK(UTIL_DIV_ROUND(29, -4) == -7);
    CHECK(UTIL_DIV_ROUND(30, -4) == -8);

    CHECK(UTIL_DIV_ROUND(-30, 5) == -6);
    CHECK(UTIL_DIV_ROUND(-29, 5) == -6);
    CHECK(UTIL_DIV_ROUND(-28, 5) == -6);
    CHECK(UTIL_DIV_ROUND(-27, 5) == -5);
    CHECK(UTIL_DIV_ROUND(-26, 5) == -5);
    CHECK(UTIL_DIV_ROUND(-25, 5) == -5);
    CHECK(UTIL_DIV_ROUND(-24, 5) == -5);
    CHECK(UTIL_DIV_ROUND(-23, 5) == -5);
    CHECK(UTIL_DIV_ROUND(-22, 5) == -4);
    CHECK(UTIL_DIV_ROUND(-21, 5) == -4);
    CHECK(UTIL_DIV_ROUND(-20, 5) == -4);
    CHECK(UTIL_DIV_ROUND(-19, 5) == -4);
    CHECK(UTIL_DIV_ROUND(-18, 5) == -4);
    CHECK(UTIL_DIV_ROUND(-17, 5) == -3);
    CHECK(UTIL_DIV_ROUND(-16, 5) == -3);
    CHECK(UTIL_DIV_ROUND(-15, 5) == -3);
    CHECK(UTIL_DIV_ROUND(-14, 5) == -3);
    CHECK(UTIL_DIV_ROUND(-13, 5) == -3);
    CHECK(UTIL_DIV_ROUND(-12, 5) == -2);
    CHECK(UTIL_DIV_ROUND(-11, 5) == -2);
    CHECK(UTIL_DIV_ROUND(-10, 5) == -2);
    CHECK(UTIL_DIV_ROUND(-9, 5) == -2);
    CHECK(UTIL_DIV_ROUND(-8, 5) == -2);
    CHECK(UTIL_DIV_ROUND(-7, 5) == -1);
    CHECK(UTIL_DIV_ROUND(-6, 5) == -1);
    CHECK(UTIL_DIV_ROUND(-5, 5) == -1);
    CHECK(UTIL_DIV_ROUND(-4, 5) == -1);
    CHECK(UTIL_DIV_ROUND(-3, 5) == -1);
    CHECK(UTIL_DIV_ROUND(-2, 5) == 0);
    CHECK(UTIL_DIV_ROUND(-1, 5) == 0);
    CHECK(UTIL_DIV_ROUND(0, 5) == 0);
    CHECK(UTIL_DIV_ROUND(1, 5) == 0);
    CHECK(UTIL_DIV_ROUND(2, 5) == 0);
    CHECK(UTIL_DIV_ROUND(3, 5) == 1);
    CHECK(UTIL_DIV_ROUND(4, 5) == 1);
    CHECK(UTIL_DIV_ROUND(5, 5) == 1);
    CHECK(UTIL_DIV_ROUND(6, 5) == 1);
    CHECK(UTIL_DIV_ROUND(7, 5) == 1);
    CHECK(UTIL_DIV_ROUND(8, 5) == 2);
    CHECK(UTIL_DIV_ROUND(9, 5) == 2);
    CHECK(UTIL_DIV_ROUND(10, 5) == 2);
    CHECK(UTIL_DIV_ROUND(11, 5) == 2);
    CHECK(UTIL_DIV_ROUND(12, 5) == 2);
    CHECK(UTIL_DIV_ROUND(13, 5) == 3);
    CHECK(UTIL_DIV_ROUND(14, 5) == 3);
    CHECK(UTIL_DIV_ROUND(15, 5) == 3);
    CHECK(UTIL_DIV_ROUND(16, 5) == 3);
    CHECK(UTIL_DIV_ROUND(17, 5) == 3);
    CHECK(UTIL_DIV_ROUND(18, 5) == 4);
    CHECK(UTIL_DIV_ROUND(19, 5) == 4);
    CHECK(UTIL_DIV_ROUND(20, 5) == 4);
    CHECK(UTIL_DIV_ROUND(21, 5) == 4);
    CHECK(UTIL_DIV_ROUND(22, 5) == 4);
    CHECK(UTIL_DIV_ROUND(23, 5) == 5);
    CHECK(UTIL_DIV_ROUND(24, 5) == 5);
    CHECK(UTIL_DIV_ROUND(25, 5) == 5);
    CHECK(UTIL_DIV_ROUND(26, 5) == 5);
    CHECK(UTIL_DIV_ROUND(27, 5) == 5);
    CHECK(UTIL_DIV_ROUND(28, 5) == 6);
    CHECK(UTIL_DIV_ROUND(29, 5) == 6);
    CHECK(UTIL_DIV_ROUND(30, 5) == 6);

    CHECK(UTIL_DIV_ROUND(-30, -5) == 6);
    CHECK(UTIL_DIV_ROUND(-29, -5) == 6);
    CHECK(UTIL_DIV_ROUND(-28, -5) == 6);
    CHECK(UTIL_DIV_ROUND(-27, -5) == 5);
    CHECK(UTIL_DIV_ROUND(-26, -5) == 5);
    CHECK(UTIL_DIV_ROUND(-25, -5) == 5);
    CHECK(UTIL_DIV_ROUND(-24, -5) == 5);
    CHECK(UTIL_DIV_ROUND(-23, -5) == 5);
    CHECK(UTIL_DIV_ROUND(-22, -5) == 4);
    CHECK(UTIL_DIV_ROUND(-21, -5) == 4);
    CHECK(UTIL_DIV_ROUND(-20, -5) == 4);
    CHECK(UTIL_DIV_ROUND(-19, -5) == 4);
    CHECK(UTIL_DIV_ROUND(-18, -5) == 4);
    CHECK(UTIL_DIV_ROUND(-17, -5) == 3);
    CHECK(UTIL_DIV_ROUND(-16, -5) == 3);
    CHECK(UTIL_DIV_ROUND(-15, -5) == 3);
    CHECK(UTIL_DIV_ROUND(-14, -5) == 3);
    CHECK(UTIL_DIV_ROUND(-13, -5) == 3);
    CHECK(UTIL_DIV_ROUND(-12, -5) == 2);
    CHECK(UTIL_DIV_ROUND(-11, -5) == 2);
    CHECK(UTIL_DIV_ROUND(-10, -5) == 2);
    CHECK(UTIL_DIV_ROUND(-9, -5) == 2);
    CHECK(UTIL_DIV_ROUND(-8, -5) == 2);
    CHECK(UTIL_DIV_ROUND(-7, -5) == 1);
    CHECK(UTIL_DIV_ROUND(-6, -5) == 1);
    CHECK(UTIL_DIV_ROUND(-5, -5) == 1);
    CHECK(UTIL_DIV_ROUND(-4, -5) == 1);
    CHECK(UTIL_DIV_ROUND(-3, -5) == 1);
    CHECK(UTIL_DIV_ROUND(-2, -5) == 0);
    CHECK(UTIL_DIV_ROUND(-1, -5) == 0);
    CHECK(UTIL_DIV_ROUND(0, -5) == 0);
    CHECK(UTIL_DIV_ROUND(1, -5) == 0);
    CHECK(UTIL_DIV_ROUND(2, -5) == 0);
    CHECK(UTIL_DIV_ROUND(3, -5) == -1);
    CHECK(UTIL_DIV_ROUND(4, -5) == -1);
    CHECK(UTIL_DIV_ROUND(5, -5) == -1);
    CHECK(UTIL_DIV_ROUND(6, -5) == -1);
    CHECK(UTIL_DIV_ROUND(7, -5) == -1);
    CHECK(UTIL_DIV_ROUND(8, -5) == -2);
    CHECK(UTIL_DIV_ROUND(9, -5) == -2);
    CHECK(UTIL_DIV_ROUND(10, -5) == -2);
    CHECK(UTIL_DIV_ROUND(11, -5) == -2);
    CHECK(UTIL_DIV_ROUND(12, -5) == -2);
    CHECK(UTIL_DIV_ROUND(13, -5) == -3);
    CHECK(UTIL_DIV_ROUND(14, -5) == -3);
    CHECK(UTIL_DIV_ROUND(15, -5) == -3);
    CHECK(UTIL_DIV_ROUND(16, -5) == -3);
    CHECK(UTIL_DIV_ROUND(17, -5) == -3);
    CHECK(UTIL_DIV_ROUND(18, -5) == -4);
    CHECK(UTIL_DIV_ROUND(19, -5) == -4);
    CHECK(UTIL_DIV_ROUND(20, -5) == -4);
    CHECK(UTIL_DIV_ROUND(21, -5) == -4);
    CHECK(UTIL_DIV_ROUND(22, -5) == -4);
    CHECK(UTIL_DIV_ROUND(23, -5) == -5);
    CHECK(UTIL_DIV_ROUND(24, -5) == -5);
    CHECK(UTIL_DIV_ROUND(25, -5) == -5);
    CHECK(UTIL_DIV_ROUND(26, -5) == -5);
    CHECK(UTIL_DIV_ROUND(27, -5) == -5);
    CHECK(UTIL_DIV_ROUND(28, -5) == -6);
    CHECK(UTIL_DIV_ROUND(29, -5) == -6);
    CHECK(UTIL_DIV_ROUND(30, -5) == -6);
}

TEST_CASE("macros.h DIV_UROUND")
{
    CHECK(UTIL_DIV_UROUND(0, 1) == 0);
    CHECK(UTIL_DIV_UROUND(1, 1) == 1);
    CHECK(UTIL_DIV_UROUND(2, 1) == 2);
    CHECK(UTIL_DIV_UROUND(3, 1) == 3);
    CHECK(UTIL_DIV_UROUND(12, 1) == 12);
    CHECK(UTIL_DIV_UROUND(123, 1) == 123);
    CHECK(UTIL_DIV_UROUND(1234, 1) == 1234);

    CHECK(UTIL_DIV_UROUND(0, 2) == 0);
    CHECK(UTIL_DIV_UROUND(1, 2) == 1);
    CHECK(UTIL_DIV_UROUND(2, 2) == 1);
    CHECK(UTIL_DIV_UROUND(3, 2) == 2);
    CHECK(UTIL_DIV_UROUND(4, 2) == 2);
    CHECK(UTIL_DIV_UROUND(5, 2) == 3);
    CHECK(UTIL_DIV_UROUND(6, 2) == 3);

    CHECK(UTIL_DIV_UROUND(0, 3) == 0);
    CHECK(UTIL_DIV_UROUND(1, 3) == 0);
    CHECK(UTIL_DIV_UROUND(2, 3) == 1);
    CHECK(UTIL_DIV_UROUND(3, 3) == 1);
    CHECK(UTIL_DIV_UROUND(4, 3) == 1);
    CHECK(UTIL_DIV_UROUND(5, 3) == 2);
    CHECK(UTIL_DIV_UROUND(6, 3) == 2);
    CHECK(UTIL_DIV_UROUND(7, 3) == 2);
    CHECK(UTIL_DIV_UROUND(8, 3) == 3);
    CHECK(UTIL_DIV_UROUND(9, 3) == 3);
    CHECK(UTIL_DIV_UROUND(10, 3) == 3);
    CHECK(UTIL_DIV_UROUND(11, 3) == 4);
    CHECK(UTIL_DIV_UROUND(12, 3) == 4);

    CHECK(UTIL_DIV_UROUND(0, 4) == 0);
    CHECK(UTIL_DIV_UROUND(1, 4) == 0);
    CHECK(UTIL_DIV_UROUND(2, 4) == 1);
    CHECK(UTIL_DIV_UROUND(3, 4) == 1);
    CHECK(UTIL_DIV_UROUND(4, 4) == 1);
    CHECK(UTIL_DIV_UROUND(5, 4) == 1);
    CHECK(UTIL_DIV_UROUND(6, 4) == 2);
    CHECK(UTIL_DIV_UROUND(7, 4) == 2);
    CHECK(UTIL_DIV_UROUND(8, 4) == 2);
    CHECK(UTIL_DIV_UROUND(9, 4) == 2);
    CHECK(UTIL_DIV_UROUND(10, 4) == 3);
    CHECK(UTIL_DIV_UROUND(11, 4) == 3);
    CHECK(UTIL_DIV_UROUND(12, 4) == 3);
    CHECK(UTIL_DIV_UROUND(13, 4) == 3);
    CHECK(UTIL_DIV_UROUND(14, 4) == 4);
    CHECK(UTIL_DIV_UROUND(15, 4) == 4);
    CHECK(UTIL_DIV_UROUND(16, 4) == 4);
    CHECK(UTIL_DIV_UROUND(17, 4) == 4);
    CHECK(UTIL_DIV_UROUND(18, 4) == 5);
    CHECK(UTIL_DIV_UROUND(19, 4) == 5);
    CHECK(UTIL_DIV_UROUND(20, 4) == 5);
    CHECK(UTIL_DIV_UROUND(21, 4) == 5);
    CHECK(UTIL_DIV_UROUND(22, 4) == 6);
    CHECK(UTIL_DIV_UROUND(23, 4) == 6);
    CHECK(UTIL_DIV_UROUND(24, 4) == 6);
    CHECK(UTIL_DIV_UROUND(25, 4) == 6);
    CHECK(UTIL_DIV_UROUND(26, 4) == 7);
    CHECK(UTIL_DIV_UROUND(27, 4) == 7);
    CHECK(UTIL_DIV_UROUND(28, 4) == 7);
    CHECK(UTIL_DIV_UROUND(29, 4) == 7);
    CHECK(UTIL_DIV_UROUND(30, 4) == 8);

    CHECK(UTIL_DIV_UROUND(0, 5) == 0);
    CHECK(UTIL_DIV_UROUND(1, 5) == 0);
    CHECK(UTIL_DIV_UROUND(2, 5) == 0);
    CHECK(UTIL_DIV_UROUND(3, 5) == 1);
    CHECK(UTIL_DIV_UROUND(4, 5) == 1);
    CHECK(UTIL_DIV_UROUND(5, 5) == 1);
    CHECK(UTIL_DIV_UROUND(6, 5) == 1);
    CHECK(UTIL_DIV_UROUND(7, 5) == 1);
    CHECK(UTIL_DIV_UROUND(8, 5) == 2);
    CHECK(UTIL_DIV_UROUND(9, 5) == 2);
    CHECK(UTIL_DIV_UROUND(10, 5) == 2);
    CHECK(UTIL_DIV_UROUND(11, 5) == 2);
    CHECK(UTIL_DIV_UROUND(12, 5) == 2);
    CHECK(UTIL_DIV_UROUND(13, 5) == 3);
    CHECK(UTIL_DIV_UROUND(14, 5) == 3);
    CHECK(UTIL_DIV_UROUND(15, 5) == 3);
    CHECK(UTIL_DIV_UROUND(16, 5) == 3);
    CHECK(UTIL_DIV_UROUND(17, 5) == 3);
    CHECK(UTIL_DIV_UROUND(18, 5) == 4);
    CHECK(UTIL_DIV_UROUND(19, 5) == 4);
    CHECK(UTIL_DIV_UROUND(20, 5) == 4);
    CHECK(UTIL_DIV_UROUND(21, 5) == 4);
    CHECK(UTIL_DIV_UROUND(22, 5) == 4);
    CHECK(UTIL_DIV_UROUND(23, 5) == 5);
    CHECK(UTIL_DIV_UROUND(24, 5) == 5);
    CHECK(UTIL_DIV_UROUND(25, 5) == 5);
    CHECK(UTIL_DIV_UROUND(26, 5) == 5);
    CHECK(UTIL_DIV_UROUND(27, 5) == 5);
    CHECK(UTIL_DIV_UROUND(28, 5) == 6);
    CHECK(UTIL_DIV_UROUND(29, 5) == 6);
    CHECK(UTIL_DIV_UROUND(30, 5) == 6);
}



#endif // IG_TEST_UNIT_MACROS_HPP
