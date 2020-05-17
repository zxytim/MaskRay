#
# $File: Makefile
# $Date: Thu Jun 27 02:56:32 2013 +0800
#
# A single output portable Makefile for
# simple c++ project

OBJ_DIR = obj
BIN_DIR = bin
TARGET = o_O

BIN_TARGET = $(BIN_DIR)/$(TARGET)

INCLUDE_DIR = -I src/include 
DEFINES = -D__DEBUG_BUILD


CXXFLAGS += -O3
#CXXFLAGS += -g -O0
#CXXFLAGS += -pg
CXXFLAGS += #$(DEFINES)
CXXFLAGS += -std=c++11
CXXFLAGS += -Wall -Wextra 
CXXFLAGS += $(INCLUDE_DIR)
CXXFLAGS += $(shell pkg-config --libs --cflags opencv4)
CXXFLAGS += -pthread
#CXXFLAGS += -lpthread
CXXFLAGS += -fopenmp

LDFLAGS = 

CXX = g++ -msse2
CXXSOURCES = $(shell find src/ -name "*.cc")
OBJS = $(addprefix $(OBJ_DIR)/,$(CXXSOURCES:.cc=.o))
DEPFILES = $(OBJS:.o=.d)

.PHONY: all clean run rebuild gdb

all: $(BIN_TARGET)

$(OBJ_DIR)/%.o: %.cc
	@echo "[cc] $< ..."
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/%.d: %.cc
	@mkdir -pv $(dir $@)
	@echo "[dep] $< ..."
	@$(CXX) $(INCLUDE_DIR) $(CXXFLAGS) -MM -MT "$(OBJ_DIR)/$(<:.cc=.o) $(OBJ_DIR)/$(<:.cc=.d)" "$<" > "$@"

sinclude $(DEPFILES)

$(BIN_TARGET): $(OBJS)
	@echo "[link] $< ..."
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(CXXFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(BIN_TARGET)
	./$(BIN_TARGET)

rebuild:
	+@make clean 
	+@make

gdb: $(BIN_TARGET)
	gdb ./$(BIN_TARGET)

show: 
	geeqie output.png
