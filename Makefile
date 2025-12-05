# Wordlang Makefile
# Modular build system

CC = gcc
CFLAGS = -Wall -O2 -I. -Isrc
LDFLAGS = -lm

# Directories
SRC_DIR = src
LIB_DIR = lib/core

# Source files
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/globals.c \
          $(SRC_DIR)/utils.c \
          $(SRC_DIR)/tokenizer.c \
          $(SRC_DIR)/parser.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Output
TARGET = wordlang

# Header dependencies
HEADERS = $(SRC_DIR)/types.h \
          $(SRC_DIR)/globals.h \
          $(SRC_DIR)/utils.h \
          $(SRC_DIR)/tokenizer.h \
          $(SRC_DIR)/parser.h \
          $(LIB_DIR)/core.h \
          $(LIB_DIR)/math_lib.h \
          $(LIB_DIR)/time_lib.h \
          $(LIB_DIR)/string_lib.h

# Default target
all: build

# Build the interpreter
build: $(TARGET)
	@echo "✓ Build complete: ./$(TARGET)"

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Cleaned"

# Run tests
test: build
	@echo "Running tests..."
	./$(TARGET) test.wl

# Install to /usr/local/bin
install: build
	@echo "Installing wordlang..."
	sudo cp $(TARGET) /usr/local/bin/
	@echo "✓ Installed to /usr/local/bin/wordlang"

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/wordlang
	@echo "✓ Uninstalled"

# Create a new package
new-package:
	@./wlpkg create

# List packages
list-packages:
	@./wlpkg list

# Quick rebuild (clean + build)
rebuild: clean build

# Development build with debug symbols
debug: CFLAGS += -g -DDEBUG
debug: clean build
	@echo "✓ Debug build complete"

# Show help
help:
	@echo "Wordlang Build System"
	@echo ""
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  build        - Compile the interpreter (default)"
	@echo "  clean        - Remove compiled files"
	@echo "  test         - Run test.wl"
	@echo "  install      - Install to /usr/local/bin (requires sudo)"
	@echo "  uninstall    - Remove from /usr/local/bin"
	@echo "  new-package  - Create a new Wordlang package"
	@echo "  list-packages- List all packages"
	@echo "  rebuild      - Clean and rebuild"
	@echo "  debug        - Build with debug symbols"
	@echo "  help         - Show this message"
	@echo ""
	@echo "Source Files:"
	@echo "  $(SOURCES)"

.PHONY: all build clean test install uninstall new-package list-packages rebuild debug help
