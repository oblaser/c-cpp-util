/*
author          Oliver Blaser
date            19.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_TEST_UNIT_TIME_HPP
#define IG_TEST_UNIT_TIME_HPP

#include <time.h>

#include "util/time.h"

#include "catch2/catch.hpp"



#define TESTUTIL_CHECK_TIMESPEC(_timespec, _t, _ns) \
    CHECK((_timespec).tv_sec == (_t));              \
    CHECK((_timespec).tv_nsec == (_ns))



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



#endif // IG_TEST_UNIT_TIME_HPP
