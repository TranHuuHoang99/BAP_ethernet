# Simple Makefile to build libPDU_MultiPlex (.so on Linux, .dll on Windows/MinGW)

CXX ?= g++
CXXFLAGS ?= -O2 -fPIC -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS ?=
SRC_DIR := src
OBJ_DIR := build

# ---------------------------------------------------------------------------
# Platform detection: on Windows (MinGW/MSYS2) produce a DLL and link the
# winsock + IP helper libraries; on POSIX produce a shared object.
# ---------------------------------------------------------------------------
ifeq ($(OS),Windows_NT)
    LIB_NAME := libPDU_MultiPlex.dll
    PLATFORM_LDLIBS := -lws2_32 -liphlpapi
else
    LIB_NAME := libPDU_MultiPlex.so
    PLATFORM_LDLIBS :=
endif

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean dirs

all: dirs $(LIB_NAME)

.PHONY: test test-clean
test:
	$(MAKE) -C ../test/libPDU_MultiPlex
test-clean:
	$(MAKE) -C ../test/libPDU_MultiPlex clean

$(LIB_NAME): $(OBJS)
	$(CXX) -shared -o $@ $^ $(LDFLAGS) $(PLATFORM_LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

dirs:
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(LIB_NAME)
