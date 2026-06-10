CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS =
SRC = src/main.c src/app.c src/translator.c src/api_client.c src/storage.c
TEST_SRC = tests/test_translation.c src/translator.c src/api_client.c src/storage.c
BIN_DIR = bin
DATA_DIR = data
TARGET = $(BIN_DIR)/app
TEST_TARGET = $(BIN_DIR)/test

ifeq ($(OS),Windows_NT)
TARGET := $(BIN_DIR)/app.exe
TEST_TARGET := $(BIN_DIR)/test.exe
LDFLAGS += -static-libgcc
endif

all: $(DATA_DIR) $(TARGET)

$(BIN_DIR):
	cmd /C "if not exist $(BIN_DIR) mkdir $(BIN_DIR)"

$(DATA_DIR):
	cmd /C "if not exist $(DATA_DIR) mkdir $(DATA_DIR)"

$(TARGET): $(BIN_DIR) $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

test: $(BIN_DIR) $(TEST_TARGET)
	$(TEST_TARGET)

$(TEST_TARGET): $(BIN_DIR) $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_TARGET) $(LDFLAGS)

clean:
	cmd /C "if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)"

.PHONY: all clean test
