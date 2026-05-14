/*
author          Oliver Blaser
date            14.05.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <cstddef>
#include <cstdint>

#include "util/buffer.h"
#include "util/macros.h"

#include "catch2/catch.hpp"



TEST_CASE("buffer.h fifo")
{
    int stack[] = { 1, 2, 3, 4, 5 };
    UTIL_fifo_t buffer;

    UTIL_fifo_init(&buffer, stack, SIZEOF_ARRAY(stack));

    CHECK(UTIL_fifo_empty(&buffer) == true);
    CHECK(UTIL_fifo_size(&buffer) == 0);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));

    CHECK(UTIL_fifo_pop(&buffer) == 0);

    CHECK(UTIL_fifo_empty(&buffer) == true);
    CHECK(UTIL_fifo_size(&buffer) == 0);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));



    REQUIRE(UTIL_fifo_push(&buffer, 11) == 0);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 1);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 11);
    CHECK(UTIL_fifo_back(&buffer) == 11);
    CHECK(UTIL_fifo_get(&buffer, 0) == 11);



    REQUIRE(UTIL_fifo_push(&buffer, 24) == 0);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 2);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 24);
    CHECK(UTIL_fifo_back(&buffer) == 11);
    CHECK(UTIL_fifo_get(&buffer, 0) == 24);
    CHECK(UTIL_fifo_get(&buffer, 1) == 11);



    REQUIRE(UTIL_fifo_push(&buffer, 39) == 0);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 3);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 39);
    CHECK(UTIL_fifo_back(&buffer) == 11);
    CHECK(UTIL_fifo_get(&buffer, 0) == 39);
    CHECK(UTIL_fifo_get(&buffer, 1) == 24);
    CHECK(UTIL_fifo_get(&buffer, 2) == 11);



    REQUIRE(UTIL_fifo_pop(&buffer) == 11);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 2);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 39);
    CHECK(UTIL_fifo_back(&buffer) == 24);
    CHECK(UTIL_fifo_get(&buffer, 0) == 39);
    CHECK(UTIL_fifo_get(&buffer, 1) == 24);



    REQUIRE(UTIL_fifo_pushow(&buffer, 40) == false);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 3);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 40);
    CHECK(UTIL_fifo_back(&buffer) == 24);
    CHECK(UTIL_fifo_get(&buffer, 0) == 40);
    CHECK(UTIL_fifo_get(&buffer, 1) == 39);
    CHECK(UTIL_fifo_get(&buffer, 2) == 24);



    REQUIRE(UTIL_fifo_push(&buffer, 55) == 0);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 4);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 55);
    CHECK(UTIL_fifo_back(&buffer) == 24);
    CHECK(UTIL_fifo_get(&buffer, 0) == 55);
    CHECK(UTIL_fifo_get(&buffer, 1) == 40);
    CHECK(UTIL_fifo_get(&buffer, 2) == 39);
    CHECK(UTIL_fifo_get(&buffer, 3) == 24);



    REQUIRE(UTIL_fifo_push(&buffer, 62) == -1);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 4);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 55);
    CHECK(UTIL_fifo_back(&buffer) == 24);
    CHECK(UTIL_fifo_get(&buffer, 0) == 55);
    CHECK(UTIL_fifo_get(&buffer, 1) == 40);
    CHECK(UTIL_fifo_get(&buffer, 2) == 39);
    CHECK(UTIL_fifo_get(&buffer, 3) == 24);



    REQUIRE(UTIL_fifo_pushow(&buffer, 62) == true);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 4);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 62);
    CHECK(UTIL_fifo_back(&buffer) == 39);
    CHECK(UTIL_fifo_get(&buffer, 0) == 62);
    CHECK(UTIL_fifo_get(&buffer, 1) == 55);
    CHECK(UTIL_fifo_get(&buffer, 2) == 40);
    CHECK(UTIL_fifo_get(&buffer, 3) == 39);



    REQUIRE(UTIL_fifo_pushow(&buffer, 78) == true);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 4);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 78);
    CHECK(UTIL_fifo_back(&buffer) == 40);
    CHECK(UTIL_fifo_get(&buffer, 0) == 78);
    CHECK(UTIL_fifo_get(&buffer, 1) == 62);
    CHECK(UTIL_fifo_get(&buffer, 2) == 55);
    CHECK(UTIL_fifo_get(&buffer, 3) == 40);



    REQUIRE(UTIL_fifo_pop(&buffer) == 40);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 3);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 78);
    CHECK(UTIL_fifo_back(&buffer) == 55);
    CHECK(UTIL_fifo_get(&buffer, 0) == 78);
    CHECK(UTIL_fifo_get(&buffer, 1) == 62);
    CHECK(UTIL_fifo_get(&buffer, 2) == 55);



    REQUIRE(UTIL_fifo_pushow(&buffer, 81) == false);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 4);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 81);
    CHECK(UTIL_fifo_back(&buffer) == 55);
    CHECK(UTIL_fifo_get(&buffer, 0) == 81);
    CHECK(UTIL_fifo_get(&buffer, 1) == 78);
    CHECK(UTIL_fifo_get(&buffer, 2) == 62);
    CHECK(UTIL_fifo_get(&buffer, 3) == 55);



    REQUIRE(UTIL_fifo_pop(&buffer) == 55);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 3);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 81);
    CHECK(UTIL_fifo_back(&buffer) == 62);
    CHECK(UTIL_fifo_get(&buffer, 0) == 81);
    CHECK(UTIL_fifo_get(&buffer, 1) == 78);
    CHECK(UTIL_fifo_get(&buffer, 2) == 62);



    REQUIRE(UTIL_fifo_pop(&buffer) == 62);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 2);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 81);
    CHECK(UTIL_fifo_back(&buffer) == 78);
    CHECK(UTIL_fifo_get(&buffer, 0) == 81);
    CHECK(UTIL_fifo_get(&buffer, 1) == 78);



    REQUIRE(UTIL_fifo_pop(&buffer) == 78);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 1);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 81);
    CHECK(UTIL_fifo_back(&buffer) == 81);
    CHECK(UTIL_fifo_get(&buffer, 0) == 81);



    REQUIRE(UTIL_fifo_pop(&buffer) == 81);

    CHECK(UTIL_fifo_empty(&buffer) == true);
    CHECK(UTIL_fifo_size(&buffer) == 0);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));



    REQUIRE(UTIL_fifo_pop(&buffer) == 0);

    CHECK(UTIL_fifo_empty(&buffer) == true);
    CHECK(UTIL_fifo_size(&buffer) == 0);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));



    REQUIRE(UTIL_fifo_pop(&buffer) == 0);

    CHECK(UTIL_fifo_empty(&buffer) == true);
    CHECK(UTIL_fifo_size(&buffer) == 0);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));



    UTIL_fifo_push(&buffer, 100);
    UTIL_fifo_push(&buffer, 245);
    UTIL_fifo_push(&buffer, 374);

    CHECK(UTIL_fifo_empty(&buffer) == false);
    CHECK(UTIL_fifo_size(&buffer) == 3);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
    CHECK(UTIL_fifo_front(&buffer) == 374);
    CHECK(UTIL_fifo_back(&buffer) == 100);
    CHECK(UTIL_fifo_get(&buffer, 0) == 374);
    CHECK(UTIL_fifo_get(&buffer, 1) == 245);
    CHECK(UTIL_fifo_get(&buffer, 2) == 100);



    UTIL_fifo_clear(&buffer);

    CHECK(UTIL_fifo_empty(&buffer) == true);
    CHECK(UTIL_fifo_size(&buffer) == 0);
    CHECK(UTIL_fifo_capacity(&buffer) == (SIZEOF_ARRAY(stack) - 1));
}
