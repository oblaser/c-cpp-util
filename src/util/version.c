/*
author          Oliver Blaser
date            12.02.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <stddef.h>
#include <stdint.h>

#include "version.h"



void UTIL_semver_clear(UTIL_semver_t* v)
{
    v->major = 0;
    v->minor = 0;
    v->patch = 0;
    v->prCount = 0;
    v->buildCount = 0;
}
