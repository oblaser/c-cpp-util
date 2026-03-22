/*
author          Oliver Blaser
date            22.03.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "util/macros.h"
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
    char* end;

    char buffer[10];
    REQUIRE(sizeof(buffer) >= (strlen(str1) + 1));
    REQUIRE(sizeof(buffer) >= (strlen(str2) + 1));



    end = NULL;
    CHECK(strcmp(UTIL_strcpy(buffer, str1 + 1, &end), "23") == 0);
    CHECK(end == buffer + 2);

    end = NULL;
    CHECK(strcmp(UTIL_strcpy(buffer, str2 + 1, &end), "1b2c3d4") == 0);
    CHECK(end == buffer + 7);



    end = NULL;
    CHECK(strcmp(UTIL_strncpy(strcpy(buffer, "xx#$"), str1, 2, &end), "12#$") == 0);
    CHECK(end == buffer + 2);

    end = NULL;
    CHECK(strcmp(UTIL_strncpy(strcpy(buffer, "xx#$"), str2, 2, &end), "a1#$") == 0);
    CHECK(end == buffer + 2);

    end = NULL;
    CHECK(strcmp(UTIL_strncpy(strcpy(buffer, "xxx#$"), str1, 3, &end), "123#$") == 0);
    CHECK(end == buffer + 3);

    end = NULL;
    CHECK(strcmp(UTIL_strncpy(strcpy(buffer, "xxxx#$"), str1, 4, &end), "123") == 0);
    CHECK(end == buffer + 3);

    end = NULL;
    CHECK(strcmp(UTIL_strncpy(buffer, str1, 200, &end), "123") == 0);
    CHECK(end == buffer + 3);

    end = NULL;
    CHECK(strcmp(UTIL_strncpy(buffer, str2, 200, &end), "a1b2c3d4") == 0);
    CHECK(end == buffer + 8);
}

TEST_CASE("string.h concatenate strings")
{
    char* end;

    const char* const baseStr = "qwe#";
    char buffer[16];
    REQUIRE(sizeof(buffer) >= (strlen(baseStr) + strlen(str1) + 1));
    REQUIRE(sizeof(buffer) >= (strlen(baseStr) + strlen(str2) + 1));



    end = NULL;
    CHECK(strcmp(UTIL_strcat(strcpy(buffer, baseStr), str1 + 1, &end), "qwe#23") == 0);
    CHECK(end == buffer + 6);

    end = NULL;
    CHECK(strcmp(UTIL_strcat(strcpy(buffer, baseStr), str2 + 1, &end), "qwe#1b2c3d4") == 0);
    CHECK(end == buffer + 11);



    end = NULL;
    strcpy(strcpy(buffer, baseStr) + strlen(baseStr) + 1, "x#$" /* this should get overwritten */);
    CHECK(strcmp(UTIL_strncat(buffer, str1, 2, &end), "qwe#12") == 0);
    CHECK(end == buffer + 6);

    end = NULL;
    strcpy(strcpy(buffer, baseStr) + strlen(baseStr) + 1, "x#$" /* this should get overwritten */);
    CHECK(strcmp(UTIL_strncat(buffer, str2, 2, &end), "qwe#a1") == 0);
    CHECK(end == buffer + 6);

    end = NULL;
    strcpy(strcpy(buffer, baseStr) + strlen(baseStr) + 1, "xx#$" /* this should get overwritten */);
    CHECK(strcmp(UTIL_strncat(buffer, str1, 3, &end), "qwe#123") == 0);
    CHECK(end == buffer + 7);

    end = NULL;
    strcpy(strcpy(buffer, baseStr) + strlen(baseStr) + 1, "xxx#$" /* this should get overwritten */);
    CHECK(strcmp(UTIL_strncat(buffer, str1, 4, &end), "qwe#123") == 0);
    CHECK(end == buffer + 7);



    end = NULL;
    CHECK(strcmp(UTIL_strncat(strcpy(buffer, baseStr), str1, 200, &end), "qwe#123") == 0);
    CHECK(end == buffer + 7);

    end = NULL;
    CHECK(strcmp(UTIL_strncat(strcpy(buffer, baseStr), str2, 200, &end), "qwe#a1b2c3d4") == 0);
    CHECK(end == buffer + 12);
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

