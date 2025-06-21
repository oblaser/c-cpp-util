/*
author          Oliver Blaser
date            21.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_TEST_UNIT_STRING_H
#define IG_TEST_UNIT_STRING_H

#include <stddef.h>
#include <stdint.h>

#include "util/string.h"

#include "catch2/catch.hpp"



static const char* const str1 = "123";
static const char* const str2 = "a1b2c3d4";



TEST_CASE("string.h defiens")
{
    CHECK(sizeof(UTIL_npos) == sizeof(size_t));
    CHECK(UTIL_npos == SIZE_MAX);
}

TEST_CASE("string.h string length")
{
    CHECK(UTIL_strlen(str1) == 3);
    CHECK(UTIL_strlen(str2) == 8);

    CHECK(UTIL_strnlen(str1, 5) == 3);
    CHECK(UTIL_strnlen(str2, 5) == 5);
}

TEST_CASE("string.h find char")
{
    CHECK(UTIL_strchr(str1, '1') == (str1 + 0));
    CHECK(UTIL_strchr(str1, '2') == (str1 + 1));
    CHECK(UTIL_strchr(str1, 0) == (str1 + 3));
    CHECK(UTIL_strchr(str1, 'a') == NULL);
    CHECK(UTIL_strchr(str2, 'a') == (str2 + 0));
    CHECK(UTIL_strchr(str2, '2') == (str2 + 3));
    CHECK(UTIL_strchr(str2, 0) == (str2 + 8));



    CHECK(UTIL_strnchr(str1, '1', 1000) == (str1 + 0));
    CHECK(UTIL_strnchr(str1, '2', 1000) == (str1 + 1));
    CHECK(UTIL_strnchr(str1, 0, 1000) == (str1 + 3));
    CHECK(UTIL_strnchr(str1, 'a', 1000) == NULL);
    CHECK(UTIL_strnchr(str2, 'a', 1000) == (str2 + 0));
    CHECK(UTIL_strnchr(str2, '2', 1000) == (str2 + 3));
    CHECK(UTIL_strnchr(str2, 0, 1000) == (str2 + 8));

    CHECK(UTIL_strnchr(str1, '1', 3) == (str1 + 0));
    CHECK(UTIL_strnchr(str1, '2', 3) == (str1 + 1));
    CHECK(UTIL_strnchr(str1, 0, 3) == (str1 + 3));
    CHECK(UTIL_strnchr(str1, 'a', 3) == NULL);
    CHECK(UTIL_strnchr(str2, 'a', 3) == (str2 + 0));
    CHECK(UTIL_strnchr(str2, '2', 3) == NULL);
    CHECK(UTIL_strnchr(str2, 0, 3) == NULL);

    CHECK(UTIL_strnchr(str1, '1', 2) == (str1 + 0));
    CHECK(UTIL_strnchr(str1, '2', 2) == (str1 + 1));
    CHECK(UTIL_strnchr(str1, 0, 2) == NULL);
    CHECK(UTIL_strnchr(str1, 'a', 2) == NULL);
    CHECK(UTIL_strnchr(str2, 'a', 2) == (str2 + 0));
    CHECK(UTIL_strnchr(str2, '2', 2) == NULL);
    CHECK(UTIL_strnchr(str2, 0, 2) == NULL);

    CHECK(UTIL_strnchr(str1, '1', 0) == NULL);
    CHECK(UTIL_strnchr(str1, '2', 0) == NULL);
    CHECK(UTIL_strnchr(str1, 0, 0) == NULL);
    CHECK(UTIL_strnchr(str1, 'a', 0) == NULL);
    CHECK(UTIL_strnchr(str2, 'a', 0) == NULL);
    CHECK(UTIL_strnchr(str2, '2', 0) == NULL);
    CHECK(UTIL_strnchr(str2, 0, 0) == NULL);
}



#endif // IG_TEST_UNIT_STRING_H
