/*
author          Oliver Blaser
date            14.05.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>

#include "../util/bool.h"
#include "buffer.h"



#define INCREMENT_POINTER(_buf, _name)                                                                   \
    {                                                                                                    \
        if ((_buf)->_name == ((_buf)->stack + (_buf)->stackSize - 1)) { (_buf)->_name = (_buf)->stack; } \
        else { ++((_buf)->_name); }                                                                      \
    }

#define BUFFER_PUSH(_buf, _value)                                            \
    {                                                                        \
        if ((((_buf)->wp + 1) == (_buf)->rp) ||                         /**/ \
            (                                                           /**/ \
             ((_buf)->wp == ((_buf)->stack + (_buf)->stackSize - 1)) && /**/ \
             ((_buf)->rp == (_buf)->stack)                              /**/ \
             )                                                          /**/ \
        )                                                                    \
        {                                                                    \
            return -1;                                                       \
        }                                                                    \
                                                                             \
        *((_buf)->wp) = (_value);                                            \
        INCREMENT_POINTER(_buf, wp);                                         \
        return 0;                                                            \
    }

#define BUFFER_PUSHOW(_buf, _value)      \
    {                                    \
        *((_buf)->wp) = (_value);        \
        INCREMENT_POINTER(_buf, wp);     \
                                         \
        if (((_buf)->wp) == (_buf)->rp)  \
        {                                \
            INCREMENT_POINTER(_buf, rp); \
            return true;                 \
        }                                \
                                         \
        return false;                    \
    }

#define BUFFER_POP(_buf, _type)                            \
    {                                                      \
        if (___UTIL_BUFFER_EMPTY_COND(_buf)) { return 0; } \
                                                           \
        _type tmp = *((_buf)->rp);                         \
        INCREMENT_POINTER(_buf, rp);                       \
        return tmp;                                        \
    }

#define BUFFER_GET(_buf, _idx)                                                                    \
    {                                                                                             \
        const uintptr_t offs = ((_buf)->wp - (_buf)->stack);                                      \
                                                                                                  \
        if (((_idx) + 1) > offs) { return *((_buf)->stack + (_buf)->stackSize - (_idx) - offs); } \
                                                                                                  \
        return *((_buf)->wp - 1 - (_idx));                                                        \
    }

#define BUFFER_SIZE(_buf)                                                   \
    {                                                                       \
        if ((_buf)->wp >= (_buf)->rp) { return ((_buf)->wp - (_buf)->rp); } \
        return ((_buf)->stackSize - ((_buf)->rp - (_buf)->wp));             \
    }



int UTIL_fifo_push(UTIL_fifo_t* buf, int value) { BUFFER_PUSH(buf, value); }
bool_t UTIL_fifo_pushow(UTIL_fifo_t* buf, int value) { BUFFER_PUSHOW(buf, value); }
int UTIL_fifo_pop(UTIL_fifo_t* buf) { BUFFER_POP(buf, int); }
int UTIL_fifo_get(UTIL_fifo_t* buf, size_t idx) { BUFFER_GET(buf, idx); }
size_t UTIL_fifo_size(UTIL_fifo_t* buf) { BUFFER_SIZE(buf); }



int UTIL_fifof_push(UTIL_fifof_t* buf, float value) { BUFFER_PUSH(buf, value); }
bool_t UTIL_fifof_pushow(UTIL_fifof_t* buf, float value) { BUFFER_PUSHOW(buf, value); }
float UTIL_fifof_pop(UTIL_fifof_t* buf) { BUFFER_POP(buf, float); }
float UTIL_fifof_get(UTIL_fifof_t* buf, size_t idx) { BUFFER_GET(buf, idx); }
size_t UTIL_fifof_size(UTIL_fifof_t* buf) { BUFFER_SIZE(buf); }
