/*
author          Oliver Blaser
date            21.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>

#include "string.h"



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

    while ((*p != 0) && ((p - str) < n))
    {
        if (*p == (char)ch) { return p; }
        ++p;
    }

    if ((ch == 0) && (*p == 0)) { return p; }
    return NULL;
}
