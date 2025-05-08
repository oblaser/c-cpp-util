/*
author          Oliver Blaser
date            08.05.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_LOG_H
#define IG_UTIL_LOG_H

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

#define LOG_CSI_EL "\033[2K" // erase line

#define LOG_SGR_RESET    "\033[0m"

// SGR foreground colors
#define LOG_SGR_BLACK    "\033[30m"
#define LOG_SGR_RED      "\033[31m"
#define LOG_SGR_GREEN    "\033[32m"
#define LOG_SGR_YELLOW   "\033[33m"
#define LOG_SGR_BLUE     "\033[34m"
#define LOG_SGR_MAGENTA  "\033[35m"
#define LOG_SGR_CYAN     "\033[36m"
#define LOG_SGR_WHITE    "\033[37m"
#define LOG_SGR_DEFAULT  "\033[39m"
#define LOG_SGR_BBLACK   "\033[90m"
#define LOG_SGR_BRED     "\033[91m"
#define LOG_SGR_BGREEN   "\033[92m"
#define LOG_SGR_BYELLOW  "\033[93m"
#define LOG_SGR_BBLUE    "\033[94m"
#define LOG_SGR_BMAGENTA "\033[95m"
#define LOG_SGR_BCYAN    "\033[96m"
#define LOG_SGR_BWHITE   "\033[97m"

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



#endif // IG_UTIL_LOG_H



#ifdef UTIL_LOG_DEFINE_FUNCTIONS
#undef UTIL_LOG_DEFINE_FUNCTIONS

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifdef __cplusplus
#include <string>
#endif


static void ___LOG_tNow_local_iso8601(char* buffer, size_t size)
{
    const time_t t = time(NULL);
    const struct tm* tm = localtime(&t);

    if (!(tm && (strftime(buffer, size, "%FT%T", tm) > 0))) { sprintf(buffer, "%lli", (int64_t)t); }
}


#ifdef __cplusplus

std::string LOG_tNow_local_iso8601()
{
    char buffer[25];
    ___LOG_tNow_local_iso8601(buffer, sizeof(buffer));
    return buffer;
}

#else // __cplusplus

const char* LOG_tNow_local_iso8601()
{
#warning "LOG_tNow_local_iso8601() is not thread safe"
    static char buffer[25];
    ___LOG_tNow_local_iso8601(buffer, sizeof(buffer));
    return buffer;
}

#endif // __cplusplus


#endif // UTIL_LOG_DEFINE_FUNCTIONS
