/*
author          Oliver Blaser
date            22.03.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

#include "util/macros.h"
#include "util/version.h"

#include "catch2/catch.hpp"



#define DBG_LOG (0)



#if DBG_LOG
extern void hexDump(const uint8_t*, size_t);
#endif



TEST_CASE("version.h format constants")
{
    UTIL_mmver_t mm;
    UTIL_mmpver_t mmp;
    char buffer[100];

    mm.major = 159;
    mm.minor = 753;
    sprintf(buffer, "%" PRImmver, ARGmmver(&mm));
    CHECK(buffer == std::string("159.753"));

    mmp.major = 123;
    mmp.minor = 5;
    mmp.patch = 9;
    sprintf(buffer, "%" PRImmpver, ARGmmpver(&mmp));
    CHECK(buffer == std::string("123.5.9"));
}



TEST_CASE("version.h UTIL_mmver_clear()")
{
    UTIL_mmver_t ___v;
    UTIL_mmver_t* v = &___v;

    v->major = 12;
    v->minor = 34;

    UTIL_mmver_clear(v);

    CHECK(v->major == 0);
    CHECK(v->minor == 0);
}

TEST_CASE("version.h UTIL_mmvercmp()")
{
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++20-extensions"
#endif

    const UTIL_mmver_t v00 = { .major = 0, .minor = 0 };
    const UTIL_mmver_t v01 = { .major = 0, .minor = 1 };
    const UTIL_mmver_t v10 = { .major = 1, .minor = 0 };
    const UTIL_mmver_t v11 = { .major = 1, .minor = 1 };
    const UTIL_mmver_t v11_2 = { .major = 1, .minor = 1 };

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

    CHECK_FALSE(UTIL_mmvercmp(&v11, &v00) == 0);
    CHECK_FALSE(UTIL_mmvercmp(&v11, &v01) == 0);
    CHECK_FALSE(UTIL_mmvercmp(&v11, &v10) == 0);
    CHECK(UTIL_mmvercmp(&v11, &v11_2) == 0);

    CHECK(UTIL_mmvercmp(&v11, &v00) != 0);
    CHECK(UTIL_mmvercmp(&v11, &v01) != 0);
    CHECK(UTIL_mmvercmp(&v11, &v10) != 0);
    CHECK_FALSE(UTIL_mmvercmp(&v11, &v11_2) != 0);

    CHECK_FALSE(UTIL_mmvercmp(&v11, &v00) < 0);
    CHECK_FALSE(UTIL_mmvercmp(&v11, &v01) < 0);
    CHECK_FALSE(UTIL_mmvercmp(&v11, &v10) < 0);
    CHECK_FALSE(UTIL_mmvercmp(&v11, &v11_2) < 0);

    CHECK_FALSE(UTIL_mmvercmp(&v11, &v00) <= 0);
    CHECK_FALSE(UTIL_mmvercmp(&v11, &v01) <= 0);
    CHECK_FALSE(UTIL_mmvercmp(&v11, &v10) <= 0);
    CHECK(UTIL_mmvercmp(&v11, &v11_2) <= 0);

    CHECK(UTIL_mmvercmp(&v11, &v00) > 0);
    CHECK(UTIL_mmvercmp(&v11, &v01) > 0);
    CHECK(UTIL_mmvercmp(&v11, &v10) > 0);
    CHECK_FALSE(UTIL_mmvercmp(&v11, &v11_2) > 0);

    CHECK(UTIL_mmvercmp(&v11, &v00) >= 0);
    CHECK(UTIL_mmvercmp(&v11, &v01) >= 0);
    CHECK(UTIL_mmvercmp(&v11, &v10) >= 0);
    CHECK(UTIL_mmvercmp(&v11, &v11_2) >= 0);
}



TEST_CASE("version.h UTIL_mmpver_clear()")
{
    UTIL_mmpver_t ___v;
    UTIL_mmpver_t* v = &___v;

    v->major = 12;
    v->minor = 34;
    v->patch = 56;

    UTIL_mmpver_clear(v);

    CHECK(v->major == 0);
    CHECK(v->minor == 0);
    CHECK(v->patch == 0);
}



TEST_CASE("version.h UTIL_semver_clear()")
{
    UTIL_semver_t ___v;
    UTIL_semver_t* v = &___v;

    v->major = 12;
    v->minor = 34;
    v->patch = 56;
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

    prCount = 5;
    pr[0] = "asdf";
    pr[1] = NULL;
    pr[2] = "12";
    pr[3] = "";
    pr[4] = "qwertz";

    buildCount = 4;
    build[0] = "ASDF";
    build[1] = "";
    build[2] = "q";
    build[3] = NULL;

    expectedPointerSection[0] = (v->stack + 5 + 3 + 7 + 5);
    expectedPointerSection[1] = (v->stack + 5 + 3 + 7);
    expectedPointerSection[2] = (v->stack + 5 + 3);
    expectedPointerSection[3] = (v->stack + 5);
    expectedPointerSection[4] = (v->stack);

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
                 "qwertz\0"
                 "ASDF\0"
                 "q\0",
                 22) == 0);

    CHECK(memcmp((v->stack + v->stackSize - (sizeof(char*) * 5)), expectedPointerSection, 5 * sizeof(expectedPointerSection[0])) == 0);
    CHECK(v->major == 1);
    CHECK(v->minor == 2);
    CHECK(v->patch == 3);
    CHECK(v->prCount == 3);
    CHECK(v->buildCount == 2);



#if DBG_LOG
    memset(___stack, 0x5A, sizeof(___stack));
    memset(pr, 0x5A, sizeof(pr));
    memset(build, 0x5A, sizeof(build));
    memset(expectedPointerSection, 0x5A, sizeof(expectedPointerSection));
#endif // DBG_LOG

    buildCount = 2;
    build[0] = "DEV";
    build[1] = "EMC";

    expectedPointerSection[0] = (v->stack + 4);
    expectedPointerSection[1] = (v->stack);

    UTIL_semver_setPrBuild(v, NULL, 0, build, buildCount);

#if DBG_LOG && 0
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

    CHECK(memcmp((v->stack + v->stackSize - (sizeof(char*) * 2)), expectedPointerSection, 2 * sizeof(expectedPointerSection[0])) == 0);
    CHECK(v->major == 1);
    CHECK(v->minor == 2);
    CHECK(v->patch == 3);
    CHECK(v->prCount == 0);
    CHECK(v->buildCount == 2);



    prCount = 3;
    pr[0] = "alpha";
    pr[1] = "12";
    pr[2] = "test";

    expectedPointerSection[0] = (v->stack + 6 + 3);
    expectedPointerSection[1] = (v->stack + 6);
    expectedPointerSection[2] = (v->stack);

    UTIL_semver_setPrBuild(v, pr, prCount, NULL, 0);

    CHECK(memcmp(v->stack,
                 "alpha\0"
                 "12\0"
                 "test\0",
                 14) == 0);

    CHECK(memcmp((v->stack + v->stackSize - (sizeof(char*) * 3)), expectedPointerSection, 3 * sizeof(expectedPointerSection[0])) == 0);
    CHECK(v->major == 1);
    CHECK(v->minor == 2);
    CHECK(v->patch == 3);
    CHECK(v->prCount == 3);
    CHECK(v->buildCount == 0);
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
