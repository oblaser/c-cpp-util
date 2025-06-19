/*
author          Oliver Blaser
date            08.05.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_MACROS_H
#define IG_UTIL_MACROS_H


#ifdef __ZEPHYR__
#include <zephyr/sys/util.h>
#include <zephyr/sys/util_macro.h>
#endif



//======================================================================================================================
// declaration specifiers/attributes

#if defined(_MSC_VER)
#if (_MSVC_LANG >= 201703L)
#define ATTR_UNUSED [[maybe_unused]]
#else // Cpp std version
#define ATTR_UNUSED
#endif // Cpp std version
#else  // compiler
#define ATTR_UNUSED __attribute__((unused))
#endif // compiler

#ifdef __cplusplus
#define ATTR_EXTERN_C   extern "C"
#define ATTR_EXTERN_CPP extern "C++"
#else // __cplusplus
#define ATTR_EXTERN_C
#define ATTR_EXTERN_CPP
#endif // __cplusplus



//======================================================================================================================
// preprocessor macros

#ifndef PP_CAT
// clang-format off
#define PP_CAT_NX(_a, _b)           _a ## _b
#define PP_CAT3_NX(_a, _b, _c)      _a ## _b ## _c
#define PP_CAT4_NX(_a, _b, _c, _d)  _a ## _b ## _c ## _d
// clang-format on
#define PP_CAT(_a, _b)          PP_CAT_NX(_a, _b)
#define PP_CAT3(_a, _b, _c)     PP_CAT3_NX(_a, _b, _c)
#define PP_CAT4(_a, _b, _c, _d) PP_CAT4_NX(_a, _b, _c, _d)
#endif // PP_CAT


#ifndef PP_STR
#define PP_STR_NX(_a) #_a
#define PP_STR(_a)    PP_STR_NX(_a)
#endif // PP_STR



#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(_array) (sizeof(_array) / sizeof((_array)[0]))
#endif



#ifndef BIT
#define BIT(_n) (1u << (_n))
#endif

#ifndef BIT64
#define BIT64(_n) (1llu << (_n))
#endif

#ifndef BIT_MASK
#define BIT_MASK(_n) ((1u << (_n)) - 1u)
#endif

#ifndef BIT_MASK64
#define BIT_MASK64(_n) ((1llu << (_n)) - 1llu)
#endif



//======================================================================================================================
// preprocessor macros

#define UTIL_CLAMP(_v, _lo, _hi) ((_v) < (_lo) ? (_lo) : ((_v) > (_hi) ? (_hi) : (_v)))
#define UTIL_MAX(_a, _b)         ((_a) > (_b) ? (_a) : (_b))
#define UTIL_MIN(_a, _b)         ((_a) < (_b) ? (_a) : (_b))
#define UTIL_ROUND(_v)           ((_v) < 0 ? ((_v) - 0.5f) : ((_v) + 0.5f))



#endif // IG_UTIL_MACROS_H
