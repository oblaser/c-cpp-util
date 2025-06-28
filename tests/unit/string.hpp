/*
author          Oliver Blaser
date            21.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_TEST_UNIT_STRING_H
#define IG_TEST_UNIT_STRING_H

#include <ctype.h>
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

TEST_CASE("string.h Character Classification")
{
    for (char c = 0; c >= 0; ++c)
    {
        CHECK((UTIL_isBlank(c) != 0) == (isblank(c) != 0));
        CHECK((UTIL_isCntrl(c) != 0) == (iscntrl(c) != 0));
        CHECK((UTIL_isDigit(c) != 0) == (isdigit(c) != 0));
        CHECK((UTIL_isGraph(c) != 0) == (isgraph(c) != 0));
        CHECK((UTIL_isHex(c) != 0) == (isxdigit(c) != 0));
        CHECK((UTIL_isLower(c) != 0) == (islower(c) != 0));
        CHECK((UTIL_isNull(c) != 0) == (c == 0));
        CHECK((UTIL_isPrint(c) != 0) == (isprint(c) != 0));
        CHECK((UTIL_isPunct(c) != 0) == (ispunct(c) != 0));
        CHECK((UTIL_isSpace(c) != 0) == (isspace(c) != 0));
        CHECK((UTIL_isUpper(c) != 0) == (isupper(c) != 0));
        CHECK((UTIL_isAlpha(c) != 0) == (isalpha(c) != 0));
        CHECK((UTIL_isAlnum(c) != 0) == (isalnum(c) != 0));
    }
}

TEST_CASE("string.h copy string")
{
    char buffer[10];
    REQUIRE(sizeof(buffer) >= (strlen(str1) + 1));
    REQUIRE(sizeof(buffer) >= (strlen(str2) + 1));

    CHECK(strcmp(UTIL_strcpy(buffer, str1 + 1), "23") == 0);
    CHECK(strcmp(UTIL_strcpy(buffer, str2 + 1), "1b2c3d4") == 0);

    CHECK(strcmp(UTIL_strncpy(strcpy(buffer, "xx#$"), str1, 2), "12#$") == 0);
    CHECK(strcmp(UTIL_strncpy(strcpy(buffer, "xx#$"), str2, 2), "a1#$") == 0);

    CHECK(strcmp(UTIL_strncpy(strcpy(buffer, "xxx#$"), str1, 3), "123#$") == 0);

    CHECK(strcmp(UTIL_strncpy(strcpy(buffer, "xxxx#$"), str1, 4), "123") == 0);

    CHECK(strcmp(UTIL_strncpy(buffer, str1, 200), "123") == 0);
    CHECK(strcmp(UTIL_strncpy(buffer, str2, 200), "a1b2c3d4") == 0);
}

TEST_CASE("string.h concatenate strings")
{
    const char* const baseStr = "qwe#";
    char buffer[16];
    REQUIRE(sizeof(buffer) >= (strlen(baseStr) + strlen(str1) + 1));
    REQUIRE(sizeof(buffer) >= (strlen(baseStr) + strlen(str2) + 1));



    CHECK(strcmp(UTIL_strcat(strcpy(buffer, baseStr), str1 + 1), "qwe#23") == 0);
    CHECK(strcmp(UTIL_strcat(strcpy(buffer, baseStr), str2 + 1), "qwe#1b2c3d4") == 0);



    strcpy(strcpy(buffer, baseStr) + strlen(baseStr) + 1, "x#$");
    CHECK(strcmp(UTIL_strncat(buffer, str1, 2), "qwe#12") == 0);

    strcpy(strcpy(buffer, baseStr) + strlen(baseStr) + 1, "x#$");
    CHECK(strcmp(UTIL_strncat(buffer, str2, 2), "qwe#a1") == 0);



    strcpy(strcpy(buffer, baseStr) + strlen(baseStr) + 1, "xx#$");
    CHECK(strcmp(UTIL_strncat(buffer, str1, 3), "qwe#123") == 0);



    strcpy(strcpy(buffer, baseStr) + strlen(baseStr) + 1, "xxx#$");
    CHECK(strcmp(UTIL_strncat(buffer, str1, 4), "qwe#123") == 0);



    CHECK(strcmp(UTIL_strncat(strcpy(buffer, baseStr), str1, 200), "qwe#123") == 0);
    CHECK(strcmp(UTIL_strncat(strcpy(buffer, baseStr), str2, 200), "qwe#a1b2c3d4") == 0);
}

TEST_CASE("string.h case conversion")
{
    const char* mixed = "0123 ThE QuIcK BrOwN FoX JuMpS OvEr tHe lAzY DoG. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    const char* lower = "0123 the quick brown fox jumps over the lazy dog. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    const char* upper = "0123 THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    char buffer[78];

    REQUIRE(sizeof(buffer) >= (strlen(mixed) + 1));
    REQUIRE(sizeof(buffer) >= (strlen(lower) + 1));
    REQUIRE(sizeof(buffer) >= (strlen(upper) + 1));

    strcpy(buffer, mixed);
    CHECK(strcmp(UTIL_strlower_ascii(buffer), lower) == 0);

    strcpy(buffer, mixed);
    CHECK(strcmp(UTIL_strupper_ascii(buffer), upper) == 0);
}

TEST_CASE("string.h string length")
{
    CHECK(UTIL_strlen(str1) == 3);
    CHECK(UTIL_strlen(str2) == 8);

    CHECK(UTIL_strnlen(str1, 5) == 3);
    CHECK(UTIL_strnlen(str2, 5) == 5);
}

TEST_CASE("string.h compare strings")
{
    const char* const lhs = "abcd";

    CHECK(UTIL_strcmp(lhs, "") > 0);
    CHECK(UTIL_strcmp(lhs, "abc") > 0);
    CHECK(UTIL_strcmp(lhs, "abcc") > 0);
    CHECK(UTIL_strcmp(lhs, "abcd") == 0);
    CHECK(UTIL_strcmp(lhs, "abcde") < 0);
    CHECK(UTIL_strcmp(lhs, "abce") < 0);
    CHECK(UTIL_strcmp("", lhs) < 0);

    CHECK(UTIL_strncmp(lhs, "", 2) > 0);
    CHECK(UTIL_strncmp(lhs, "abc", 2) == 0);
    CHECK(UTIL_strncmp(lhs, "abcc", 2) == 0);
    CHECK(UTIL_strncmp(lhs, "abcd", 2) == 0);
    CHECK(UTIL_strncmp(lhs, "abcde", 2) == 0);
    CHECK(UTIL_strncmp(lhs, "abce", 2) == 0);
    CHECK(UTIL_strncmp("", lhs, 2) < 0);

    CHECK(UTIL_strncmp(lhs, "ab", 2) == 0);
    CHECK(UTIL_strncmp(lhs, "a", 2) > 0);

    CHECK(UTIL_strncmp(lhs, "", 200) > 0);
    CHECK(UTIL_strncmp(lhs, "abc", 200) > 0);
    CHECK(UTIL_strncmp(lhs, "abcc", 200) > 0);
    CHECK(UTIL_strncmp(lhs, "abcd", 200) == 0);
    CHECK(UTIL_strncmp(lhs, "abcde", 200) < 0);
    CHECK(UTIL_strncmp(lhs, "abce", 200) < 0);
    CHECK(UTIL_strncmp("", lhs, 200) < 0);



    CHECK(UTIL_streq(lhs, "") == 0);
    CHECK(UTIL_streq(lhs, "abc") == 0);
    CHECK(UTIL_streq(lhs, "abcc") == 0);
    CHECK(UTIL_streq(lhs, "abcd") != 0);
    CHECK(UTIL_streq(lhs, "abcde") == 0);
    CHECK(UTIL_streq(lhs, "abce") == 0);
    CHECK(UTIL_streq("", lhs) == 0);

    CHECK(UTIL_strneq(lhs, "", 2) == 0);
    CHECK(UTIL_strneq(lhs, "abc", 2) != 0);
    CHECK(UTIL_strneq(lhs, "abcc", 2) != 0);
    CHECK(UTIL_strneq(lhs, "abcd", 2) != 0);
    CHECK(UTIL_strneq(lhs, "abcde", 2) != 0);
    CHECK(UTIL_strneq(lhs, "abce", 2) != 0);
    CHECK(UTIL_strneq("", lhs, 2) == 0);

    CHECK(UTIL_strneq(lhs, "ab", 2) != 0);
    CHECK(UTIL_strneq(lhs, "a", 2) == 0);

    CHECK(UTIL_strneq(lhs, "", 200) == 0);
    CHECK(UTIL_strneq(lhs, "abc", 200) == 0);
    CHECK(UTIL_strneq(lhs, "abcc", 200) == 0);
    CHECK(UTIL_strneq(lhs, "abcd", 200) != 0);
    CHECK(UTIL_strneq(lhs, "abcde", 200) == 0);
    CHECK(UTIL_strneq(lhs, "abce", 200) == 0);
    CHECK(UTIL_strneq("", lhs, 200) == 0);
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
