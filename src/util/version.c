/*
author          Oliver Blaser
date            09.05.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#if CONFIG_UTIL_VERSION_USE_STDIO
#include <stdio.h>
#include <string.h>
#endif

#include "version.h"
#if !CONFIG_UTIL_VERSION_USE_STDIO
#include "../util/string.h"
#endif



static const char identDelimiter = '.'; // identifier delimiter
static const char prDelimiter = '-';
static const char buildDelimiter = '+';



void UTIL_mmver_clear(UTIL_mmver_t* v)
{
    v->major = 0;
    v->minor = 0;
}

int UTIL_mmvercmp(const UTIL_mmver_t* a, const UTIL_mmver_t* b)
{
    int r = 0;

    if (a->major < b->major) { r = -1; }
    else if (a->major == b->major)
    {
        if (a->minor < b->minor) { r = -1; }
        else if (a->minor == b->minor) { r = 0; }
        else { r = 1; }
    }
    else { r = 1; }

    return r;
}



void UTIL_mmpver_clear(UTIL_mmpver_t* v)
{
    v->major = 0;
    v->minor = 0;
    v->patch = 0;
}



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
    if (!v)
    {
        errno = EINVAL;
        return -1;
    }



    // check size

    size_t reqSize = 0;

    if (pr)
    {
        for (size_t i = 0; i < prCount; ++i)
        {
            const char* const p = *(pr + i);

            if (p && *p) // valid pointer and not empty string
            {
                reqSize +=
#if CONFIG_UTIL_VERSION_USE_STDIO
                    strlen(p);
#else
                    UTIL_strlen(p);
#endif

                ++reqSize; // null terminator
                reqSize += sizeof(uintptr_t);
            }
        }
    }

    if (build)
    {
        for (size_t i = 0; i < buildCount; ++i)
        {
            const char* const p = *(build + i);

            if (p && *p) // valid pointer and not empty string
            {
                reqSize +=
#if CONFIG_UTIL_VERSION_USE_STDIO
                    strlen(p);
#else
                    UTIL_strlen(p);
#endif

                ++reqSize; // null terminator
                reqSize += sizeof(uintptr_t);
            }
        }
    }

    if (reqSize > v->stackSize)
    {
        errno = ENOMEM;
        return -1;
    }



    // copy

    v->prCount = 0;
    v->buildCount = 0;

    char* p = (char*)(v->stack);
    _Static_assert((sizeof(**pr) == 1) && (sizeof(**build) == 1), "sizeof(char) is expected to be 1");
    _Static_assert((sizeof(uintptr_t) == sizeof(p)) && (sizeof(uintptr_t) == sizeof(char*)), "sizeof(uintptr_t) is expected to be equal to sizeof(char*)");

    if (pr)
    {
        for (size_t i = 0; i < prCount; ++i)
        {
            const char* prStr = *(pr + i);

            if (prStr && *prStr) // valid pointer and not empty string
            {
                *((uintptr_t*)(v->stack + v->stackSize - ((v->prCount + 1) * sizeof(uintptr_t)))) = (uintptr_t)p;

                while (*prStr != 0)
                {
                    *p = *prStr;
                    ++p;
                    ++prStr;
                }

                *p = 0;
                ++p;

                ++(v->prCount);
            }
        }
    }

    if (build)
    {
        for (size_t i = 0; i < buildCount; ++i)
        {
            const char* buildStr = *(build + i);

            if (buildStr && *buildStr) // valid pointer and not empty string
            {
                *((uintptr_t*)(v->stack + v->stackSize - (v->prCount * sizeof(uintptr_t)) - ((v->buildCount + 1) * sizeof(uintptr_t)))) = (uintptr_t)p;

                while (*buildStr != 0)
                {
                    *p = *buildStr;
                    ++p;
                    ++buildStr;
                }

                *p = 0;
                ++p;

                ++(v->buildCount);
            }
        }
    }

    return 0;
}

char* UTIL_semvertos(char* dst, size_t size, const UTIL_semver_t* v, char** end)
{
#warning "TODO size checks, currently assuming sufficent destination buffer size"
    (void)size;

#if CONFIG_UTIL_VERSION_USE_STDIO
    sprintf(dst, "%i.%i.%i", v->major, v->minor, v->patch);
    char* p = dst + strlen(dst);
#else
    char* p = dst;
    UTIL_i32tos(p, v->major, &p);
    *p++ = '.';
    UTIL_i32tos(p, v->minor, &p);
    *p++ = '.';
    UTIL_i32tos(p, v->patch, &p);
#endif

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
        *p = 0;
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
        *p = 0;
    }

    if (end) { *end = p; }

    return dst;
}
