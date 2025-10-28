/*
author          Oliver Blaser
date            27.10.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_BITS_LOGANSIESCRTT_H
#define IG_UTIL_BITS_LOGANSIESCRTT_H



#define RTT_SGR_RESET "\033[0m"

#define RTT_FG_BLACK   "\033[0;30m"
#define RTT_FG_RED     "\033[0;31m"
#define RTT_FG_GREEN   "\033[0;32m"
#define RTT_FG_YELLOW  "\033[0;33m"
#define RTT_FG_BLUE    "\033[0;34m"
#define RTT_FG_MAGENTA "\033[0;35m"
#define RTT_FG_CYAN    "\033[0;36m"
#define RTT_FG_WHITE   "\033[0;37m"
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



#define LOG_SGR_RESET RTT_SGR_RESET

#define LOG_FG_BLACK   RTT_FG_BLACK
#define LOG_FG_RED     RTT_FG_RED
#define LOG_FG_GREEN   RTT_FG_GREEN
#define LOG_FG_YELLOW  RTT_FG_YELLOW
#define LOG_FG_BLUE    RTT_FG_BLUE
#define LOG_FG_MAGENTA RTT_FG_MAGENTA
#define LOG_FG_CYAN    RTT_FG_CYAN
#define LOG_FG_WHITE   RTT_FG_WHITE

#define LOG_FG_BBLACK   RTT_FG_BBLACK
#define LOG_FG_BRED     RTT_FG_BRED
#define LOG_FG_BGREEN   RTT_FG_BGREEN
#define LOG_FG_BYELLOW  RTT_FG_BYELLOW
#define LOG_FG_BBLUE    RTT_FG_BBLUE
#define LOG_FG_BMAGENTA RTT_FG_BMAGENTA
#define LOG_FG_BCYAN    RTT_FG_BCYAN
#define LOG_FG_BWHITE   RTT_FG_BWHITE



#endif // IG_UTIL_BITS_LOGANSIESCRTT_H