TEST_CASE("string.h String Classification integer")
{
    CHECK(UTIL_isIntStr(NULL, UTIL_npos) == 0);
    CHECK(UTIL_isIntStr("", UTIL_npos) == 0);
    CHECK(UTIL_isIntStr("123", 0) == 0);

    CHECK(UTIL_isIntStr("a123", UTIL_npos) == 0);
    CHECK(UTIL_isIntStr("a", UTIL_npos) == 0);
    CHECK(UTIL_isIntStr("abc", UTIL_npos) == 0);
    CHECK(UTIL_isIntStr("-", UTIL_npos) == 0);

    CHECK(UTIL_isIntStr("-abc", UTIL_npos) == 0);
    CHECK(UTIL_isIntStr("-abc", 1) == 0);

    CHECK(UTIL_isIntStr("123abc", UTIL_npos) == 0);
    CHECK(UTIL_isIntStr("123abc", 3) != 0);
    CHECK(UTIL_isIntStr("123abc", 4) == 0);

    CHECK(UTIL_isIntStr("123 abc", UTIL_npos) == 0);
    CHECK(UTIL_isIntStr("123 abc", 3) != 0);
    CHECK(UTIL_isIntStr("123 abc", 4) == 0);

    CHECK(UTIL_isIntStr("-123abc", UTIL_npos) == 0);
    CHECK(UTIL_isIntStr("-123abc", 4) != 0);
    CHECK(UTIL_isIntStr("-123abc", 5) == 0);

    CHECK(UTIL_isIntStr("-123 abc", UTIL_npos) == 0);
    CHECK(UTIL_isIntStr("-123 abc", 4) != 0);
    CHECK(UTIL_isIntStr("-123 abc", 5) == 0);

    CHECK(UTIL_isIntStr("0", UTIL_npos) != 0);
    CHECK(UTIL_isIntStr("-0", UTIL_npos) != 0);
    CHECK(UTIL_isIntStr("-1", UTIL_npos) != 0);
    CHECK(UTIL_isIntStr("-123", UTIL_npos) != 0);
    CHECK(UTIL_isIntStr("1", UTIL_npos) != 0);
    CHECK(UTIL_isIntStr("123", UTIL_npos) != 0);



    CHECK(UTIL_isUIntStr(NULL, UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("123", 0) == 0);

    CHECK(UTIL_isUIntStr("a123", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("a", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("abc", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("-", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("-abc", UTIL_npos) == 0);

    CHECK(UTIL_isUIntStr("123abc", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("123abc", 3) != 0);
    CHECK(UTIL_isUIntStr("123abc", 4) == 0);

    CHECK(UTIL_isUIntStr("123 abc", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("123 abc", 3) != 0);
    CHECK(UTIL_isUIntStr("123 abc", 4) == 0);

    CHECK(UTIL_isUIntStr("-123abc", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("-123abc", 4) == 0);
    CHECK(UTIL_isUIntStr("-123abc", 5) == 0);

    CHECK(UTIL_isUIntStr("-123 abc", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("-123 abc", 4) == 0);
    CHECK(UTIL_isUIntStr("-123 abc", 5) == 0);

    CHECK(UTIL_isUIntStr("0", UTIL_npos) != 0);
    CHECK(UTIL_isUIntStr("-0", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("-1", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("-123", UTIL_npos) == 0);
    CHECK(UTIL_isUIntStr("1", UTIL_npos) != 0);
    CHECK(UTIL_isUIntStr("123", UTIL_npos) != 0);
}

TEST_CASE("string.h String Classification hex")
{
    const char* s1 = "3F5";

    CHECK(UTIL_isHexStr(s1, UTIL_npos) != 0);
    CHECK(UTIL_isHexStr("0123456789ABCDEF", UTIL_npos) != 0);
    CHECK(UTIL_isHexStr("0123456789abcdef", UTIL_npos) != 0);
    CHECK(UTIL_isHexStr("0123456789ABCDEF0123", UTIL_npos) != 0);

    CHECK(UTIL_isHexStr(NULL, UTIL_npos) == 0);
    CHECK(UTIL_isHexStr("", UTIL_npos) == 0);
    CHECK(UTIL_isHexStr("0x3F", UTIL_npos) == 0);

    for (int c = 0; c <= 0xFF; ++c)
    {
        const char chr = (char)c;
        const char hexStr[] = { '5', 'a', chr, 0 };
        bool expectedResult;

        if (((chr >= '0') && (chr <= '9')) || ((chr >= 'A') && (chr <= 'F')) || ((chr >= 'a') && (chr <= 'f'))) { expectedResult = true; }
        else { expectedResult = false; }

        if (chr == 0) { expectedResult = true; }
        if (expectedResult) { CHECK(UTIL_isHexStr(hexStr, UTIL_npos) != 0); }
        else { CHECK(UTIL_isHexStr(hexStr, UTIL_npos) == 0); }
    }

    const char* substrTest = "AB-06CD;12345-a4d902q";

    CHECK(UTIL_isHexStr(substrTest, UTIL_npos) == 0);
    CHECK(UTIL_isHexStr(substrTest + 0, 2) != 0);
    CHECK(UTIL_isHexStr(substrTest + 0, 3) == 0);
    CHECK(UTIL_isHexStr(substrTest + 3, 4) != 0);
    CHECK(UTIL_isHexStr(substrTest + 8, 5) != 0);
    CHECK(UTIL_isHexStr(substrTest + 8, 6) == 0);
    CHECK(UTIL_isHexStr(substrTest + 14, 6) != 0);
    CHECK(UTIL_isHexStr(substrTest + 14, 7) == 0);
    CHECK(UTIL_isHexStr(substrTest + 18, 1) != 0);
    CHECK(UTIL_isHexStr(substrTest + 20, 1) == 0);
    CHECK(UTIL_isHexStr(substrTest + 20, 2) == 0);

    substrTest = "12345-a4d902";

    CHECK(UTIL_isHexStr(substrTest, UTIL_npos) == 0);
    CHECK(UTIL_isHexStr(substrTest + 6, UTIL_npos) != 0);
    CHECK(UTIL_isHexStr(substrTest + 6, 100) != 0);
    CHECK(UTIL_isHexStr(substrTest + 5, 100) == 0);

    CHECK(UTIL_isHexStr(substrTest + 12, UTIL_npos) == 0);
    CHECK(UTIL_isHexStr(substrTest + 12, 5) == 0);
    CHECK(UTIL_isHexStr(substrTest + 1, 0) == 0);
}

TEST_CASE("string.h integer to string")
{
    char* end;
    char buffer[21];

    auto reset = [&]() {
        end = NULL;
        for (size_t i = 0; i < sizeof(buffer); ++i) { buffer[i] = '#'; }
        buffer[sizeof(buffer) - 1] = 0;
    };

#if 0
    const test_case_t tests[] = {
        // { .value = 1, .i8 = "1", .i16 = "1", .i32 = "1", .i64 = "1", .ui8 = "1", .ui16 = "1", .ui32 = "1", .ui64 = "1" },
        // { .value = 2, .i8 = "2", .i16 = "2", .i32 = "2", .i64 = "2", .ui8 = "2", .ui16 = "2", .ui32 = "2", .ui64 = "2" },
        // { .value = 123, .i8 = "123", .i16 = "123", .i32 = "123", .i64 = "123", .ui8 = "123", .ui16 = "123", .ui32 = "123", .ui64 = "123" },
        // { .value = -123, .i8 = "-123", .i16 = "-123", .i32 = "-123", .i64 = "-123", .ui8 = "133", .ui16 = "133", .ui32 = "133", .ui64 = "133" },
        // { .value = 1234, .i8 = "210", .i16 = "1234", .i32 = "1234", .i64 = "1234", .ui8 = "210", .ui16 = "1234", .ui32 = "1234", .ui64 = "1234" },
    };
#endif



#undef SiXtos_value
#define SiXtos_value (0)
    {
        reset();
        CHECK(strcmp(UTIL_i8tos(buffer, SiXtos_value, &end), "0") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_i16tos(buffer, SiXtos_value, &end), "0") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_i32tos(buffer, SiXtos_value, &end), "0") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_i64tos(buffer, SiXtos_value, &end), "0") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui8tos(buffer, SiXtos_value, &end), "0") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui16tos(buffer, SiXtos_value, &end), "0") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui32tos(buffer, SiXtos_value, &end), "0") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui64tos(buffer, SiXtos_value, &end), "0") == 0);
        CHECK(end == (buffer + 1));
    }
#undef SiXtos_value



#undef SiXtos_value
#define SiXtos_value (-2)
    {
        reset();
        CHECK(strcmp(UTIL_i8tos(buffer, SiXtos_value, &end), "-2") == 0);
        CHECK(end == (buffer + 2));

        reset();
        CHECK(strcmp(UTIL_i16tos(buffer, SiXtos_value, &end), "-2") == 0);
        CHECK(end == (buffer + 2));

        reset();
        CHECK(strcmp(UTIL_i32tos(buffer, SiXtos_value, &end), "-2") == 0);
        CHECK(end == (buffer + 2));

        reset();
        CHECK(strcmp(UTIL_i64tos(buffer, SiXtos_value, &end), "-2") == 0);
        CHECK(end == (buffer + 2));

        reset();
        CHECK(strcmp(UTIL_ui8tos(buffer, SiXtos_value, &end), "254") == 0);
        CHECK(end == (buffer + 3));

        reset();
        CHECK(strcmp(UTIL_ui16tos(buffer, SiXtos_value, &end), "65534") == 0);
        CHECK(end == (buffer + 5));

        reset();
        CHECK(strcmp(UTIL_ui32tos(buffer, SiXtos_value, &end), "4294967294") == 0);
        CHECK(end == (buffer + 10));

        reset();
        CHECK(strcmp(UTIL_ui64tos(buffer, SiXtos_value, &end), "18446744073709551614") == 0);
        CHECK(end == (buffer + 20));
    }
#undef SiXtos_value



#undef SiXtos_value
#define SiXtos_value (-1)
    {
        reset();
        CHECK(strcmp(UTIL_i8tos(buffer, SiXtos_value, &end), "-1") == 0);
        CHECK(end == (buffer + 2));

        reset();
        CHECK(strcmp(UTIL_i16tos(buffer, SiXtos_value, &end), "-1") == 0);
        CHECK(end == (buffer + 2));

        reset();
        CHECK(strcmp(UTIL_i32tos(buffer, SiXtos_value, &end), "-1") == 0);
        CHECK(end == (buffer + 2));

        reset();
        CHECK(strcmp(UTIL_i64tos(buffer, SiXtos_value, &end), "-1") == 0);
        CHECK(end == (buffer + 2));

        reset();
        CHECK(strcmp(UTIL_ui8tos(buffer, SiXtos_value, &end), "255") == 0);
        CHECK(end == (buffer + 3));

        reset();
        CHECK(strcmp(UTIL_ui16tos(buffer, SiXtos_value, &end), "65535") == 0);
        CHECK(end == (buffer + 5));

        reset();
        CHECK(strcmp(UTIL_ui32tos(buffer, SiXtos_value, &end), "4294967295") == 0);
        CHECK(end == (buffer + 10));

        reset();
        CHECK(strcmp(UTIL_ui64tos(buffer, SiXtos_value, &end), "18446744073709551615") == 0);
        CHECK(end == (buffer + 20));
    }
#undef SiXtos_value



#undef SiXtos_value
#define SiXtos_value (1)
    {
        reset();
        CHECK(strcmp(UTIL_i8tos(buffer, SiXtos_value, &end), "1") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_i16tos(buffer, SiXtos_value, &end), "1") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_i32tos(buffer, SiXtos_value, &end), "1") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_i64tos(buffer, SiXtos_value, &end), "1") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui8tos(buffer, SiXtos_value, &end), "1") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui16tos(buffer, SiXtos_value, &end), "1") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui32tos(buffer, SiXtos_value, &end), "1") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui64tos(buffer, SiXtos_value, &end), "1") == 0);
        CHECK(end == (buffer + 1));
    }
