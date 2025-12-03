/*
author          Oliver Blaser
date            19.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_TEST_UNIT_LOG_HPP
#define IG_TEST_UNIT_LOG_HPP

#include <cstddef>
#include <cstdio>
#include <ctime>
#include <string>

#define LOG_MODULE_LEVEL LOG_LEVEL_DBG
#define LOG_MODULE_NAME  UNIT_TEST
#include "util/log.h"

#include "catch2/catch.hpp"



TEST_CASE("log.h ___LOG_t_local_iso8601")
{
    constexpr size_t bufferSize = 25;
    char buffer[bufferSize];



    ___LOG_t_local_iso8601(buffer, bufferSize, 0);
    CHECK(std::string(buffer) == "1970-01-01T01:00:00");



    const auto tNow = std::time(nullptr);
    const struct tm tm = *localtime(&tNow);
    char tmBuffer[bufferSize * 3];
    sprintf(tmBuffer, "%04i-%02i-%02iT%02i:%02i:%02i", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    ___LOG_t_local_iso8601(buffer, bufferSize, tNow);
    CHECK(std::string(buffer) == tmBuffer);



    ___LOG_t_local_iso8601(buffer, 5, tNow);
    CHECK(std::string(buffer) == std::to_string(tNow));
}



#endif // IG_TEST_UNIT_LOG_HPP
