/*
author          Oliver Blaser
date            12.02.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#include "../util/string.h"
#include "version.h"



static const char identDelimiter = '.'; // identifier delimiter
static const char prDelimiter = '-';
static const char buildDelimiter = '+';



void UTIL_semver_clear(UTIL_semver_t* v)
{
    v->major = 0;
    v->minor = 0;
    v->patch = 0;
    v->prCount = 0;
    v->buildCount = 0;
}

int UTIL_semver_setPrBuild(UTIL_semver_t* v, const char* const * pr, size_t prCount, const char* const * build, size_t buildCount)
{
    // TODO skip empty identifiers



    // check size

    size_t reqSize = 0;

    for (size_t i = 0; i < prCount; ++i)
    {
        reqSize += UTIL_strlen(*(pr + i));
        ++reqSize; // null terminator
        reqSize += sizeof(uintptr_t);
    }

    for (size_t i = 0; i < buildCount; ++i)
    {
        reqSize += UTIL_strlen(*(build + i));
        ++reqSize; // null terminator
        reqSize += sizeof(uintptr_t);
    }

    if (reqSize > v->stackSize)
    {
        errno = ENOMEM;
        return -1;
    }



    // copy

    v->prCount = prCount;
    v->buildCount = buildCount;

    char* p = (char*)(v->stack);
    _Static_assert((sizeof(**pr) == 1) && (sizeof(**build) == 1), "sizeof(char) is expected to be 1");
    _Static_assert((sizeof(uintptr_t) == sizeof(p)) && (sizeof(uintptr_t) == sizeof(char*)), "sizeof(uintptr_t) is expected to be equal to sizeof(char*)");

    for (size_t i = 0; i < prCount; ++i)
    {
        *((uintptr_t*)(v->stack + v->stackSize - ((i + 1) * sizeof(uintptr_t)))) = (uintptr_t)p;

        const char* prStr = *(pr + i);
        while (*prStr != 0)
        {
            *p = *prStr;
            ++p;
            ++prStr;
        }

        *p = 0;
        ++p;
    }

    for (size_t i = 0; i < buildCount; ++i)
    {
        *((uintptr_t*)(v->stack + v->stackSize - (prCount * sizeof(uintptr_t)) - ((i + 1) * sizeof(uintptr_t)))) = (uintptr_t)p;

        const char* buildStr = *(build + i);
        while (*buildStr != 0)
        {
            *p = *buildStr;
            ++p;
            ++buildStr;
        }

        *p = 0;
        ++p;
    }

    return 0;
}

// TODO rm these two headers
#include <stdio.h>
#include <string.h>
char* UTIL_semvertos(char* dst, size_t size, const UTIL_semver_t* v, char** end)
{
#warning "TODO size checks, currently assuming sufficent destination buffer size"
    (void)size;
    (void)end;

    // TODO decimal string conversion from util/string.h instead of <string.h>
    sprintf(dst, "%i.%i.%i", v->major, v->minor, v->patch);
    char* p = dst + strlen(dst);
    size_t cnt = 0;

    for (size_t i = 0; i < v->prCount; ++i)
    {
        const char* identifier = (char*)(*((uintptr_t*)(v->stack + v->stackSize - ((i + 1) * sizeof(uintptr_t)))));

        if (i == 0) { *p = prDelimiter; }
        else { *p = identDelimiter; }
        ++p;
        ++cnt;

        while (*identifier != 0)
        {
            *p = *identifier;
            ++p;
            ++cnt;
            ++identifier;
        }
    }

    for (size_t i = 0; i < v->buildCount; ++i)
    {
        const char* identifier = (char*)(*((uintptr_t*)(v->stack + v->stackSize - (v->prCount * sizeof(uintptr_t)) - ((i + 1) * sizeof(uintptr_t)))));

        if (i == 0) { *p = buildDelimiter; }
        else { *p = identDelimiter; }
        ++p;
        ++cnt;

        while (*identifier != 0)
        {
            *p = *identifier;
            ++p;
            ++cnt;
            ++identifier;
        }
    }

    return dst;
}