#undef SiXtos_value



#undef SiXtos_value
#define SiXtos_value (5)
    {
        reset();
        CHECK(strcmp(UTIL_i8tos(buffer, SiXtos_value, &end), "5") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_i16tos(buffer, SiXtos_value, &end), "5") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_i32tos(buffer, SiXtos_value, &end), "5") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_i64tos(buffer, SiXtos_value, &end), "5") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui8tos(buffer, SiXtos_value, &end), "5") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui16tos(buffer, SiXtos_value, &end), "5") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui32tos(buffer, SiXtos_value, &end), "5") == 0);
        CHECK(end == (buffer + 1));

        reset();
        CHECK(strcmp(UTIL_ui64tos(buffer, SiXtos_value, &end), "5") == 0);
        CHECK(end == (buffer + 1));
    }
#undef SiXtos_value



    reset();
    CHECK(strcmp(UTIL_i8tos(buffer, INT8_MIN, &end), "-128") == 0);
    CHECK(end == (buffer + 4));

    reset();
    CHECK(strcmp(UTIL_i16tos(buffer, INT8_MIN, &end), "-128") == 0);
    CHECK(end == (buffer + 4));

    reset();
    CHECK(strcmp(UTIL_i32tos(buffer, INT8_MIN, &end), "-128") == 0);
    CHECK(end == (buffer + 4));

    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, INT8_MIN, &end), "-128") == 0);
    CHECK(end == (buffer + 4));

    reset();
    CHECK(strcmp(UTIL_ui8tos(buffer, INT8_MIN, &end), "128") == 0);
    CHECK(end == (buffer + 3));



    reset();
    CHECK(strcmp(UTIL_i8tos(buffer, INT8_MAX, &end), "127") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_i16tos(buffer, INT8_MAX, &end), "127") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_i32tos(buffer, INT8_MAX, &end), "127") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, INT8_MAX, &end), "127") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_ui8tos(buffer, INT8_MAX, &end), "127") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_ui16tos(buffer, INT8_MAX, &end), "127") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_ui32tos(buffer, INT8_MAX, &end), "127") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_ui64tos(buffer, INT8_MAX, &end), "127") == 0);
    CHECK(end == (buffer + 3));



    reset();
    CHECK(strcmp(UTIL_i8tos(buffer, (int8_t)UINT8_MAX, &end), "-1") == 0);
    CHECK(end == (buffer + 2));

    reset();
    CHECK(strcmp(UTIL_i16tos(buffer, UINT8_MAX, &end), "255") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_i32tos(buffer, UINT8_MAX, &end), "255") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, UINT8_MAX, &end), "255") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_ui8tos(buffer, UINT8_MAX, &end), "255") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_ui16tos(buffer, UINT8_MAX, &end), "255") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_ui32tos(buffer, UINT8_MAX, &end), "255") == 0);
    CHECK(end == (buffer + 3));

    reset();
    CHECK(strcmp(UTIL_ui64tos(buffer, UINT8_MAX, &end), "255") == 0);
    CHECK(end == (buffer + 3));



    reset();
    CHECK(strcmp(UTIL_i16tos(buffer, INT16_MIN, &end), "-32768") == 0);
    CHECK(end == (buffer + 6));

    reset();
    CHECK(strcmp(UTIL_i32tos(buffer, INT16_MIN, &end), "-32768") == 0);
    CHECK(end == (buffer + 6));

    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, INT16_MIN, &end), "-32768") == 0);
    CHECK(end == (buffer + 6));

    reset();
    CHECK(strcmp(UTIL_ui16tos(buffer, INT16_MIN, &end), "32768") == 0);
    CHECK(end == (buffer + 5));



    reset();
    CHECK(strcmp(UTIL_i16tos(buffer, INT16_MAX, &end), "32767") == 0);
    CHECK(end == (buffer + 5));

    reset();
    CHECK(strcmp(UTIL_i32tos(buffer, INT16_MAX, &end), "32767") == 0);
    CHECK(end == (buffer + 5));

    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, INT16_MAX, &end), "32767") == 0);
    CHECK(end == (buffer + 5));

    reset();
    CHECK(strcmp(UTIL_ui16tos(buffer, INT16_MAX, &end), "32767") == 0);
    CHECK(end == (buffer + 5));

    reset();
    CHECK(strcmp(UTIL_ui32tos(buffer, INT16_MAX, &end), "32767") == 0);
    CHECK(end == (buffer + 5));

    reset();
    CHECK(strcmp(UTIL_ui64tos(buffer, INT16_MAX, &end), "32767") == 0);
    CHECK(end == (buffer + 5));



    reset();
    CHECK(strcmp(UTIL_i16tos(buffer, (int16_t)UINT16_MAX, &end), "-1") == 0);
    CHECK(end == (buffer + 2));

    reset();
    CHECK(strcmp(UTIL_i32tos(buffer, UINT16_MAX, &end), "65535") == 0);
    CHECK(end == (buffer + 5));

    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, UINT16_MAX, &end), "65535") == 0);
    CHECK(end == (buffer + 5));

    reset();
    CHECK(strcmp(UTIL_ui16tos(buffer, UINT16_MAX, &end), "65535") == 0);
    CHECK(end == (buffer + 5));

    reset();
    CHECK(strcmp(UTIL_ui32tos(buffer, UINT16_MAX, &end), "65535") == 0);
    CHECK(end == (buffer + 5));

    reset();
    CHECK(strcmp(UTIL_ui64tos(buffer, UINT16_MAX, &end), "65535") == 0);
    CHECK(end == (buffer + 5));



    reset();
    CHECK(strcmp(UTIL_i32tos(buffer, INT32_MIN, &end), "-2147483648") == 0);
    CHECK(end == (buffer + 11));

    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, INT32_MIN, &end), "-2147483648") == 0);
    CHECK(end == (buffer + 11));

    reset();
    CHECK(strcmp(UTIL_ui32tos(buffer, INT32_MIN, &end), "2147483648") == 0);
    CHECK(end == (buffer + 10));



    reset();
    CHECK(strcmp(UTIL_i32tos(buffer, INT32_MAX, &end), "2147483647") == 0);
    CHECK(end == (buffer + 10));

    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, INT32_MAX, &end), "2147483647") == 0);
    CHECK(end == (buffer + 10));

    reset();
    CHECK(strcmp(UTIL_ui32tos(buffer, INT32_MAX, &end), "2147483647") == 0);
    CHECK(end == (buffer + 10));

    reset();
    CHECK(strcmp(UTIL_ui64tos(buffer, INT32_MAX, &end), "2147483647") == 0);
    CHECK(end == (buffer + 10));



    reset();
    CHECK(strcmp(UTIL_i32tos(buffer, (int32_t)UINT32_MAX, &end), "-1") == 0);
    CHECK(end == (buffer + 2));

    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, UINT32_MAX, &end), "4294967295") == 0);
    CHECK(end == (buffer + 10));

    reset();
    CHECK(strcmp(UTIL_ui32tos(buffer, UINT32_MAX, &end), "4294967295") == 0);
    CHECK(end == (buffer + 10));

    reset();
    CHECK(strcmp(UTIL_ui64tos(buffer, UINT32_MAX, &end), "4294967295") == 0);
    CHECK(end == (buffer + 10));



    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, INT64_MIN, &end), "-9223372036854775808") == 0);
    CHECK(end == (buffer + 20));

    reset();
    CHECK(strcmp(UTIL_ui64tos(buffer, INT64_MIN, &end), "9223372036854775808") == 0);
    CHECK(end == (buffer + 19));



    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, INT64_MAX, &end), "9223372036854775807") == 0);
    CHECK(end == (buffer + 19));

    reset();
    CHECK(strcmp(UTIL_ui64tos(buffer, INT64_MAX, &end), "9223372036854775807") == 0);
    CHECK(end == (buffer + 19));



    reset();
    CHECK(strcmp(UTIL_i64tos(buffer, (int64_t)UINT64_MAX, &end), "-1") == 0);
    CHECK(end == (buffer + 2));

    reset();
    CHECK(strcmp(UTIL_ui64tos(buffer, UINT64_MAX, &end), "18446744073709551615") == 0);
    CHECK(end == (buffer + 20));
}

