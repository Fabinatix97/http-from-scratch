BIN_DIR := bin
SRC_DIR := src
CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c17

PROGRAMS := $(patsubst $(SRC_DIR)/%.c,%,$(wildcard $(SRC_DIR)/*.c))

.PHONY: all clean $(PROGRAMS)

all: $(PROGRAMS)

$(PROGRAMS): %: $(BIN_DIR)/%

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)
