# Makefile defs

SRC = src
TARGET = target
OUTPUT = $(TARGET)/main

MKDIRTARGET = mkdir -p $(TARGET)

CC = g++
CC_FLAGS = -o $(OUTPUT) -std=c++20

ARGS ?=

# Commands
run: build
	echo "Running application"
	./$(OUTPUT) $(ARGS)
	
test:
	echo "Run tests for software inspection"

build: clean
	$(MKDIRTARGET)
	$(CC) $(CC_FLAGS) $(SRC)/*.cpp -lgmp

clean:
	rm -rf $(TARGET)/*
