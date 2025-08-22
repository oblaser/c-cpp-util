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



//! \name Character Classification
/// @{

static inline int UTIL_isBlank(int ch) { return ((ch == 0x09) || (ch == 0x20)); }
static inline int UTIL_isCntrl(int ch) { return (((ch >= 0x00) && (ch <= 0x1F)) || (ch == 0x7F)); }
static inline int UTIL_isDigit(int ch) { return ((ch >= 0x30) && (ch <= 0x39)); }
static inline int UTIL_isGraph(int ch) { return ((ch >= 0x21) && (ch <= 0x7E)); }
static inline int UTIL_isHex(int ch)
{
    // clang-format off
    return (
        ((ch >= 0x30) && (ch <= 0x39)) ||
        ((ch >= 0x41) && (ch <= 0x46)) ||
        ((ch >= 0x61) && (ch <= 0x66))
    );
    // clang-format on
}
static inline int UTIL_isLower(int ch) { return ((ch >= 0x61) && (ch <= 0x7A)); }
static inline int UTIL_isNull(int ch) { return (ch == 0x00); }
static inline int UTIL_isPrint(int ch) { return ((ch >= 0x20) && (ch <= 0x7E)); }
static inline int UTIL_isPunct(int ch)
{
    // clang-format off
    return (
        ((ch >= 0x21) && (ch <= 0x2F)) ||
        ((ch >= 0x3A) && (ch <= 0x40)) ||
        ((ch >= 0x5B) && (ch <= 0x60)) ||
        ((ch >= 0x7B) && (ch <= 0x7E))
    );
    // clang-format on
}
static inline int UTIL_isSpace(int ch) { return (((ch >= 0x09) && (ch <= 0x0D)) || (ch == 0x20)); }
static inline int UTIL_isUpper(int ch) { return ((ch >= 0x41) && (ch <= 0x5A)); }

static inline int UTIL_isAlpha(int ch) { return (UTIL_isLower(ch) || UTIL_isUpper(ch)); }
static inline int UTIL_isAlnum(int ch) { return (UTIL_isAlpha(ch) || UTIL_isDigit(ch)); }

/// @}



//! \name String Manipulation
/// @{

char* UTIL_strcpy(char* dst, const char* src);

/**
 * In contrast to the standard `strncpy()`, this implementation stops if, after copying the terminating null character
 * from src, count is not reached.
 */
char* UTIL_strncpy(char* dst, const char* src, size_t n);

char* UTIL_strcat(char* dst, const char* src);

/**
 * Always appends a null terminator.
 */
char* UTIL_strncat(char* dst, const char* src, size_t n);

char* UTIL_strlower_ascii(char* str);
char* UTIL_strupper_ascii(char* str);

/// @}



//! \name String Examination
/// @{

size_t UTIL_strlen(const char* str);
size_t UTIL_strnlen(const char* str, size_t n);

int UTIL_strcmp(const char* lhs, const char* rhs);
int UTIL_strncmp(const char* lhs, const char* rhs, size_t n);

static inline int UTIL_streq(const char* lhs, const char* rhs) { return (UTIL_strcmp(lhs, rhs) == 0); }
static inline int UTIL_strneq(const char* lhs, const char* rhs, size_t n) { return (UTIL_strncmp(lhs, rhs, n) == 0); }

/**
 * See <a href="https://en.cppreference.com/w/c/string/byte/strchr.html" target="_blank">cppreference.com strchr</a>
 */
const char* UTIL_strchr(const char* str, int ch);

/**
 * Like `UTIL_strchr(const char* str, int ch)`, but only the first `n` characters are searched.
 */
const char* UTIL_strnchr(const char* str, int ch, size_t n);

/// @}



/*! @} */

#ifdef __cplusplus
}
#endif

#endif // IG_UTIL_STRING_H
