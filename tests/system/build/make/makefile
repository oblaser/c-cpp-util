
# author        Oliver Blaser
# date          18.06.2025
# copyright     MIT - Copyright (c) 2025 Oliver Blaser


CC = gcc
CC_BIN = gcc
CC_LINK = gcc
CXX = g++
CXX_BIN = g++
CXX_LINK = g++

SRC_DIR = ../../../../src

DEFINE_FLAGS = -DCONFIG_UTIL_LOG_MAX_LEVEL=4 -DCONFIG_UTIL_LOG_NO_ANSIESC=0
INCLUDE_DIR_FLAGS = -I$(SRC_DIR)

CFLAGS_COMMON = $(INCLUDE_DIR_FLAGS) $(DEFINE_FLAGS) --pedantic -Wall -Werror=format -Werror=overflow -Werror=return-type -Wdouble-promotion -Werror=unused-parameter
CFLAGS_CC = -Werror=discarded-qualifiers -Werror=implicit -Werror=incompatible-pointer-types -Werror=int-conversion -Werror=pointer-sign
CFLAGS_CXX = -Werror=reorder -Werror=switch #-Wno-psabi

SRC_FILES_LIB = $(SRC_DIR)/util/ansi-esc.h $(SRC_DIR)/util/bool.h $(SRC_DIR)/util/log.h $(SRC_DIR)/util/macros.h $(SRC_DIR)/util/time.c $(SRC_DIR)/util/time.h $(SRC_DIR)/util/string.c $(SRC_DIR)/util/string.h # $(SRC_DIR)/util/bits/ansi-esc.h $(SRC_DIR)/util/log_ansi-esc_disabled.h $(SRC_DIR)/util/log_ansi-esc_enabled.h $(SRC_DIR)/util/log_ansi-esc_rtt.h $(SRC_DIR)/util/log_ansi-esc.h $(SRC_DIR)/util/log_zephyr.h
OBJS_LIB = time.o string.o
OBJS = main.o $(OBJS_LIB)
EXE = test_system.bin

FILES_TO_CLEAN = $(OBJS) $(EXE)

BUILDDATE = $(shell date +"%Y-%m-%d-%H-%M")



all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CFLAGS_COMMON) $(CFLAGS_CXX) -o $(EXE) $(OBJS)

main.o: $(OBJS_LIB) $(SRC_FILES_LIB) ../../main.cpp
	$(CXX) -c $(CFLAGS_COMMON) $(CFLAGS_CXX) ../../main.cpp

time.o: $(SRC_DIR)/util/time.c $(SRC_DIR)/util/time.h
	$(CC) -c $(CFLAGS_COMMON) $(CFLAGS_CC) $(SRC_DIR)/util/time.c

string.o: $(SRC_DIR)/util/string.c $(SRC_DIR)/util/string.h
	$(CC) -c $(CFLAGS_COMMON) $(CFLAGS_CC) $(SRC_DIR)/util/string.c

clean:
	rm $(FILES_TO_CLEAN)

run: $(EXE)
	@echo "\033[32m########################################\033[39m"
	./$(EXE)
