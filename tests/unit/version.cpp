/*
author          Oliver Blaser
date            12.02.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include "util/macros.h"
#include "util/version.h"

#include "catch2/catch.hpp"



#define DBG_LOG (0)



#if DBG_LOG
extern void hexDump(const uint8_t*, size_t);
#endif



TEST_CASE("version.h UTIL_semver_clear()")
{
    UTIL_semver_t ___v;
    UTIL_semver_t* v = &___v;

    v->major = 1;
    v->minor = 2;
    v->patch = 3;
    v->prCount = 4;
    v->buildCount = 5;

    UTIL_semver_clear(v);

    CHECK(v->major == 0);
    CHECK(v->minor == 0);
    CHECK(v->patch == 0);
    CHECK(v->prCount == 0);
    CHECK(v->buildCount == 0);
}

TEST_CASE("version.h UTIL_semver_setPrBuild()")
{
    uint8_t ___stack[512];
    UTIL_semver_t ___v;
    ___v.stack = ___stack;
    ___v.stackSize = sizeof(___stack);
    ___v.major = 1;
    ___v.minor = 2;
    ___v.patch = 3;

    UTIL_semver_t* v = &___v;

    size_t prCount, buildCount;
    const char* pr[10];
    const char* build[10];
    const uint8_t* expectedPointerSection[SIZEOF_ARRAY(pr) + SIZEOF_ARRAY(build)];



#if DBG_LOG
    memset(___stack, 0x5A, sizeof(___stack));
    memset(pr, 0x5A, sizeof(pr));
    memset(build, 0x5A, sizeof(build));
    memset(expectedPointerSection, 0x5A, sizeof(expectedPointerSection));
#endif // DBG_LOG

    prCount = 4;
    pr[0] = "asdf";
    pr[1] = "12";
    pr[2] = "";
    pr[3] = "qwertz";

    buildCount = 3;
    build[0] = "ASDF";
    build[1] = "";
    build[2] = "q";

    expectedPointerSection[0] = (v->stack + 5 + 3 + 1 + 7 + 5 + 1);
    expectedPointerSection[1] = (v->stack + 5 + 3 + 1 + 7 + 5);
    expectedPointerSection[2] = (v->stack + 5 + 3 + 1 + 7);
    expectedPointerSection[3] = (v->stack + 5 + 3 + 1);
    expectedPointerSection[4] = (v->stack + 5 + 3);
    expectedPointerSection[5] = (v->stack + 5);
    expectedPointerSection[6] = (v->stack);

    UTIL_semver_setPrBuild(v, pr, prCount, build, buildCount);

#if DBG_LOG && 0
    printf("stack: %p\n", v->stack);
    hexDump(v->stack, v->stackSize);
    printf("\n");
    hexDump((uint8_t*)expectedPointerSection, sizeof(expectedPointerSection));
    printf("\n");
#endif // DBG_LOG

    CHECK(memcmp(v->stack,
                 "asdf\0"
                 "12\0"
                 "\0"
                 "qwertz\0"
                 "ASDF\0"
                 "\0"
                 "q\0",
                 24) == 0);

    CHECK(memcmp((v->stack + v->stackSize - (sizeof(char*) * 7)), expectedPointerSection, 7) == 0);
    CHECK(v->major == 1);
    CHECK(v->minor == 2);
    CHECK(v->patch == 3);
    CHECK(v->prCount == 4);
    CHECK(v->buildCount == 3);



#if DBG_LOG
    memset(___stack, 0x5A, sizeof(___stack));
    memset(pr, 0x5A, sizeof(pr));
    memset(build, 0x5A, sizeof(build));
    memset(expectedPointerSection, 0x5A, sizeof(expectedPointerSection));
#endif // DBG_LOG

    prCount = 0;

    buildCount = 2;
    build[0] = "DEV";
    build[1] = "EMC";

    expectedPointerSection[0] = (v->stack + 4);
    expectedPointerSection[1] = (v->stack);

    UTIL_semver_setPrBuild(v, pr, prCount, build, buildCount);

#if DBG_LOG && 01
    printf("stack: %p\n", v->stack);
    hexDump(v->stack, v->stackSize);
    printf("\n");
    hexDump((uint8_t*)expectedPointerSection, sizeof(expectedPointerSection));
    printf("\n");
#endif // DBG_LOG

    CHECK(memcmp(v->stack,
                 "DEV\0"
                 "EMC\0",
                 8) == 0);

    CHECK(memcmp((v->stack + v->stackSize - (sizeof(char*) * 2)), expectedPointerSection, 2) == 0);
    CHECK(v->major == 1);
    CHECK(v->minor == 2);
    CHECK(v->patch == 3);
    CHECK(v->prCount == 0);
    CHECK(v->buildCount == 2);
}

TEST_CASE("version.h UTIL_semvertos()")
{
    UTIL_semver_t ___v;
    UTIL_semver_t* v = &___v;
    char buffer[1024];

    v->major = 1;
    v->minor = 2;
    v->patch = 3;
    v->prCount = 0;
    v->buildCount = 0;

    CHECK(UTIL_semvertos(buffer, sizeof(buffer), v, NULL) == std::string("1.2.3"));
}
