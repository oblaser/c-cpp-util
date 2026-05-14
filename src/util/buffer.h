/*
author          Oliver Blaser
date            14.05.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#ifndef IG_UTIL_BUFFER_H
#define IG_UTIL_BUFFER_H

#include <stddef.h>
#include <stdint.h>

#include "../util/bool.h"


#ifdef __cplusplus
extern "C" {
#endif

/*! \addtogroup grp_bufferLib
 * @{
 */



#define ___UTIL_BUFFER_DECLARE_MEMBERS(_type) \
    {                                         \
        size_t stackSize;                     \
        _type* stack;                         \
        _type* rp; /**< read pointer */       \
        _type* wp; /**< write pointer */      \
    }

#define ___UTIL_BUFFER_INIT(_buf, _stack, _stackSize) \
    {                                                 \
        (_buf)->stackSize = (_stackSize);             \
        (_buf)->stack = (_stack);                     \
        (_buf)->rp = (_buf)->stack;                   \
        (_buf)->wp = (_buf)->stack;                   \
    }

#define ___UTIL_BUFFER_CLEAR(_buf)  \
    {                               \
        (_buf)->rp = (_buf)->stack; \
        (_buf)->wp = (_buf)->stack; \
    }

#define ___UTIL_BUFFER_EMPTY_COND(_buf) ((_buf)->rp == (_buf)->wp) // empty condition

#define ___UTIL_BUFFER_EMPTY(_buf) return ___UTIL_BUFFER_EMPTY_COND(_buf)

#define ___UTIL_BUFFER_FRONT(_buf)                                                            \
    {                                                                                         \
        if ((_buf)->wp == (_buf)->stack) { return *((_buf)->stack + (_buf)->stackSize - 1); } \
        return *((_buf)->wp - 1);                                                             \
    }

#define ___UTIL_BUFFER_BACK(_buf) return *((_buf)->rp)

#define ___UTIL_BUFFER_CAPACITY(_buf) return ((_buf)->stackSize - 1)



typedef struct ___UTIL_BUFFER_DECLARE_MEMBERS(int) UTIL_fifo_t;
typedef struct ___UTIL_BUFFER_DECLARE_MEMBERS(float) UTIL_fifof_t;



static inline void UTIL_fifo_init(UTIL_fifo_t* buf, int* stack, size_t stackSize) { ___UTIL_BUFFER_INIT(buf, stack, stackSize); }
static inline void UTIL_fifo_clear(UTIL_fifo_t* buf) { ___UTIL_BUFFER_CLEAR(buf); }
static inline bool_t UTIL_fifo_empty(UTIL_fifo_t* buf) { ___UTIL_BUFFER_EMPTY(buf); }
static inline size_t UTIL_fifo_capacity(UTIL_fifo_t* buf) { ___UTIL_BUFFER_CAPACITY(buf); }

/**
 * The returned value is undefined if the buffer is empty.
 */
static inline int UTIL_fifo_front(UTIL_fifo_t* buf) { ___UTIL_BUFFER_FRONT(buf); }

/**
 * The returned value is undefined if the buffer is empty.
 */
static inline int UTIL_fifo_back(UTIL_fifo_t* buf) { ___UTIL_BUFFER_BACK(buf); }

/**
 * Pushes a new value to the front. If the buffer would overflow, -1 is returned and the buffer remains unchanged.
 *
 * @return 0 on success, -1 on error
 */
int UTIL_fifo_push(UTIL_fifo_t* buf, int value);

/**
 * Pushes a new value to the front and potentially overwrites the oldest vale.
 * If old data is overwritten (buffer overflow), `true` is returned.
 *
 * @retval `true` Old data was overwritten
 * @retval `false` No old data was overwritten
 */
bool_t UTIL_fifo_pushow(UTIL_fifo_t* buf, int value);

/**
 * @return The value removed from the back, or 0 if buffer is empty.
 */
int UTIL_fifo_pop(UTIL_fifo_t* buf);

/**
 * ERROR
 *
 * @param idx Index of the value to return in range [`0`, `size`), where `0` is _front_ and `size - 1` is _back_
 * @return The value at `idx`, undefined if `idx` is out of range
 */
int UTIL_fifo_get(UTIL_fifo_t* buf, size_t idx);

/**
 * @return Number of values in buffer
 */
size_t UTIL_fifo_size(UTIL_fifo_t* buf);



static inline void UTIL_fifof_init(UTIL_fifof_t* buf, float* stack, size_t stackSize) { ___UTIL_BUFFER_INIT(buf, stack, stackSize); }
static inline void UTIL_fifof_clear(UTIL_fifof_t* buf) { ___UTIL_BUFFER_CLEAR(buf); }
static inline bool_t UTIL_fifof_empty(UTIL_fifof_t* buf) { ___UTIL_BUFFER_EMPTY(buf); }
static inline size_t UTIL_fifof_capacity(UTIL_fifof_t* buf) { ___UTIL_BUFFER_CAPACITY(buf); }

/**
 * The returned value is undefined if the buffer is empty.
 */
static inline float UTIL_fifof_front(UTIL_fifof_t* buf) { ___UTIL_BUFFER_FRONT(buf); }

/**
 * The returned value is undefined if the buffer is empty.
 */
static inline float UTIL_fifof_back(UTIL_fifof_t* buf) { ___UTIL_BUFFER_BACK(buf); }

/**
 * Pushes a new value to the front. If the buffer would overflow, -1 is returned and the buffer remains unchanged.
 *
 * @return 0 on success, -1 on error
 */
int UTIL_fifof_push(UTIL_fifof_t* buf, float value);

/**
 * Pushes a new value to the front and potentially overwrites the oldest vale.
 * If old data is overwritten (buffer overflow), `true` is returned.
 *
 * @retval `true` Old data was overwritten
 * @retval `false` No old data was overwritten
 */
bool_t UTIL_fifof_pushow(UTIL_fifof_t* buf, float value);

/**
 * @return The value removed from the back, or 0 if buffer is empty.
 */
float UTIL_fifof_pop(UTIL_fifof_t* buf);

/**
 * ERROR
 *
 * @param idx Index of the value to return in range [`0`, `size`), where `0` is _front_ and `size - 1` is _back_
 * @return The value at `idx`, undefined if `idx` is out of range
 */
float UTIL_fifof_get(UTIL_fifof_t* buf, size_t idx);

/**
 * @return Number of values in buffer
 */
size_t UTIL_fifof_size(UTIL_fifof_t* buf);



/*! @} */

#ifdef __cplusplus
}
#endif

#endif // IG_UTIL_BUFFER_H
