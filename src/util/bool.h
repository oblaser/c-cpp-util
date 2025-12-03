/*
author          Oliver Blaser
date            03.12.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_BOOL_H
#define IG_UTIL_BOOL_H



enum
{
    UTIL_false = 0,
    UTIL_true = 1,

#ifndef __cplusplus

#ifndef false
    false = UTIL_false,
#endif

#ifndef true
    true = UTIL_true,
#endif

#endif // __cplusplus
};



typedef int UTIL_bool_t;

#if !CONFIG_UTIL_BOOL_NO_BOOL_T
typedef UTIL_bool_t bool_t;
#endif



#endif // IG_UTIL_BOOL_H
