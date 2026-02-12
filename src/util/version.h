/*
author          Oliver Blaser
date            12.02.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#ifndef IG_UTIL_VERSION_H
#define IG_UTIL_VERSION_H

#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif



typedef struct
{
    int32_t major;
    int32_t minor;
} UTIL_mmver_t;

typedef struct
{
    void* buffer;      ///< _internal use_
    size_t bufferSize; ///< _internal use_

    size_t prCount;    ///< Number of pre-release identifiers
    size_t buildCount; ///< Number of build identifiers

    int32_t major;
    int32_t minor;
    int32_t patch;
} UTIL_semver_t;



void UTIL_mmver_clear(UTIL_mmver_t* v);
int UTIL_mmvercmp(const UTIL_mmver_t* a, const UTIL_mmver_t* b);
char* UTIL_mmvertos(char* dst, size_t size, const UTIL_mmver_t* v, char** end);
int UTIL_stommver(UTIL_mmver_t* v, const char* str);



/**
 * @brief Resets/clears/initialises the structure.
 *
 * Sets the version to `0.0.0`.
 *
 * @param [out] v
 */
void UTIL_semver_clear(UTIL_semver_t* v);

/**
 * @brief Sets pre-release and build identifiers.
 *
 * @param [out] v
 * @param pr Pre-release identifier list
 * @param prCount Number of pre-release identifiers
 * @param build Build identifier list
 * @param buildCount Number of build identifiers
 * @return `0` on success, `-1` on error and `errno` is set accordingly
 */
int UTIL_semver_setPrBuild(UTIL_semver_t* v, const char* const * pr, size_t prCount, const char* const * build, size_t buildCount);

int UTIL_semvercmp(const UTIL_semver_t* a, const UTIL_semver_t* b);

/**
 * @brief Serialises an `UTIL_semver_t` to a string.
 *
 * If the destination buffer is too small, `errno` is set to `ENOMEM` and `NULL` is returned.
 *
 * @param dst Destination buffer
 * @param size Size of the destination buffer
 * @param v
 * @param [out] end <i>optional</i> Pointer to a pointer which will point, after successful operation, to the null terminator in the destination buffer
 * @return `dst` on success, `NULL` on error and `errno` is set accordingly
 */
char* UTIL_semvertos(char* dst, size_t size, const UTIL_semver_t* v, char** end);

/**
 * @brief Parses a semver string.
 *
 * If a value is out of range of the target data type, `errno` is set to `ERANGE` and the types maximal or minimal value
 * is returned.
 * If the string is not a valid semver string, `errno` is set to `EINVAL` and `-1` is returned.
 *
 * @param [out] v
 * @param str Version string according to semver
 * @return `0` on success, `-1` on error and `errno` is set accordingly
 */
int UTIL_stosemver(UTIL_semver_t* v, const char* str);



#ifdef __cplusplus
}
#endif

#endif // IG_UTIL_VERSION_H
