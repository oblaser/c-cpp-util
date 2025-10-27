/*
author          Oliver Blaser
date            27.10.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_LOG_H
#define IG_UTIL_LOG_H



#ifndef __ZEPHYR__ // =========================================================================================== ZEPHYR



#include <stdio.h>



#define LOG_LEVEL_OFF (0)
#define LOG_LEVEL_ERR (1)
#define LOG_LEVEL_WRN (2)
#define LOG_LEVEL_INF (3)
#define LOG_LEVEL_DBG (4)



// stringify
#define ___LOG_STR_HELPER(x) #x
#define ___LOG_STR(x)        ___LOG_STR_HELPER(x)

// optional args
#define ___LOG_OPT_VA_ARGS(...) , ##__VA_ARGS__



#ifndef CONFIG_LOG_LEVEL
#ifdef _MSC_VER
#define __PRAGMA_LOC__ __FILE__ "(" ___LOG_STR(__LINE__) ") "
__pragma(message(__PRAGMA_LOC__ ": warning: \"CONFIG_LOG_LEVEL is not defined, defaulting to 2 (warning)\""))
#undef __PRAGMA_LOC__
#else //_MSC_VER
#warning "CONFIG_LOG_LEVEL is not defined, defaulting to 2 (warning)"
#endif //_MSC_VER
#define CONFIG_LOG_LEVEL LOG_LEVEL_WRN
#endif

#ifndef UTIL_LOG_DEFINE_FUNCTIONS
#ifndef LOG_MODULE_LEVEL
#error "define LOG_MODULE_LEVEL before including log.h"
#endif
#ifndef LOG_MODULE_NAME
#error "define LOG_MODULE_NAME before including log.h"
#endif
#endif // UTIL_LOG_DEFINE_FUNCTIONS

#ifndef LOG_TIMESTAMP_STR

#ifdef __cplusplus
#define LOG_TIMESTAMP_STR LOG_tNow_local_iso8601().c_str()
#else
#define LOG_TIMESTAMP_STR LOG_tNow_local_iso8601()
#endif

#endif // LOG_TIMESTAMP_STR



#if CONFIG_UTIL_LOG_NO_ANSIESC
#else // CONFIG_UTIL_LOG_NO_ANSIESC

#define CSI_EL "\033[2K" // erase line

#define SGR_RESET       "\033[0m"

// SGR foreground colors
#define SGR_FG_BLACK    "\033[30m"
#define SGR_FG_RED      "\033[31m"
#define SGR_FG_GREEN    "\033[32m"
#define SGR_FG_YELLOW   "\033[33m"
#define SGR_FG_BLUE     "\033[34m"
#define SGR_FG_MAGENTA  "\033[35m"
#define SGR_FG_CYAN     "\033[36m"
#define SGR_FG_WHITE    "\033[37m"
#define SGR_FG_DEFAULT  "\033[39m"
#define SGR_FG_BBLACK   "\033[90m"
#define SGR_FG_BRED     "\033[91m"
#define SGR_FG_BGREEN   "\033[92m"
#define SGR_FG_BYELLOW  "\033[93m"
#define SGR_FG_BBLUE    "\033[94m"
#define SGR_FG_BMAGENTA "\033[95m"
#define SGR_FG_BCYAN    "\033[96m"
#define SGR_FG_BWHITE   "\033[97m"

// TODO ansi-esc-header

#endif // CONFIG_UTIL_LOG_NO_ANSIESC



// config can limit log level
#if (CONFIG_LOG_LEVEL < LOG_MODULE_LEVEL)
#undef LOG_MODULE_LEVEL
#define LOG_MODULE_LEVEL CONFIG_LOG_LEVEL
#endif



// clang-format off
#define LOG_ERR(msg, ...) printf(LOG_CSI_EL "[%s] " LOG_SGR_BRED ___LOG_STR(LOG_MODULE_NAME) " <ERR> " msg LOG_SGR_RESET "\n", LOG_TIMESTAMP_STR ___LOG_OPT_VA_ARGS(__VA_ARGS__))
#define LOG_WRN(msg, ...) printf(LOG_CSI_EL "[%s] " LOG_SGR_BYELLOW ___LOG_STR(LOG_MODULE_NAME) " <WRN> " msg LOG_SGR_RESET "\n", LOG_TIMESTAMP_STR ___LOG_OPT_VA_ARGS(__VA_ARGS__))
#define LOG_INF(msg, ...) printf(LOG_CSI_EL "[%s] " LOG_SGR_RESET ___LOG_STR(LOG_MODULE_NAME) " <INF> " msg LOG_SGR_RESET "\n", LOG_TIMESTAMP_STR ___LOG_OPT_VA_ARGS(__VA_ARGS__))
//#define LOG_DBG(msg, ...) printf(LOG_CSI_EL "[%s] " LOG_SGR_RESET ___LOG_STR(LOG_MODULE_NAME) " <DBG> " msg LOG_SGR_RESET "\n", LOG_TIMESTAMP_STR ___LOG_OPT_VA_ARGS(__VA_ARGS__))
#define LOG_DBG(msg, ...) printf(LOG_CSI_EL "[%s] " LOG_SGR_RESET ___LOG_STR(LOG_MODULE_NAME) " <DBG> " LOG_SGR_BBLACK "%s():%i" LOG_SGR_RESET " " msg LOG_SGR_RESET "\n", LOG_TIMESTAMP_STR, __func__, (int)(__LINE__) ___LOG_OPT_VA_ARGS(__VA_ARGS__))
// clang-format on



#if (LOG_MODULE_LEVEL < LOG_LEVEL_DBG)
#undef LOG_DBG
#define LOG_DBG(...) (void)0
#endif
#if (LOG_MODULE_LEVEL < LOG_LEVEL_INF)
#undef LOG_INF
#define LOG_INF(...) (void)0
#endif
#if (LOG_MODULE_LEVEL < LOG_LEVEL_WRN)
#undef LOG_WRN
#define LOG_WRN(...) (void)0
#endif
#if (LOG_MODULE_LEVEL < LOG_LEVEL_ERR)
#undef LOG_ERR
#define LOG_ERR(...) (void)0
#endif



#ifdef __cplusplus
#include <string>
    std::string LOG_tNow_local_iso8601();
#else  // __cplusplus
const char* LOG_tNow_local_iso8601();
#endif // __cplusplus



#else // __ZEPHYR__  ============================================================================================ ZEPHYR



#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>



#if CONFIG_LOG_BACKEND_SHOW_COLOR

#define RTT_FG_BLACK    "\033[0;30m"
#define RTT_FG_RED      "\033[0;31m"
#define RTT_FG_GREEN    "\033[0;32m"
#define RTT_FG_YELLOW   "\033[0;33m"
#define RTT_FG_BLUE     "\033[0;34m"
#define RTT_FG_MAGENTA  "\033[0;35m"
#define RTT_FG_CYAN     "\033[0;36m"
#define RTT_FG_WHITE    "\033[0;37m"
// #define RTT_FG_DEFAULT "\033[39m" // ignored by RTT

// using bold parameter for making foreground colors bright, works with RTT and PuTTY (RTT ignores bright colors 9x)
#define RTT_FG_BBLACK   "\033[1;30m"
#define RTT_FG_BRED     "\033[1;31m"
#define RTT_FG_BGREEN   "\033[1;32m"
#define RTT_FG_BYELLOW  "\033[1;33m"
#define RTT_FG_BBLUE    "\033[1;34m"
#define RTT_FG_BMAGENTA "\033[1;35m"
#define RTT_FG_BCYAN    "\033[1;36m"
#define RTT_FG_BWHITE   "\033[1;37m"

#define ___RTT_PRINT_TEST()                                                                                                                 \
    {                                                                                                                                       \
        k_msleep(100);                                                                                                                      \
        printk(SGR_RESET "    0;3x  1;3x  9x\r\n");                                                                                         \
        for (int i = 30; i <= 37; ++i) { printk("x%i  \033[0;%im###   \033[1;%im###   \033[%im###\033[0m\r\n", (i - 30), i, i, (i + 60)); } \
        printk(SGR_RESET "\r\n");                                                                                                           \
        k_msleep(100);                                                                                                                      \
    }



#if CONFIG_UTIL_LOG_NO_ANSIESC
#else // CONFIG_UTIL_LOG_NO_ANSIESC

#define CSI_EL "\033[2K" // erase line

#define SGR_RESET "\033[0m"

#if CONFIG_USE_SEGGER_RTT

#define SGR_FG_BLACK    RTT_FG_BLACK
#define SGR_FG_RED      RTT_FG_RED
#define SGR_FG_GREEN    RTT_FG_GREEN
#define SGR_FG_YELLOW   RTT_FG_YELLOW
#define SGR_FG_BLUE     RTT_FG_BLUE
#define SGR_FG_MAGENTA  RTT_FG_MAGENTA
#define SGR_FG_CYAN     RTT_FG_CYAN
#define SGR_FG_WHITE    RTT_FG_WHITE
#define SGR_FG_DEFAULT  SGR_RESET
#define SGR_FG_BBLACK   RTT_FG_BBLACK
#define SGR_FG_BRED     RTT_FG_BRED
#define SGR_FG_BGREEN   RTT_FG_BGREEN
#define SGR_FG_BYELLOW  RTT_FG_BYELLOW
#define SGR_FG_BBLUE    RTT_FG_BBLUE
#define SGR_FG_BMAGENTA RTT_FG_BMAGENTA
#define SGR_FG_BCYAN    RTT_FG_BCYAN
#define SGR_FG_BWHITE   RTT_FG_BWHITE

#else // CONFIG_USE_SEGGER_RTT
#error "not implemented"
// TODO create ANSI ESC code bits header which can be used here and at "ansi-esc-header"
#endif // CONFIG_USE_SEGGER_RTT

#endif // CONFIG_UTIL_LOG_NO_ANSIESC



#endif // CONFIG_LOG_BACKEND_SHOW_COLOR



#define ___IS_LOG_LEVEL_ENABLED(_level) ((MODULE_LOG_LEVEL >= (_level)) && (CONFIG_LOG_MAX_LEVEL >= (_level)))

#if ___IS_LOG_LEVEL_ENABLED(LOG_LEVEL_ERR)
#define LOG_ERR_MSLEEP(_ms) k_msleep((_ms))
#else
#define LOG_ERR_MSLEEP(...) (void)0
#endif

#if ___IS_LOG_LEVEL_ENABLED(LOG_LEVEL_WRN)
#define LOG_WRN_MSLEEP(_ms) k_msleep((_ms))
#else
#define LOG_WRN_MSLEEP(...) (void)0
#endif

#if ___IS_LOG_LEVEL_ENABLED(LOG_LEVEL_INF)
#define LOG_INF_MSLEEP(_ms) k_msleep((_ms))
#else
#define LOG_INF_MSLEEP(...) (void)0
#endif

#if ___IS_LOG_LEVEL_ENABLED(LOG_LEVEL_DBG)
#define LOG_DBG_MSLEEP(_ms) k_msleep((_ms))
#else
#define LOG_DBG_MSLEEP(...) (void)0
#endif



#endif // __ZEPHYR__ ============================================================================================ ZEPHYR



#endif // IG_UTIL_LOG_H



// #####################################################################################################################
// #####################################################################################################################
// #####################################################################################################################



#if defined(UTIL_LOG_DEFINE_FUNCTIONS) && !defined(__ZEPHYR__)
#undef UTIL_LOG_DEFINE_FUNCTIONS

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifdef __cplusplus
#include <string>
#endif


static inline void ___LOG_t_local_iso8601(char* buffer, size_t size, time_t t)
{
    const struct tm* tm = localtime(&t);

    if (!(tm && (strftime(buffer, size, "%FT%T", tm) > 0))) { sprintf(buffer, "%" PRIi64, (int64_t)t); }
}


#ifdef __cplusplus

std::string LOG_tNow_local_iso8601()
{
    char buffer[25];
    ___LOG_t_local_iso8601(buffer, sizeof(buffer), time(NULL));
    return buffer;
}

#else // __cplusplus

const char* LOG_tNow_local_iso8601()
{
#warning "LOG_tNow_local_iso8601() is not thread safe"
    static char buffer[25];
    ___LOG_t_local_iso8601(buffer, sizeof(buffer), time(NULL));
    return buffer;
}

#endif // __cplusplus


#endif // UTIL_LOG_DEFINE_FUNCTIONS
