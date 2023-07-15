CC := gcc
CFLAGS := -Wall -Werror
DBG_FLAGS := -g3 -ggdb3 -o0
RELEASE_FLAGS := -o2

SRC_DIR := src
LIB_DIR := lib
TEST_SRC_DIR := tests
OBJ_DIR := obj
TEST_OBJ_DIR := tests/obj
TARGET := aoc_c
TEST_TARGET := tests/test

.PHONY: all dbg release test

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
LIB_SRC_FILES := $(wildcard $(LIB_DIR)/*.c)
TEST_SRC_FILES := $(wildcard $(TEST_SRC_DIR)/*.c) $(wildcard $(TEST_SRC_DIR)/**/*.c)
# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
LIB_OBJ_FILES := $(patsubst $(LIB_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIB_SRC_FILES))
TEST_OBJ_FILES := $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC_FILES))

# Default target
all: dbg

dbg: CFLAGS += $(DBG_FLAGS)
dbg: $(TARGET)

release: CFLAGS += $(RELEASE_FLAGS)
release: clean
release: $(TARGET)

test: CFLAGS += $(DBG_FLAGS)
test: $(TEST_TARGET)

# Compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile library source files to object files
$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files and library object files to create target
$(TARGET): $(OBJ_FILES) $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

############################## TEST #######################

# Compile .c files to .o files
$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files and library object files to create target
$(TEST_TARGET): $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object and target files
clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/**/*.o $(TEST_OBJ_DIR)/**/*.o $(TARGET) $(TEST_TARGET)