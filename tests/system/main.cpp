/*
author          Oliver Blaser
date            01.02.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <stdio.h>

#include "util/ansi-esc.h"
#include "util/macros.h"

#define LOG_MODULE_LEVEL LOG_LEVEL_DBG
#define LOG_MODULE_NAME  MAIN
#include "util/log.h"



#define LOG_TEST_FUNC()                                \
    LOG_INF("UTIL__FUNCNAME__: %s", UTIL__FUNCNAME__); \
    LOG_INF("UTIL__FUNCSIG__:  %s", UTIL__FUNCSIG__)



namespace namsp {

class Class
{
public:
    void log() { LOG_TEST_FUNC(); }
};

void log() { LOG_TEST_FUNC(); }

} // namespace namsp

class Other
{
public:
    void log() { LOG_TEST_FUNC(); }
};



int main()
{
    LOG_ERR("error     %s %i", __func__, __LINE__);
    LOG_WRN("warning   %s %i", __func__, __LINE__);
    LOG_INF("info      %s %i", __func__, __LINE__);

    printf(CSI_CUF(35) SGR_BG_YELLOW " 0123456789abcdef 0123456789abcdef " SGR_BG_DEFAULT "\r");
    fflush(stdout);

    LOG_DBG("debug     %s %i", __func__, __LINE__);

    printf("\n");



    namsp::log();
    printf("\n");

    namsp::Class().log();
    printf("\n");

    Other().log();



    printf("\n");



    return 0;
}



#define UTIL_LOG_DEFINE_FUNCTIONS
#include "util/log.h"
