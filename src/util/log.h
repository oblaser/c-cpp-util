/*
author          Oliver Blaser
date            27.10.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_LOG_H
#define IG_UTIL_LOG_H

#include "bits/log_ansi-esc.h"



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



#ifndef CONFIG_UTIL_LOG_MAX_LEVEL
#ifdef _MSC_VER
#define __PRAGMA_LOC__ __FILE__ "(" ___LOG_STR(__LINE__) ") "
__pragma(message(__PRAGMA_LOC__ ": warning: \"CONFIG_UTIL_LOG_MAX_LEVEL is not defined, defaulting to 2 (warning)\""))
#undef __PRAGMA_LOC__
#else //_MSC_VER
#warning "CONFIG_UTIL_LOG_MAX_LEVEL is not defined, defaulting to 2 (warning)"
#endif //_MSC_VER
#define CONFIG_UTIL_LOG_MAX_LEVEL LOG_LEVEL_WRN
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



#define LOG_COL_ERR LOG_FG_BRED
#define LOG_COL_WRN LOG_FG_BYELLOW
#define LOG_COL_INF LOG_COL_DEFAULT
#define LOG_COL_DBG LOG_FG_BBLACK



// clang-format off
#define LOG_ERR(msg, ...) printf(LOG_CSI_EL "[%s] " LOG_COL_ERR ___LOG_STR(LOG_MODULE_NAME) " <ERR> " msg LOG_SGR_RESET "\n", LOG_TIMESTAMP_STR ___LOG_OPT_VA_ARGS(__VA_ARGS__))
#define LOG_WRN(msg, ...) printf(LOG_CSI_EL "[%s] " LOG_COL_WRN ___LOG_STR(LOG_MODULE_NAME) " <WRN> " msg LOG_SGR_RESET "\n", LOG_TIMESTAMP_STR ___LOG_OPT_VA_ARGS(__VA_ARGS__))
#define LOG_INF(msg, ...) printf(LOG_CSI_EL "[%s] " LOG_COL_INF ___LOG_STR(LOG_MODULE_NAME) " <INF> " msg LOG_SGR_RESET "\n", LOG_TIMESTAMP_STR ___LOG_OPT_VA_ARGS(__VA_ARGS__))
//#define LOG_DBG(msg, ...) printf(LOG_CSI_EL "[%s] " LOG_COL_DEFAULT ___LOG_STR(LOG_MODULE_NAME) " <DBG> " msg LOG_SGR_RESET "\n", LOG_TIMESTAMP_STR ___LOG_OPT_VA_ARGS(__VA_ARGS__))
#define LOG_DBG(msg, ...) printf(LOG_CSI_EL "[%s] " LOG_COL_DEFAULT ___LOG_STR(LOG_MODULE_NAME) " <DBG> " LOG_COL_DBG "%s():%i" LOG_COL_DEFAULT " " msg LOG_SGR_RESET "\n", LOG_TIMESTAMP_STR, __func__, (int)(__LINE__) ___LOG_OPT_VA_ARGS(__VA_ARGS__))
// clang-format on



#define LOG_LEVEL_IS_ENABLED(_level) ((LOG_MODULE_LEVEL >= (_level)) && (CONFIG_UTIL_LOG_MAX_LEVEL >= (_level)))



#if !LOG_LEVEL_IS_ENABLED(LOG_LEVEL_DBG)
#undef LOG_DBG
#define LOG_DBG(...) (void)0
#endif

#if !LOG_LEVEL_IS_ENABLED(LOG_LEVEL_INF)
#undef LOG_INF
#define LOG_INF(...) (void)0
#endif

#if !LOG_LEVEL_IS_ENABLED(LOG_LEVEL_WRN)
#undef LOG_WRN
#define LOG_WRN(...) (void)0
#endif

#if !LOG_LEVEL_IS_ENABLED(LOG_LEVEL_ERR)
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

#define LOG_LEVEL_IS_ENABLED(_level) (((MODULE_LOG_LEVEL >= (_level)) || (LOG_MODULE_LEVEL >= (_level))) && (CONFIG_LOG_MAX_LEVEL >= (_level)))

#if LOG_LEVEL_IS_ENABLED(LOG_LEVEL_ERR)
#define LOG_ERR_MSLEEP(_ms) k_msleep((_ms))
#else
#define LOG_ERR_MSLEEP(...) (void)0
#endif

#if LOG_LEVEL_IS_ENABLED(LOG_LEVEL_WRN)
#define LOG_WRN_MSLEEP(_ms) k_msleep((_ms))
#else
#define LOG_WRN_MSLEEP(...) (void)0
#endif

#if LOG_LEVEL_IS_ENABLED(LOG_LEVEL_INF)
#define LOG_INF_MSLEEP(_ms) k_msleep((_ms))
#else
#define LOG_INF_MSLEEP(...) (void)0
#endif

#if LOG_LEVEL_IS_ENABLED(LOG_LEVEL_DBG)
#define LOG_DBG_MSLEEP(_ms) k_msleep((_ms))
#else
#define LOG_DBG_MSLEEP(...) (void)0
#endif

#endif // __ZEPHYR__ ============================================================================================ ZEPHYR



#endif // IG_UTIL_LOG_H



// #####################################################################################################################
// #####################################################################################################################
// #####################################################################################################################



#ifdef UTIL_LOG_DEFINE_FUNCTIONS
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