TEST_CASE("string.h string to signed integer") {}

#define CHECK_STOUI_INVAL(_str)  \
    {                            \
        init((_str));            \
        UTIL_stoui8(str, &end);  \
        CHECK(end == (str + 0)); \
        CHECK(errno == EINVAL);  \
                                 \
        init((_str));            \
        UTIL_stoui16(str, &end); \
        CHECK(end == (str + 0)); \
        CHECK(errno == EINVAL);  \
                                 \
        init((_str));            \
        UTIL_stoui32(str, &end); \
        CHECK(end == (str + 0)); \
        CHECK(errno == EINVAL);  \
                                 \
        init((_str));            \
        UTIL_stoui64(str, &end); \
        CHECK(end == (str + 0)); \
        CHECK(errno == EINVAL);  \
    }

TEST_CASE("string.h string to unsigned integer")
{
    const char* input;
    const char* str;
    const char* end;

    auto init = [&](const char* s) {
        str = s;
        errno = 0;
    };



    CHECK_STOUI_INVAL(NULL);
    CHECK_STOUI_INVAL("");
    CHECK_STOUI_INVAL("a");
    CHECK_STOUI_INVAL("-");
    CHECK_STOUI_INVAL("+");



    input = "0";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == 0);
    CHECK(end == (str + 1));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == 0);
    CHECK(end == (str + 1));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == 0);
    CHECK(end == (str + 1));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == 0);
    CHECK(end == (str + 1));
    CHECK(errno == 0);



    input = "1";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == 1);
    CHECK(end == (str + 1));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == 1);
    CHECK(end == (str + 1));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == 1);
    CHECK(end == (str + 1));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == 1);
    CHECK(end == (str + 1));
    CHECK(errno == 0);



    input = "123";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == 123);
    CHECK(end == (str + 3));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == 123);
    CHECK(end == (str + 3));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == 123);
    CHECK(end == (str + 3));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == 123);
    CHECK(end == (str + 3));
    CHECK(errno == 0);



    input = "255";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == 255);
    CHECK(end == (str + 3));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == 255);
    CHECK(end == (str + 3));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == 255);
    CHECK(end == (str + 3));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == 255);
    CHECK(end == (str + 3));
    CHECK(errno == 0);



    input = "256";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == UINT8_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == 256);
    CHECK(end == (str + 3));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == 256);
    CHECK(end == (str + 3));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == 256);
    CHECK(end == (str + 3));
    CHECK(errno == 0);

    for (int i = 257; i <= 357; ++i)
    {
        const auto tmp = std::to_string(i);
        init(tmp.c_str());
        CHECK(UTIL_stoui8(str, &end) == UINT8_MAX);
        CHECK(errno == ERANGE);
    }



    input = "65535";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == UINT8_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == 65535);
    CHECK(end == (str + 5));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == 65535);
    CHECK(end == (str + 5));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == 65535);
    CHECK(end == (str + 5));
    CHECK(errno == 0);



    input = "65536";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == UINT8_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == UINT16_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == 65536);
    CHECK(end == (str + 5));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == 65536);
    CHECK(end == (str + 5));
    CHECK(errno == 0);

    for (int i = 65537; i <= 65637; ++i)
    {
        const auto tmp = std::to_string(i);
        init(tmp.c_str());
        CHECK(UTIL_stoui16(str, &end) == UINT16_MAX);
        CHECK(errno == ERANGE);
    }



    input = "4294967295";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == UINT8_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == UINT16_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == 4294967295);
    CHECK(end == (str + 10));
    CHECK(errno == 0);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == 4294967295);
    CHECK(end == (str + 10));
    CHECK(errno == 0);



    input = "4294967296";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == UINT8_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == UINT16_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == UINT32_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == 4294967296);
    CHECK(end == (str + 10));
    CHECK(errno == 0);

    for (uint64_t i = 4294967297; i <= 4294967397; ++i)
    {
        const auto tmp = std::to_string(i);
        init(tmp.c_str());
        CHECK(UTIL_stoui32(str, &end) == UINT32_MAX);
        CHECK(errno == ERANGE);
    }



    input = "18446744073709551615";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == UINT8_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == UINT16_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == UINT32_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == 18446744073709551615);
    CHECK(end == (str + 20));
    CHECK(errno == 0);



    input = "18446744073709551616";

    init(input);
    CHECK(UTIL_stoui8(str, &end) == UINT8_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui16(str, &end) == UINT16_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui32(str, &end) == UINT32_MAX);
    CHECK(errno == ERANGE);

    init(input);
    CHECK(UTIL_stoui64(str, &end) == UINT64_MAX);
    CHECK(errno == ERANGE);

    for (int i = 1617; i <= 1717; ++i)
    {
        const auto tmp = "1844674407370955" + std::to_string(i);
        init(tmp.c_str());
        CHECK(UTIL_stoui64(str, &end) == UINT64_MAX);
        CHECK(errno == ERANGE);
    }
}

