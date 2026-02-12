
# author        Oliver Blaser
# date          12.02.2026
# copyright     MIT - Copyright (c) 2026 Oliver Blaser


CC = gcc
CC_BIN = gcc
CC_LINK = gcc
CXX = g++
CXX_BIN = g++
CXX_LINK = g++

SRC_DIR = ../../../../src

DEFINE_FLAGS = -DCONFIG_UTIL_LOG_MAX_LEVEL=0
INCLUDE_DIR_FLAGS = -I$(SRC_DIR)

CFLAGS_COMMON = $(INCLUDE_DIR_FLAGS) $(DEFINE_FLAGS) --pedantic -Wall -Wextra -Werror=format -Werror=overflow -Werror=return-type -Werror=array-bounds -Werror=unused-parameter -Wdouble-promotion
CFLAGS_CC = -Werror=discarded-qualifiers -Werror=implicit -Werror=incompatible-pointer-types -Werror=int-conversion -Werror=pointer-sign
CFLAGS_CXX = -Werror=reorder -Werror=switch #-Wno-psabi

SRC_FILES_LIB = $(SRC_DIR)/util/ansi-esc.h $(SRC_DIR)/util/bool.h $(SRC_DIR)/util/log.h $(SRC_DIR)/util/macros.h $(SRC_DIR)/util/time.c $(SRC_DIR)/util/time.h $(SRC_DIR)/util/string.c $(SRC_DIR)/util/string.h $(SRC_DIR)/util/version.c $(SRC_DIR)/util/version.h # $(SRC_DIR)/util/bits/ansi-esc.h $(SRC_DIR)/util/log_ansi-esc_disabled.h $(SRC_DIR)/util/log_ansi-esc_enabled.h $(SRC_DIR)/util/log_ansi-esc_rtt.h $(SRC_DIR)/util/log_ansi-esc.h $(SRC_DIR)/util/log_zephyr.h
OBJS_LIB = time.o string.o version.o
OBJS_TEST = test-bool-c.o test-string.o test-version.o
OBJS = main.o $(OBJS_TEST) $(OBJS_LIB)
EXE = test_unit.bin

FILES_TO_CLEAN = $(OBJS) $(EXE)

BUILDDATE = $(shell date +"%Y-%m-%d-%H-%M")



all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CFLAGS_COMMON) $(CFLAGS_CXX) -o $(EXE) $(OBJS)

main.o: $(OBJS_LIB) $(OBJS_TEST) $(SRC_FILES_LIB) ../../main.cpp ../../bool.hpp $(SRC_DIR)/util/bool.h ../../log.hpp $(SRC_DIR)/util/log.h ../../macros.hpp $(SRC_DIR)/util/macros.h ../../time.hpp $(SRC_DIR)/util/time.h
	$(CXX) -c $(CFLAGS_COMMON) $(CFLAGS_CXX) ../../main.cpp

test-bool-c.o: ../../bool.c ../../bool.h $(SRC_DIR)/util/bool.h
	$(CC) -o test-bool-c.o -c $(CFLAGS_COMMON) $(CFLAGS_CC) ../../bool.c

test-string.o: string.o ../../string.cpp $(SRC_DIR)/util/macros.h
	$(CXX) -o test-string.o -c $(CFLAGS_COMMON) $(CFLAGS_CXX) ../../string.cpp

test-version.o: version.o ../../version.cpp
	$(CXX) -o test-version.o -c $(CFLAGS_COMMON) $(CFLAGS_CXX) ../../version.cpp

time.o: $(SRC_DIR)/util/time.c $(SRC_DIR)/util/time.h
	$(CC) -c $(CFLAGS_COMMON) $(CFLAGS_CC) $(SRC_DIR)/util/time.c

string.o: $(SRC_DIR)/util/string.c $(SRC_DIR)/util/string.h
	$(CC) -c $(CFLAGS_COMMON) $(CFLAGS_CC) $(SRC_DIR)/util/string.c

version.o: $(SRC_DIR)/util/version.c $(SRC_DIR)/util/version.h
	$(CC) -c $(CFLAGS_COMMON) $(CFLAGS_CC) $(SRC_DIR)/util/version.c

clean:
	rm $(FILES_TO_CLEAN)

run: $(EXE)
	@echo "\033[32m########################################\033[39m"
	./$(EXE)
