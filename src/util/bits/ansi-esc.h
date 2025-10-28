/*
author          Oliver Blaser
date            27.10.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_BITS_ANSIESC_H
#define IG_UTIL_BITS_ANSIESC_H



#define CSI_CUU(_n) "\033[" #_n "A" // cursor up
#define CSI_CUD(_n) "\033[" #_n "B" // cursor down
#define CSI_CUF(_n) "\033[" #_n "C" // cursor forward
#define CSI_CUB(_n) "\033[" #_n "D" // cursor back
#define CSI_EL      "\033[2K"       // erase line

#define SGR_RESET "\033[0m"

#define SGR_FG_BLACK   "\033[30m"
#define SGR_FG_RED     "\033[31m"
#define SGR_FG_GREEN   "\033[32m"
#define SGR_FG_YELLOW  "\033[33m"
#define SGR_FG_BLUE    "\033[34m"
#define SGR_FG_MAGENTA "\033[35m"
#define SGR_FG_CYAN    "\033[36m"
#define SGR_FG_WHITE   "\033[37m"

#define SGR_FG_8BIT(_n)        "\033[38;5;" #_n "m"                 // 8bit colour lookup table
#define SGR_FG_RGB(_r, _g, _b) "\033[38;2;" #_r ";" #_g ";" #_b "m" // 24bit colours

#define SGR_FG_DEFAULT "\033[39m"

#define SGR_BG_BLACK   "\033[40m"
#define SGR_BG_RED     "\033[41m"
#define SGR_BG_GREEN   "\033[42m"
#define SGR_BG_YELLOW  "\033[43m"
#define SGR_BG_BLUE    "\033[44m"
#define SGR_BG_MAGENTA "\033[45m"
#define SGR_BG_CYAN    "\033[46m"
#define SGR_BG_WHITE   "\033[47m"

#define SGR_BG_8BIT(_n)        "\033[48;5;" #_n "m"                 // 8bit colour lookup table
#define SGR_BG_RGB(_r, _g, _b) "\033[48;2;" #_r ";" #_g ";" #_b "m" // 24bit colours

#define SGR_BG_DEFAULT "\033[49m"

#define SGR_FG_BBLACK   "\033[90m"
#define SGR_FG_BRED     "\033[91m"
#define SGR_FG_BGREEN   "\033[92m"
#define SGR_FG_BYELLOW  "\033[93m"
#define SGR_FG_BBLUE    "\033[94m"
#define SGR_FG_BMAGENTA "\033[95m"
#define SGR_FG_BCYAN    "\033[96m"
#define SGR_FG_BWHITE   "\033[97m"

#define SGR_BG_BBLACK   "\033[100m"
#define SGR_BG_BRED     "\033[101m"
#define SGR_BG_BGREEN   "\033[102m"
#define SGR_BG_BYELLOW  "\033[103m"
#define SGR_BG_BBLUE    "\033[104m"
#define SGR_BG_BMAGENTA "\033[105m"
#define SGR_BG_BCYAN    "\033[106m"
#define SGR_BG_BWHITE   "\033[107m"



#endif // IG_UTIL_BITS_ANSIESC_H
