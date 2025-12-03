/*
author          Oliver Blaser
date            21.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_TEST_UNIT_STRING_HPP
#define IG_TEST_UNIT_STRING_HPP

#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>

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

TEST_CASE("string.h signed integer to string") {}

TEST_CASE("string.h unsigned integer to string") {}

TEST_CASE("string.h string to signed integer") {}

TEST_CASE("string.h string to unsigned integer") {}

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



#endif // IG_TEST_UNIT_STRING_HPP
