/*
author          Oliver Blaser
date            19.03.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#ifndef IG_UTIL_BITS_COMPILER_H
#define IG_UTIL_BITS_COMPILER_H

// #include


#ifdef __cplusplus
extern "C" {
#endif



#ifdef _WIN32
#define ___UTIL_PLAT_WIN (1)
#endif

#if (defined(__unix__) || defined(__unix))
#define ___UTIL_PLAT_UNIX (1)
#endif

#ifdef __linux__
#define ___UTIL_PLAT_LINUX (1)
#endif

#ifdef __ZEPHYR__
#define ___UTIL_PLAT_ZEPHYR (1)
#endif



#define ___UTIL_STDC __STDC_VERSION__

// https://en.cppreference.com/w/c/preprocessor/replace.html
// https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros
#define ___UTIL_STDC_11 201112L
#define ___UTIL_STDC_17 201710L



#ifdef __cplusplus
}
#endif

#endif // IG_UTIL_BITS_COMPILER_H
