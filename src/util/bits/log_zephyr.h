/*
author          Oliver Blaser
date            27.10.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_BITS_LOGZEPHYR_H
#define IG_UTIL_BITS_LOGZEPHYR_H

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>



#define LOG_LEVEL_IS_ENABLED(_level) ((MODULE_LOG_LEVEL >= (_level)) && (CONFIG_LOG_MAX_LEVEL >= (_level)))



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



#endif // IG_UTIL_BITS_LOGZEPHYR_H
