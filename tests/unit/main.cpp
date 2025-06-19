/*
author          Oliver Blaser
date            18.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"


TEST_CASE("C/C++ Util") { std::cout << std::endl << "Testing C/C++ Util ..." << std::endl; }



#include "macros.hpp"



#define UTIL_LOG_DEFINE_FUNCTIONS
#include "util/log.h"
