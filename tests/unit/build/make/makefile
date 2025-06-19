
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

DEFINE_FLAGS = -DCONFIG_LOG_LEVEL=0
INCLUDE_DIR_FLAGS = -I$(SRC_DIR)

CFLAGS_COMMON = $(INCLUDE_DIR_FLAGS) $(DEFINE_FLAGS) -Wall -Werror=format -Werror=overflow -Werror=return-type -Wdouble-promotion
CFLAGS_CC = -Werror=discarded-qualifiers -Werror=implicit -Werror=incompatible-pointer-types -Werror=int-conversion -Werror=pointer-sign
CFLAGS_CXX = -Werror=reorder -Werror=switch #-Wno-psabi

OBJS_LIB = sleep.o
OBJS = main.o $(OBJS_LIB)
EXE = test_unit.bin

FILES_TO_CLEAN = $(OBJS) $(EXE)

BUILDDATE = $(shell date +"%Y-%m-%d-%H-%M")



all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CFLAGS_COMMON) $(CFLAGS_CXX) -o $(EXE) $(OBJS)

main.o: $(OBJS_LIB) ../../main.cpp ../../macros.hpp
	$(CXX) -c $(CFLAGS_COMMON) $(CFLAGS_CXX) ../../main.cpp

sleep.o: $(SRC_DIR)/util/sleep.c $(SRC_DIR)/util/sleep.h
	$(CC) -c $(CFLAGS_COMMON) $(CFLAGS_CC) $(SRC_DIR)/util/sleep.c

clean:
	rm $(FILES_TO_CLEAN)

run: $(EXE)
	./$(EXE)
