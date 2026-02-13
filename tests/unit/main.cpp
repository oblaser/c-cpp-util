/*
author          Oliver Blaser
date            18.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"


TEST_CASE("C/C++ Util")
{
    std::cout << std::endl;
    std::cout << "Testing C/C++ Util ..." << std::endl;
    std::cout << std::endl;
}



#define UTIL_LOG_DEFINE_FUNCTIONS
#include "util/log.h"



#include "bool.hpp"
#include "log.hpp"
#include "macros.hpp"
#include "time.hpp"



static void hexDump_dataToString(char* buffer, const uint8_t* p, const uint8_t* end)
{
    size_t i = 0;

    while ((i < 16) && (p < end))
    {
        if (isprint(*p)) { buffer[i] = (char)(*p); }
        else { buffer[i] = '.'; }

        ++p;
        ++i;
    }

    while (i < 16)
    {
        buffer[i] = ' ';
        ++i;
    }

    buffer[i] = 0;
}

void hexDump(const uint8_t* data, size_t count)
{
    if (!data) { count = 0; }

    const uint8_t* const end = (data + count);

    for (size_t i = 0; i < count; ++i)
    {
        const int byte = *(data + i);
        const size_t row = (i / 16);
        const size_t col = (i % 16);

        if (col == 0)
        {
            if (i == 0) { printf("%05zx ", i); }
            else
            {
                char str[17];
                hexDump_dataToString(str, data + 16 * (row - 1), end);
                printf("  | %s\n%05zx ", str, i);
            }
        }
        else if (col == 8) { printf(" "); }

        printf(" %02x", byte);
    }

    if (count == 0) { printf("%05x ", 0); }



    size_t lastRowSize = (count % 16);
    if ((lastRowSize == 0) && (count != 0)) { lastRowSize = 16; }
    const size_t remaining = (16 - lastRowSize);

    if (remaining >= 8) { printf(" "); }
    for (size_t i = 0; i < remaining; ++i) { printf("   "); }

    char str[17];
    hexDump_dataToString(str, end - lastRowSize, end);
    printf("  | %s", str);

    printf("\n");
}
