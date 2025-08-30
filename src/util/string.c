/*
author          Oliver Blaser
date            21.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>

#include "string.h"



char* UTIL_strcpy(char* dst, const char* src, const char** end)
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

char* UTIL_strncpy(char* dst, const char* src, size_t n, const char** end)
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

char* UTIL_strcat(char* dst, const char* src)
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
    }

    return dst;
}

char* UTIL_strncat(char* dst, const char* src, size_t n)
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
