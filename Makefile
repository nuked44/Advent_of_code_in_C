CC := gcc
CFLAGS := -Wall -Werror
DBG_FLAGS := -ggdb3
RELEASE_FLAGS := -o2

SRC_DIR := src
OBJ_DIR := obj
TARGET := aoc_c

.PHONY: all dbg release

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target
all: dbg

dbg: CFLAGS += $(DBG_FLAGS)
dbg: $(TARGET)

release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# Compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create target
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object and target files
clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/**/*.o $(TARGET)