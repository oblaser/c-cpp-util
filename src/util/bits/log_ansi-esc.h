/*
author          Oliver Blaser
date            27.10.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_BITS_LOGANSIESC_H
#define IG_UTIL_BITS_LOGANSIESC_H



#if (!CONFIG_UTIL_LOG_NO_ANSIESC || (defined(__ZEPHYR__) && (CONFIG_LOG_BACKEND_SHOW_COLOR)))

#if (defined(__ZEPHYR__) && CONFIG_USE_SEGGER_RTT)
#include "log_ansi-esc_rtt.h"
#else
#include "log_ansi-esc_enabled.h"
#endif

#else // !CONFIG_UTIL_LOG_NO_ANSIESC

#include "log_ansi-esc_disabled.h"

#endif // !CONFIG_UTIL_LOG_NO_ANSIESC



#endif // IG_UTIL_BITS_LOGANSIESC_H
