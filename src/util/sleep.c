/*
author          Oliver Blaser
date            01.03.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <stdint.h>

#include "sleep.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
#endif



#define LITERAL_1e6 (1000000)



int UTIL_sleep_ms(uint32_t t_ms)
{
#ifdef _WIN32

    Sleep(t_ms);
    return 0;

#else // _WIN32

    struct timespec ts;
    UTIL_ms_to_timespec(&ts, t_ms);
    return nanosleep(&ts, NULL);

#endif // _WIN32
}

int UTIL_sleep_us(uint32_t t_us)
{
#ifdef _WIN32

    // clamp to 1ms
    if (t_us < 1000) { t_us = 1000; }

    // round at 3/4 (normal rounding would be done at 1/2)
    t_us += 250;
    const DWORD t_ms = (DWORD)(t_us / 1000);

    Sleep(t_ms);
    return 0;

#else // _WIN32

    struct timespec ts;
    UTIL_us_to_timespec(&ts, t_us);
    return nanosleep(&ts, NULL);

#endif // _WIN32
}


#ifndef _WIN32

void UTIL_ms_to_timespec(struct timespec* dst, uint64_t t_ms)
{
    dst->tv_sec = (time_t)(t_ms / 1000);
    dst->tv_nsec = (int32_t)((t_ms - ((uint32_t)(dst->tv_sec) * 1000)) * LITERAL_1e6);
}

void UTIL_us_to_timespec(struct timespec* dst, uint64_t t_us)
{
    dst->tv_sec = (time_t)(t_us / LITERAL_1e6);
    dst->tv_nsec = (int32_t)((t_us - ((uint64_t)(dst->tv_sec) * LITERAL_1e6)) * 1000);
}

#endif
