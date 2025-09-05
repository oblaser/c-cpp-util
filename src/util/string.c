/*
author          Oliver Blaser
date            30.08.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#include "string.h"



static const char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };



static uint8_t xctonv(char ch);



char* UTIL_strcpy(char* dst, const char* src, char** end)
{
    if (dst && src)
    {
        char* d = dst;
        const char* s = src;

        while (*s != 0)
        {
            *d = *s;
            ++d;
            ++s;
        }

        *d = 0;

        if (end) { *end = d; }
    }

    return dst;
}

char* UTIL_strncpy(char* dst, const char* src, size_t n, char** end)
{
    if (dst && src)
    {
        size_t cnt = 0;

        while ((*(src + cnt) != 0) && (cnt < n))
        {
            *(dst + cnt) = *(src + cnt);
            ++cnt;
        }

        if (cnt < n) { *(dst + cnt) = 0; }

        if (end) { *end = (dst + cnt); }
    }

    return dst;
}

char* UTIL_strcat(char* dst, const char* src, char** end)
{
    if (dst && src)
    {
        char* d = dst;
        const char* s = src;

        while (*d != 0) { ++d; }

        while (*s != 0)
        {
            *d = *s;
            ++d;
            ++s;
        }

        *d = 0;

        if (end) { *end = d; }
    }

    return dst;
}

char* UTIL_strncat(char* dst, const char* src, size_t n, char** end)
{
    if (dst && src)
    {
        char* d = dst;
        const char* s = src;
        size_t cnt = 0;

        while (*d != 0) { ++d; }

        while ((*s != 0) && (cnt < n))
        {
            *d = *s;
            ++d;
            ++s;
            ++cnt;
        }

        *d = 0;

        if (end) { *end = d; }
    }

    return dst;
}

char* UTIL_strlower_ascii(char* str)
{
    if (str)
    {
        char* p = str;

        while (*p != 0)
        {
            if (UTIL_isUpper(*p)) { *p += 32; }
            ++p;
        }
    }

    return str;
}

char* UTIL_strupper_ascii(char* str)
{
    if (str)
    {
        char* p = str;

        while (*p != 0)
        {
            if (UTIL_isLower(*p)) { *p -= 32; }
            ++p;
        }
    }

    return str;
}



size_t UTIL_strlen(const char* str)
{
    if (!str) { return 0; }

    size_t cnt = 0;

    while (*(str + cnt) != 0) { ++cnt; }

    return cnt;
}

size_t UTIL_strnlen(const char* str, size_t n)
{
    if (!str) { return 0; }

    size_t cnt = 0;

    while ((*(str + cnt) != 0) && (cnt < n)) { ++cnt; }

    return cnt;
}

int UTIL_strcmp(const char* lhs, const char* rhs)
{
    int r = 0;

    if (lhs && rhs)
    {
        while ((*lhs != 0) && (*rhs != 0))
        {
            r = ((unsigned char)(*lhs) - (unsigned char)(*rhs));

            if (r != 0) { break; }

            ++lhs;
            ++rhs;
        }

        if ((*lhs != 0) || (*rhs != 0)) { r = ((unsigned char)(*lhs) - (unsigned char)(*rhs)); }
    }

    return r;
}

int UTIL_strncmp(const char* lhs, const char* rhs, size_t n)
{
    int r = 0;

    if (lhs && rhs)
    {
        size_t cnt = 0;

        while ((*lhs != 0) && (*rhs != 0) && (cnt < n))
        {
            r = ((unsigned char)(*lhs) - (unsigned char)(*rhs));

            if (r != 0) { break; }

            ++lhs;
            ++rhs;
            ++cnt;
        }

        if (((*lhs != 0) || (*rhs != 0)) && (cnt < n)) { r = ((unsigned char)(*lhs) - (unsigned char)(*rhs)); }
    }

    return r;
}

const char* UTIL_strchr(const char* str, int ch)
{
    if (!str) { return NULL; }

    const char* p = str;

    while (*p != 0)
    {
        if (*p == (char)ch) { return p; }
        ++p;
    }

    if (ch == 0) { return p; }
    return NULL;
}

const char* UTIL_strnchr(const char* str, int ch, size_t n)
{
    if (!str) { return NULL; }

    const char* p = str;

    while ((*p != 0) && ((size_t)(p - str) < n))
    {
        if (*p == (char)ch) { return p; }
        ++p;
    }

    if ((ch == 0) && (*p == 0)) { return p; }

    return NULL;
}

int UTIL_isIntStr(const char* str, size_t count)
{
    if (str && (str[0] == '-'))
    {
        ++str;
        --count;
    }

    return UTIL_isUIntStr(str, count);
}

int UTIL_isUIntStr(const char* str, size_t count)
{
    int r = 0;

    if (str && (*str != 0) && (count > 0))
    {
        r = 1;

        while ((*str != 0) && (count > 0))
        {
            if ((*str < '0') || (*str > '9'))
            {
                r = 0;
                break;
            }

            ++str;
            --count;
        }
    }

    return r;
}

int UTIL_isHexStr(const char* str, size_t count)
{
    int r = 0;

    if (str && (*str != 0) && (count > 0))
    {
        r = 1;

        while ((*str != 0) && (count > 0))
        {
            if (!( // clang-format off
                ((*str >= '0') && (*str <= '9')) ||
                ((*str >= 'A') && (*str <= 'F')) ||
                ((*str >= 'a') && (*str <= 'f'))
                )) // clang-format on
            {
                r = 0;
                break;
            }

            ++str;
            --count;
        }
    }

    return r;
}

// https://en.cppreference.com/w/c/string/byte/strtol.html
// https://en.cppreference.com/w/cpp/string/basic_string/stol
// https://en.cppreference.com/w/c/error/errno_macros.html

char* UTIL_ui8toxs(char* dst, uint8_t value, char** end)
{
    if (dst)
    {
        *(dst + 0) = hexDigits[value >> 4];
        *(dst + 1) = hexDigits[value & 0x0F];
        *(dst + 2) = 0;

        if (end) { *end = dst + 2; }
    }

    return dst;
}

char* UTIL_ui16toxs(char* dst, uint16_t value, char** end)
{
    if (dst)
    {
        *(dst + 0) = hexDigits[value >> 12];
        *(dst + 1) = hexDigits[(value >> 8) & 0x000F];
        *(dst + 2) = hexDigits[(value >> 4) & 0x000F];
        *(dst + 3) = hexDigits[value & 0x000F];
        *(dst + 4) = 0;

        if (end) { *end = dst + 4; }
    }

    return dst;
}

char* UTIL_ui32toxs(char* dst, uint32_t value, char** end)
{
    if (dst)
    {
        *(dst + 0) = hexDigits[value >> 28];
        *(dst + 1) = hexDigits[(value >> 24) & 0x0000000F];
        *(dst + 2) = hexDigits[(value >> 20) & 0x0000000F];
        *(dst + 3) = hexDigits[(value >> 16) & 0x0000000F];
        *(dst + 4) = hexDigits[(value >> 12) & 0x0000000F];
        *(dst + 5) = hexDigits[(value >> 8) & 0x0000000F];
        *(dst + 6) = hexDigits[(value >> 4) & 0x0000000F];
        *(dst + 7) = hexDigits[value & 0x0000000F];
        *(dst + 8) = 0;

        if (end) { *end = dst + 8; }
    }

    return dst;
}

char* UTIL_ui64toxs(char* dst, uint64_t value, char** end)
{
    if (dst)
    {
        *(dst + 0) = hexDigits[value >> 60];
        *(dst + 1) = hexDigits[(value >> 56) & 0x000000000000000Full];
        *(dst + 2) = hexDigits[(value >> 52) & 0x000000000000000Full];
        *(dst + 3) = hexDigits[(value >> 48) & 0x000000000000000Full];
        *(dst + 4) = hexDigits[(value >> 44) & 0x000000000000000Full];
        *(dst + 5) = hexDigits[(value >> 40) & 0x000000000000000Full];
        *(dst + 6) = hexDigits[(value >> 36) & 0x000000000000000Full];
        *(dst + 7) = hexDigits[(value >> 32) & 0x000000000000000Full];
        *(dst + 8) = hexDigits[(value >> 28) & 0x000000000000000Full];
        *(dst + 9) = hexDigits[(value >> 24) & 0x000000000000000Full];
        *(dst + 10) = hexDigits[(value >> 20) & 0x000000000000000Full];
        *(dst + 11) = hexDigits[(value >> 16) & 0x000000000000000Full];
        *(dst + 12) = hexDigits[(value >> 12) & 0x000000000000000Full];
        *(dst + 13) = hexDigits[(value >> 8) & 0x000000000000000Full];
        *(dst + 14) = hexDigits[(value >> 4) & 0x000000000000000Full];
        *(dst + 15) = hexDigits[value & 0x000000000000000Full];
        *(dst + 16) = 0;

        if (end) { *end = dst + 16; }
    }

    return dst;
}

uint8_t UTIL_xstoui8(const char* str)
{
    uint8_t r = 0;

    if (str && UTIL_isHex(*str) && UTIL_isHex(*(str + 1)))
    {
        r = xctonv(*str);
        ++str;
        r <<= 4;
        r |= xctonv(*str);
    }
    else { errno = EINVAL; }

    return r;
}

uint16_t UTIL_xstoui16(const char* str)
{
    uint16_t r = 0;

    if (str)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            r <<= 4;
            r |= xctonv(*(str + i));

            if (!UTIL_isHex(*(str + i))) { errno = EINVAL; }
        }
    }
    else { errno = EINVAL; }

    return r;
}

uint32_t UTIL_xstoui32(const char* str)
{
    uint32_t r = 0;

    if (str)
    {
        for (size_t i = 0; i < 8; ++i)
        {
            r <<= 4;
            r |= xctonv(*(str + i));

            if (!UTIL_isHex(*(str + i))) { errno = EINVAL; }
        }
    }
    else { errno = EINVAL; }

    return r;
}

uint64_t UTIL_xstoui64(const char* str)
{
    uint64_t r = 0;

    if (str)
    {
        for (size_t i = 0; i < 16; ++i)
        {
            r <<= 4;
            r |= xctonv(*(str + i));

            if (!UTIL_isHex(*(str + i))) { errno = EINVAL; }
        }
    }
    else { errno = EINVAL; }

    return r;
}

char* UTIL_dataToHexStr(char* dst, const uint8_t* data, size_t count, char** end)
{
    if (dst)
    {
        char* p = dst;

        for (size_t i = 0; i < count; ++i)
        {
            *(p++) = hexDigits[*(data + i) >> 4];
            *(p++) = hexDigits[*(data + i) & 0x0F];
        }

        *p = 0;

        if (end) { *end = p; }
    }

    return dst;
}

char* UTIL_dataToHexStrDelim(char* dst, const uint8_t* data, size_t count, char delimiter, char** end)
{
    if (dst)
    {
        char* p = dst;

        for (size_t i = 0; i < count; ++i)
        {
            if (i > 0) { *(p++) = delimiter; }

            *(p++) = hexDigits[*(data + i) >> 4];
            *(p++) = hexDigits[*(data + i) & 0x0F];
        }

        *p = 0;

        if (end) { *end = p; }
    }

    return dst;
}



/**
 * @brief Converts a hex character to it's nibbles value.
 *
 * No error checking, pure and thus potentially erroneous conversion.
 *
 */
uint8_t xctonv(char ch)
{
    // make upper case
    if ((ch >= 'a') && (ch <= 'f')) { ch -= 32; }

    uint8_t r = 0;

    while (r < 16)
    {
        if (hexDigits[r] == ch) { break; }
        ++r;
    }

    return r;
}
