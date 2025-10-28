/*
author          Oliver Blaser
date            27.10.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_BITS_LOGANSIESCENABLED_H
#define IG_UTIL_BITS_LOGANSIESCENABLED_H

#include "ansi-esc.h"



#define LOG_CSI_EL CSI_EL

#define LOG_SGR_RESET SGR_RESET

#define LOG_FG_BLACK   SGR_FG_BLACK
#define LOG_FG_RED     SGR_FG_RED
#define LOG_FG_GREEN   SGR_FG_GREEN
#define LOG_FG_YELLOW  SGR_FG_YELLOW
#define LOG_FG_BLUE    SGR_FG_BLUE
#define LOG_FG_MAGENTA SGR_FG_MAGENTA
#define LOG_FG_CYAN    SGR_FG_CYAN
#define LOG_FG_WHITE   SGR_FG_WHITE

#define LOG_FG_8BIT(_n)        SGR_FG_8BIT(_n)
#define LOG_FG_RGB(_r, _g, _b) SGR_FG_RGB(_r, _g, _b)

#define LOG_FG_DEFAULT SGR_FG_DEFAULT

#define LOG_BG_BLACK   SGR_BG_BLACK
#define LOG_BG_RED     SGR_BG_RED
#define LOG_BG_GREEN   SGR_BG_GREEN
#define LOG_BG_YELLOW  SGR_BG_YELLOW
#define LOG_BG_BLUE    SGR_BG_BLUE
#define LOG_BG_MAGENTA SGR_BG_MAGENTA
#define LOG_BG_CYAN    SGR_BG_CYAN
#define LOG_BG_WHITE   SGR_BG_WHITE

#define LOG_BG_8BIT(_n)        SGR_BG_8BIT(_n)
#define LOG_BG_RGB(_r, _g, _b) SGR_BG_RGB(_r, _g, _b)

#define LOG_BG_DEFAULT SGR_BG_DEFAULT

#define LOG_FG_BBLACK   SGR_FG_BBLACK
#define LOG_FG_BRED     SGR_FG_BRED
#define LOG_FG_BGREEN   SGR_FG_BGREEN
#define LOG_FG_BYELLOW  SGR_FG_BYELLOW
#define LOG_FG_BBLUE    SGR_FG_BBLUE
#define LOG_FG_BMAGENTA SGR_FG_BMAGENTA
#define LOG_FG_BCYAN    SGR_FG_BCYAN
#define LOG_FG_BWHITE   SGR_FG_BWHITE

#define LOG_BG_BBLACK   SGR_BG_BBLACK
#define LOG_BG_BRED     SGR_BG_BRED
#define LOG_BG_BGREEN   SGR_BG_BGREEN
#define LOG_BG_BYELLOW  SGR_BG_BYELLOW
#define LOG_BG_BBLUE    SGR_BG_BBLUE
#define LOG_BG_BMAGENTA SGR_BG_BMAGENTA
#define LOG_BG_BCYAN    SGR_BG_BCYAN
#define LOG_BG_BWHITE   SGR_BG_BWHITE

#define LOG_COL_DEFAULT "\033[39;49m" // default background and foreground colour



#endif // IG_UTIL_BITS_LOGANSIESCENABLED_H
