CC = gcc
DEBUG = -g -fsanitize=address
CFLAGS = -Wall -Wpedantic -Wextra -Wconversion $(DEBUG)
LDFLAGS = $(DEBUG)
LIBS = -l raylib -l m

SRC_DIR = ./src
INCLUDE_DIR = ./include
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
INCLUDES = $(wildcard $(INCLUDE_DIR)/*.h)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

main: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) $< -o $@

.PHONY: clean
clean:
	rm -rf build/*.o

all:
	rm -f main