TEST_CASE("string.h integer to hex string")
{
    char* end;
    char buffer[17];

    auto reset = [&]() {
        end = NULL;
        for (size_t i = 0; i < sizeof(buffer); ++i) { buffer[i] = '#'; }
        buffer[sizeof(buffer) - 1] = 0;
    };



    reset();
    CHECK(strcmp(UTIL_ui8toxs(buffer, 0xBC, &end), "BC") == 0);
    CHECK(end == buffer + 2);

    reset();
    CHECK(strcmp(UTIL_ui16toxs(buffer, 0x5678, &end), "5678") == 0);
    CHECK(end == buffer + 4);

    reset();
    CHECK(strcmp(UTIL_ui32toxs(buffer, 0x89ABCDEF, &end), "89ABCDEF") == 0);
    CHECK(end == buffer + 8);

    reset();
    CHECK(strcmp(UTIL_ui64toxs(buffer, 0x0123456789ABCDEF, &end), "0123456789ABCDEF") == 0);
    CHECK(end == buffer + 16);



    reset();
    CHECK(strcmp(UTIL_i8toxs(buffer, -1, &end), "FF") == 0);
    CHECK(end == buffer + 2);

    reset();
    CHECK(strcmp(UTIL_i16toxs(buffer, -5103, &end), "EC11") == 0);
    CHECK(end == buffer + 4);

    reset();
    CHECK(strcmp(UTIL_i32toxs(buffer, -701234, &end), "FFF54CCE") == 0);
    CHECK(end == buffer + 8);

    reset();
    CHECK(strcmp(UTIL_i64toxs(buffer, -123456789, &end), "FFFFFFFFF8A432EB") == 0);
    CHECK(end == buffer + 16);
}

