# General Makefile
# Used for building lvm & testing
CC = gcc
BIN_DIR = bin
BUILD_DIR = build
TEST_DIR = test
OUT = $(BUILD_DIR)/lvm

STD = -std=gnu23
WARN = -Wall -Wextra -Werror \
       -Wshadow -Wstrict-aliasing=2 -Wpointer-arith -Wcast-align=strict \
       -Wundef -Warray-bounds=2 -Wstringop-overflow=4 -Wformat=2 \
       -Wconversion -Wsign-conversion -Wswitch-default -Wswitch-enum \
       -Wmissing-prototypes -Wimplicit-fallthrough=5

INCLUDE = -Iabi/include -Iinclude

# Optimization configurations
OPT_NORMAL = -O2 -g -MMD -MP
OPT_MAX = -O3 -s -flto -MMD -MP

# --- AUTOMATIC MODE SELECTION ---
mode ?= normal

ifeq ($(mode), release)
    OPT = $(OPT_MAX)
    LTO_FLAG = -flto
else
    OPT = $(OPT_NORMAL)
    LTO_FLAG =
endif

TARGET ?= X64

ifeq ($(TARGET), X64)
    ARCH = -march=x86-64-v3
else ifeq ($(TARGET), ARM)
    ARCH = -march=armv8-a
endif

# Combine flags cleanly
CFLAGS = $(STD) $(ARCH) $(WARN) $(INCLUDE) $(OPT) $(LTO_FLAG)
LDFLAGS = -lm $(LTO_FLAG)

# Source and Object discovery
SRCS = $(wildcard src/*.c) $(wildcard abi/src/*.c)
MAIN_SRC = $(wildcard *.c) # Isolates main.c if present at root

# Core objects (everything EXCEPT the root main file, if you have one, to avoid double main symbols in tests)
CORE_SRCS = $(SRCS)
OBJS = $(patsubst %.c, $(BIN_DIR)/%.o, $(CORE_SRCS) $(MAIN_SRC))
CORE_OBJS = $(patsubst %.c, $(BIN_DIR)/%.o, $(CORE_SRCS))

DEPS = $(OBJS:.o=.d)

# Test Suite configuration
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/$(TEST_DIR)/%, $(TEST_SRCS))

# --- Rules ---

.PHONY: all release clean test

# 1. DAILY WORKFLOW (Default): Fast compiling + debugging mode
all: $(OUT)

# 2. MAX PRODUCTION BUILD: Explicitly cleans, sets optimized variables, and builds
release:
	@$(MAKE) mode=release clean
	@$(MAKE) mode=release $(OUT)

# Linking core executable
$(OUT): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compilation step for source files
$(BIN_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Test Suite Rules ---

# Compiles test binaries cleanly inside bin/test/ linked against core object files
$(BIN_DIR)/$(TEST_DIR)/%: $(TEST_DIR)/%.c $(CORE_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(CORE_OBJS) -o $@ $(LDFLAGS)

# Main test runner execution target
test: $(TEST_BINS)
	@echo "-----------------------------------"
	@echo "Running Test Suite..."
	@echo "-----------------------------------"
	@for bin in $(TEST_BINS); do \
		echo "Executing $$bin..."; \
		./$$bin || exit 1; \
		printf "\n------------- Passed. ----------------------\n"; \
	done
	@echo "All tests executed successfully."

# Safe cleanup
clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

# Include auto-generated dependency rules safely
-include $(DEPS)
