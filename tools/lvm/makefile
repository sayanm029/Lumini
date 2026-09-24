CC = gcc
BUILD_DIR = build
BIN_DIR = bin
OUT = $(BIN_DIR)/lvm


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
# Default to normal. If typed 'make mode=release', it automatically upgrades.
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

SRCS = $(wildcard src/*.c) $(wildcard *.c) $(wildcard abi/src/*.c)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# --- Rules ---

.PHONY: all release clean

# 1. DAILY WORKFLOW (Default): Fast compiling + debugging mode
all: $(OUT)

# 2. MAX PRODUCTION BUILD: Explicitly cleans, sets optimized variables, and builds
release:
	@$(MAKE) mode=release clean
	@$(MAKE) mode=release $(OUT)

# Linking step
$(OUT): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compilation step (creates matching subdirectories inside build/)
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Safe cleanup
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Include auto-generated dependency rules safely
-include $(DEPS)