TEST_CASE("string.h hex string to integer")
{
    const char* str;

    auto reset = [&](const char* s) {
        str = s;
        errno = 0;
    };



    reset("AbCdEf0123456789");
    CHECK(UTIL_xstoui8(str) == 0xAB);
    CHECK(UTIL_xstoui16(str + 3) == 0xDEF0);
    CHECK(UTIL_xstoui32(str + 5) == 0xF0123456);
    CHECK(UTIL_xstoui64(str) == 0xABCDEF0123456789ull);
    CHECK(UTIL_xstoi8(str) == -85);
    CHECK(UTIL_xstoi16(str + 3) == -8464);
    CHECK(UTIL_xstoi32(str + 5) == -267242410);
    CHECK(UTIL_xstoi64(str) == -6066930334832433271);
    CHECK(errno == 0);



    const char* badStrings[] = {
        NULL,
        "",
        "2",
        "FG00000000000000",
    };

    for (size_t i = 0; i < SIZEOF_ARRAY(badStrings); ++i)
    {
        volatile int64_t d;

        reset(badStrings[i]);
        d = UTIL_xstoui8(str);
        CHECK(errno == EINVAL);

        reset(badStrings[i]);
        d = UTIL_xstoui16(str);
        CHECK(errno == EINVAL);

        reset(badStrings[i]);
        d = UTIL_xstoui32(str);
        CHECK(errno == EINVAL);

        reset(badStrings[i]);
        d = UTIL_xstoui64(str);
        CHECK(errno == EINVAL);

        reset(badStrings[i]);
        d = UTIL_xstoi8(str);
        CHECK(errno == EINVAL);

        reset(badStrings[i]);
        d = UTIL_xstoi16(str);
        CHECK(errno == EINVAL);

        reset(badStrings[i]);
        d = UTIL_xstoi32(str);
        CHECK(errno == EINVAL);

        reset(badStrings[i]);
        d = UTIL_xstoi64(str);
        CHECK(errno == EINVAL);

        (void)d;
    }
}

TEST_CASE("string.h data buffer to hex string")
{
    char* end;
    char buffer[12];

    auto reset = [&]() {
        end = NULL;
        for (size_t i = 0; i < sizeof(buffer); ++i) { buffer[i] = '#'; }
        buffer[sizeof(buffer) - 1] = 0;
    };

    const uint8_t data[] = { 0x30, 0x35, 'A', 'b' };



    reset();
    CHECK(strcmp(UTIL_dataToHexStr(buffer, data, sizeof(data), &end), "30354162") == 0);
    CHECK(end == buffer + 8);

    reset();
    CHECK(strcmp(UTIL_dataToHexStr(buffer, data, 0, &end), "") == 0);
    CHECK(end == buffer + 0);



    reset();
    CHECK(strcmp(UTIL_dataToHexStrDelim(buffer, data, sizeof(data), '$', &end), "30$35$41$62") == 0);
    CHECK(end == buffer + 11);

    reset();
    CHECK(strcmp(UTIL_dataToHexStrDelim(buffer, data, 0, '$', &end), "") == 0);
    CHECK(end == buffer + 0);
}
