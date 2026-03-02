CC = gcc
CFLAGS = -Wall -Werror -g -std=c99
LIBS = -lSDL3 -lSDL3_image -lm
SRC_DIR = src
OBJ_DIR = obj
OUT = out

# 1. Identify all source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# 2. Define object files (e.g., src/main.c becomes obj/main.o)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Final Linking Step
$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compilation Step (Incremental)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

build: $(OUT)

run: build
	./$(OUT)

clean:
	rm -rf $(OBJ_DIR) $(OUT)

.PHONY: build run clean