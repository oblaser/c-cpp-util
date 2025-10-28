/*
author          Oliver Blaser
date            27.10.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <stdio.h>

#include "util/ansi-esc.h"

#define LOG_MODULE_LEVEL LOG_LEVEL_DBG
#define LOG_MODULE_NAME  MAIN
#include "util/log.h"



int main()
{
    LOG_ERR("error     %s %i", __func__, __LINE__);
    LOG_WRN("warning   %s %i", __func__, __LINE__);
    LOG_INF("info      %s %i", __func__, __LINE__);

    printf(CSI_CUF(35) SGR_BG_YELLOW " 0123456789abcdef 0123456789abcdef " SGR_BG_DEFAULT "\r");
    fflush(stdout);

    LOG_DBG("debug     %s %i", __func__, __LINE__);

    printf("\n");

    return 0;
}



#define UTIL_LOG_DEFINE_FUNCTIONS
#include "util/log.h"
