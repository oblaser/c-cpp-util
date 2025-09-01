/*
author          Oliver Blaser
date            30.08.2025
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



/**
 * Using `SIZE_MAX` as string `npos` indicator.
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

/**
 * Copies `src` to `dst`, including the null terminator.
 *
 * See <a href="https://en.cppreference.com/w/c/string/byte/strcpy.html" target="_blank">cppreference.com</a> for more
 * detail.
 *
 * @param dst Pointer to the buffer to write to
 * @param src Pointer to the string to read from
 * @param [out] end _optional_ Pointer to a pointer which will point, after successful operation, to the null terminator
 * in the destination buffer
 * @return `dst`
 */
char* UTIL_strcpy(char* dst, const char* src, char** end);

/**
 * In contrast to the standard `strncpy()`, this implementation stops if, after copying the terminating null character
 * from `src`, `count` is not reached.
 *
 * The resulting character array may be not null terminated.
 *
 * @param dst Pointer to the buffer to write to
 * @param src Pointer to the string to read from
 * @param [out] end _optional_ Pointer to a pointer which will point, after successful operation, to the position after
 * the last copied character or the null terminator in the destination buffer
 * @return `dst`
 */
char* UTIL_strncpy(char* dst, const char* src, size_t n, char** end);

/**
 * Appends `src` to `dst`, including the null terminator.
 *
 * See <a href="https://en.cppreference.com/w/c/string/byte/strcat.html" target="_blank">cppreference.com</a> for more
 * detail.
 *
 * @param dst Pointer to the buffer to append to
 * @param src Pointer to the string to read from
 * @param [out] end _optional_ Pointer to a pointer which will point, after successful operation, to the null terminator
 * in the destination buffer
 * @return `dst`
 */
char* UTIL_strcat(char* dst, const char* src, char** end);

/**
 * Always appends a null terminator, thus `n+1` characters may be written to `dst`.
 *
 * See <a href="https://en.cppreference.com/w/c/string/byte/strncat.html" target="_blank">cppreference.com</a> for more
 * detail.
 *
 * @param dst Pointer to the buffer to append to
 * @param src Pointer to the string to read from
 * @param [out] end _optional_ Pointer to a pointer which will point, after successful operation, to the null terminator
 * in the destination buffer
 * @return `dst`
 */
char* UTIL_strncat(char* dst, const char* src, size_t n, char** end);

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



//! \name String Classification
/// @{

int UTIL_isIntStr(const char* str, size_t count);
int UTIL_isUIntStr(const char* str, size_t count);
int UTIL_isHexStr(const char* str, size_t count);

/// @}



//! \name String Conversion
//!
//! <b>number to string</b>
//! Parameters:
//! - `dst` Pointer to the buffer to write to
//! - `value` The value to be converted
//! - `end` [out] <i>optional</i> Pointer to a pointer which will point, after successful operation, to the null
//!   terminator in the destination buffer
//!
//! <b>string to number</b>
//! On error `errno` is set to `ERANGE` or `EINVAL`.
//! Parameters:
//! - `str` Pointer to a string to be converted
//! - `end` [out] <i>optional</i> Pointer to a pointer which will point to the character after the converted number
//!
//! If the value is too big for the target data type, `errno` is set to `ERANGE` and the types minimal/maximal value is
//! returned.
//! If the string does not represent a number, `errno` is set to `EINVAL` and `0` is returned.
//!
/// @{

char* UTIL_i8tos(char* dst, int8_t value, char** end);
char* UTIL_i16tos(char* dst, int16_t value, char** end);
char* UTIL_i32tos(char* dst, int32_t value, char** end);
char* UTIL_i64tos(char* dst, int64_t value, char** end);

char* UTIL_ui8tos(char* dst, uint8_t value, char** end);
char* UTIL_ui16tos(char* dst, uint16_t value, char** end);
char* UTIL_ui32tos(char* dst, uint32_t value, char** end);
char* UTIL_ui64tos(char* dst, uint64_t value, char** end);

int8_t UTIL_stoi8(const char* str, char** end);
int16_t UTIL_stoi16(const char* str, char** end);
int32_t UTIL_stoi32(const char* str, char** end);
int64_t UTIL_stoi64(const char* str, char** end);

uint8_t UTIL_stoui8(const char* str, char** end);
uint16_t UTIL_stoui16(const char* str, char** end);
uint32_t UTIL_stoui32(const char* str, char** end);
uint64_t UTIL_stoui64(const char* str, char** end);

char* UTIL_ui8toxs(char* dst, uint8_t value, char** end);
char* UTIL_ui16toxs(char* dst, uint16_t value, char** end);
char* UTIL_ui32toxs(char* dst, uint32_t value, char** end);
char* UTIL_ui64toxs(char* dst, uint64_t value, char** end);

static inline char* UTIL_i8toxs(char* dst, int8_t value, char** end) { return UTIL_ui8toxs(dst, (uint8_t)value, end); }
static inline char* UTIL_i16toxs(char* dst, int16_t value, char** end) { return UTIL_ui16toxs(dst, (uint16_t)value, end); }
static inline char* UTIL_i32toxs(char* dst, int32_t value, char** end) { return UTIL_ui32toxs(dst, (uint32_t)value, end); }
static inline char* UTIL_i64toxs(char* dst, int64_t value, char** end) { return UTIL_ui64toxs(dst, (uint64_t)value, end); }

uint8_t UTIL_xstoui8(const char* str, char** end);
uint16_t UTIL_xstoui16(const char* str, char** end);
uint32_t UTIL_xstoui32(const char* str, char** end);
uint64_t UTIL_xstoui64(const char* str, char** end);

static inline int8_t UTIL_xstoi8(const char* str, char** end) { return (int8_t)UTIL_xstoui8(str, end); }
static inline int16_t UTIL_xstoi16(const char* str, char** end) { return (int16_t)UTIL_xstoui16(str, end); }
static inline int32_t UTIL_xstoi32(const char* str, char** end) { return (int32_t)UTIL_xstoui32(str, end); }
static inline int64_t UTIL_xstoi64(const char* str, char** end) { return (int64_t)UTIL_xstoui64(str, end); }

/**
 * If `count` is `0`: `*dst=0` and `*end=dst`.
 */
char* UTIL_dataToHexStr(char* dst, const uint8_t* data, size_t count, char** end);

/**
 * If `count` is `0`: `*dst=0` and `*end=dst`.
 */
char* UTIL_dataToHexStrDelim(char* dst, const uint8_t* data, size_t count, char delimiter, char** end);

/// @}



/*! @} */

#ifdef __cplusplus
}
#endif

#endif // IG_UTIL_STRING_H
