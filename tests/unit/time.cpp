/*
author          Oliver Blaser
date            19.03.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <time.h>

#include "util/time.h"

#include "catch2/catch.hpp"



#define TESTUTIL_CHECK_TIMESPEC(_timespec, _t, _ns) \
    CHECK((_timespec).tv_sec == (_t));              \
    CHECK((_timespec).tv_nsec == (_ns))



TEST_CASE("time.h constant expressions")
{
    CHECK(UTIL_SECOND_s == 1);
    CHECK(UTIL_MINUTE_s == 60);
    CHECK(UTIL_HOUR_s == 3600);
    CHECK(UTIL_DAY_s == 86400);

    CHECK(UTIL_SECOND_ms == 1000);
    CHECK(UTIL_MINUTE_ms == 60000);
    CHECK(UTIL_HOUR_ms == 3600000);
    CHECK(UTIL_DAY_ms == 86400000);

    CHECK(UTIL_SECOND_us == 1000000);
    CHECK(UTIL_MINUTE_us == 60000000);
    CHECK(UTIL_HOUR_us == 3600000000ll);
    CHECK(UTIL_DAY_us == 86400000000ll);
}

TEST_CASE("time.h UTIL_ms_to_timespec")
{
    struct timespec ts;

    UTIL_ms_to_timespec(&ts, 0);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 0);

    UTIL_ms_to_timespec(&ts, 1);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 1000000);

    UTIL_ms_to_timespec(&ts, 987);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 987000000);

    UTIL_ms_to_timespec(&ts, 3000);
    TESTUTIL_CHECK_TIMESPEC(ts, 3, 0);

    UTIL_ms_to_timespec(&ts, 5001);
    TESTUTIL_CHECK_TIMESPEC(ts, 5, 1000000);

    UTIL_ms_to_timespec(&ts, 123456789);
    TESTUTIL_CHECK_TIMESPEC(ts, 123456, 789000000);
}

TEST_CASE("time.h UTIL_us_to_timespec")
{
    struct timespec ts;

    UTIL_us_to_timespec(&ts, 0);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 0);

    UTIL_us_to_timespec(&ts, 1);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 1000);

    UTIL_us_to_timespec(&ts, 987);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 987000);

    UTIL_us_to_timespec(&ts, 3000);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 3000000);

    UTIL_us_to_timespec(&ts, 5001);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 5001000);

    UTIL_us_to_timespec(&ts, 3000000);
    TESTUTIL_CHECK_TIMESPEC(ts, 3, 0);

    UTIL_us_to_timespec(&ts, 5000001);
    TESTUTIL_CHECK_TIMESPEC(ts, 5, 1000);

    UTIL_us_to_timespec(&ts, 123456789);
    TESTUTIL_CHECK_TIMESPEC(ts, 123, 456789000);
}

TEST_CASE("time.h UTIL_ns_to_timespec")
{
    struct timespec ts;

    UTIL_ns_to_timespec(&ts, 0);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 0);

    UTIL_ns_to_timespec(&ts, 1);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 1);

    UTIL_ns_to_timespec(&ts, 987);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 987);

    UTIL_ns_to_timespec(&ts, 3000);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 3000);

    UTIL_ns_to_timespec(&ts, 5001);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 5001);

    UTIL_ns_to_timespec(&ts, 3000000);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 3000000);

    UTIL_ns_to_timespec(&ts, 5000001);
    TESTUTIL_CHECK_TIMESPEC(ts, 0, 5000001);

    UTIL_ns_to_timespec(&ts, 3000000000);
    TESTUTIL_CHECK_TIMESPEC(ts, 3, 0);

    UTIL_ns_to_timespec(&ts, 5000000001);
    TESTUTIL_CHECK_TIMESPEC(ts, 5, 1);

    UTIL_ns_to_timespec(&ts, 1234567890123);
    TESTUTIL_CHECK_TIMESPEC(ts, 1234, 567890123);
}

#if ___UTIL_PLAT_WIN // && (___UTIL_STDC >= ___UTIL_STDC_11) test has to be done
TEST_CASE("time.h timspec FILETIME conversion")
{
#error "TODO implement tests"
    // https://learn.microsoft.com/en-us/windows/win32/api/timezoneapi/nf-timezoneapi-filetimetosystemtime
}
#endif
