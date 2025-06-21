/*
author          Oliver Blaser
date            21.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_UTIL_STRING_H
#define IG_UTIL_STRING_H

#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

/*! \addtogroup grp_stringLib
 * @{
 */



#define UTIL_npos (SIZE_MAX)



//! \name String Examination
/// @{

/**
 * See <a href="https://en.cppreference.com/w/c/string/byte/strlen.html" target="_blank">cppreference.com strlen</a>.
 */
size_t UTIL_strlen(const char* str);
size_t UTIL_strnlen(const char* str, size_t n);

/**
 * See <a href="https://en.cppreference.com/w/c/string/byte/strchr.html" target="_blank">cppreference.com strchr</a>
 */
const char* UTIL_strchr(const char* str, int ch);

/**
 * Like `UTIL_strchr(const char* str, int ch)`, but only searches the first `n` characters.
 */
const char* UTIL_strnchr(const char* str, int ch, size_t n);

/// @}



/*! @} */

#ifdef __cplusplus
}
#endif

#endif // IG_UTIL_STRING_H
