# Wordlang

A flexible programming language that uses English words OR traditional symbols - your choice!

---

## Table of Contents

- [Quick Start](#quick-start)
- [Features](#features)
- [Syntax: Words OR Symbols](#syntax-words-or-symbols)
- [Language Basics](#language-basics)
  - [Variables](#variables)
  - [Arithmetic](#arithmetic)
  - [Conditionals](#conditionals)
  - [Loops](#loops)
  - [Functions](#functions)
  - [Classes](#classes)
  - [Arrays](#arrays)
  - [Strings](#strings)
- [Core Libraries (Built-in)](#core-libraries-built-in)
  - [Math Library](#math-library)
  - [Time Library](#time-library)
  - [String Library](#string-library)
- [Import System](#import-system)
- [Package Manager (wlpkg)](#package-manager-wlpkg)
- [Standard Library (.wl files)](#standard-library-wl-files)
- [Creating Your Own Package](#creating-your-own-package)
- [Makefile Commands](#makefile-commands)
- [Project Structure](#project-structure)
- [Source Code Modules](#source-code-modules)
- [Complete Example](#complete-example)
- [Version](#version)
- [License](#license)

---

## Quick Start

```bash
# Compile
make build

# Run
./wordlang program.wl

# Run tests
make test
```

## Features

- **Dual syntax**: Use English words OR symbols (`add x y` or `x + y`)
- **Classes & methods**: OOP with `class`, `method`, `new`, and `>` operator
- **Core libraries**: Built-in math, time, and string functions
- **Import system**: Import .wl files like Python
- **Package manager**: Create and manage packages with `wlpkg`
- **Modular codebase**: Clean separation of concerns in source code

---

## Syntax: Words OR Symbols

| Operation | Words | Symbols |
|-----------|-------|---------|
| Add | `add x y`, `plus x y` | `x + y` |
| Subtract | `subtract x y`, `minus x y` | `x - y` |
| Multiply | `multiply x y`, `times x y` | `x * y` |
| Divide | `divide x y` | `x / y` |
| Modulo | `modulo x y`, `mod x y` | `x % y` |
| Power | `power x y`, `pow x y` | `x ^ y`, `x ** y` |
| Equals | `x equals y`, `x is y` | `x == y` |
| Not equals | `x not equals y` | `x != y` |
| Greater | `x greater than y` | `x > y` |
| Less | `x less than y` | `x < y` |
| Greater/equal | - | `x >= y` |
| Less/equal | - | `x <= y` |
| And | `and` | `&&` |
| Or | `or` | `\|\|` |
| Not | `not` | `!` |
| Method call | `instance > method args` | - |
| New instance | `set x to new ClassName` | - |

---

## Language Basics

### Variables
```
set x to 10
set name to "Alice"
set flag to true
```

### Arithmetic
```
set sum to x + y
set product to multiply a b
print (10 + 5) * 2
```

### Conditionals
```
# Simple if-else
if x > 10 then
    print "big"
else
    print "small"
end

# Elseif chain (use 'elseif' or 'elif')
if score >= 90 then
    print "A"
elseif score >= 80 then
    print "B"
elseif score >= 70 then
    print "C"
else
    print "F"
end

# Nested if inside else (explicit structure)
if x > 5 then
    print "x big"
else
    if y > 5 then
        print "y big"
    else
        print "both small"
    end
end

# Nested if inside method
class Checker do
    method classify with n do
        if n > 0 then
            if n > 100 then
                return 3
            elseif n > 10 then
                return 2
            else
                return 1
            end
        else
            return 0
        end
    end
end
```

### Loops
```
# While loop
while counter < 10 do
    print counter
    set counter to counter + 1
end

# For loop
for i in range 0 10 do
    print i
end

# For with step
for i in range 10 0 -1 do
    print i
end
```

### Functions
```
define square with n do
    return n * n
end

print call square 7
```

### Classes
```
# Define a class with methods
class Calculator do
    method add with a b do
        return a + b
    end
    
    method multiply with a b do
        return a * b
    end
    
    method grade with score do
        if score >= 90 then
            return 5
        elseif score >= 80 then
            return 4
        else
            return 3
        end
    end
end

# Create instance
set calc to new Calculator

# Call methods using > operator
print calc > add 10 5        # 15
print calc > multiply 7 6    # 42
print calc > grade 85        # 4
```

### Arrays
```
set nums to array 1 2 3 4 5
print nums
print get nums 0
put nums 0 to 100
append nums 6
print length nums
```

### Strings
```
set msg to "Hello"
set greeting to concat msg " World!"
print greeting
```

---

## Core Libraries (Built-in)

Core libraries are written in C and always available - no import needed.

### Math Library

| Function | Description | Example |
|----------|-------------|---------|
| `abs n` | Absolute value | `abs -5` → 5 |
| `min a b` | Minimum | `min 3 7` → 3 |
| `max a b` | Maximum | `max 3 7` → 7 |
| `sqrt n` | Square root | `sqrt 16` → 4 |
| `sign n` | Sign (-1, 0, 1) | `sign -5` → -1 |
| `gcd a b` | Greatest common divisor | `gcd 12 8` → 4 |
| `lcm a b` | Least common multiple | `lcm 3 4` → 12 |
| `factorial n` | Factorial | `factorial 5` → 120 |
| `clamp n lo hi` | Clamp value | `clamp 15 0 10` → 10 |
| `iseven n` | Is even? | `iseven 4` → 1 |
| `isodd n` | Is odd? | `isodd 5` → 1 |
| `random` | Random 0-99 | `random` → 42 |
| `randint n` | Random 0 to n-1 | `randint 100` → 73 |
| `randrange a b` | Random a to b-1 | `randrange 10 20` → 15 |

### Time Library

| Function | Description | Example |
|----------|-------------|---------|
| `hour` | Current hour (0-23) | `hour` → 14 |
| `minute` | Current minute | `minute` → 30 |
| `second` | Current second | `second` → 45 |
| `day` | Day of month | `day` → 5 |
| `month` | Month (1-12) | `month` → 12 |
| `year` | Year | `year` → 2025 |
| `weekday` | Day of week (0=Sun) | `weekday` → 5 |
| `yearday` | Day of year | `yearday` → 339 |
| `now` | Unix timestamp | `now` → 1733418600 |
| `time` | Time string "HH:MM:SS" | `print time` |
| `date` | Date string "YYYY-MM-DD" | `print date` |
| `datetime` | Full datetime string | `print datetime` |
| `sleep ms` | Sleep milliseconds | `sleep 1000` |

### String Library

| Function | Description | Example |
|----------|-------------|---------|
| `upper s` | Uppercase | `upper "hello"` → "HELLO" |
| `lower s` | Lowercase | `lower "HELLO"` → "hello" |
| `trim s` | Trim whitespace | `trim "  hi  "` → "hi" |
| `reverse s` | Reverse string | `reverse "abc"` → "cba" |
| `repeat s n` | Repeat n times | `repeat "ab" 3` → "ababab" |
| `length s` | String length | `length "hello"` → 5 |
| `contains s sub` | Contains substring? | `contains "hello" "ell"` → 1 |
| `startswith s pre` | Starts with? | `startswith "hello" "hel"` → 1 |
| `endswith s suf` | Ends with? | `endswith "hello" "lo"` → 1 |
| `indexof s sub` | Find index (-1 if not found) | `indexof "hello" "l"` → 2 |
| `charat s i` | Char at index (ASCII) | `charat "abc" 0` → 97 |
| `replace s old new` | Replace first occurrence | `replace "hello" "l" "L"` → "heLlo" |
| `isnumeric s` | Is all digits? | `isnumeric "123"` → 1 |
| `isalpha s` | Is all letters? | `isalpha "abc"` → 1 |

---

## Import System

### Importing Libraries

```
# Import standard library
import arrays
import math_extra

# Import user package
import mypackage

# Import by path
import "path/to/file.wl"
```

### Search Order

1. `packages/` directory (user packages)
2. `lib/std/` directory (standard library)
3. Current directory

---

## Package Manager (wlpkg)

```bash
# List all packages
./wlpkg list

# List standard library only
./wlpkg list std

# List core libraries
./wlpkg list core

# Create new package
./wlpkg create mypackage

# Show package info
./wlpkg info mypackage

# Remove package
./wlpkg remove mypackage

# Show help
./wlpkg help
```

---

## Standard Library (.wl files)

Standard library modules are written in Wordlang. Import them with `import <name>`.

### utils
```
import utils
call blank          # Print blank line
call between 5 1 10 # Check if value in range
```

### loops
```
import loops
call sum_range 1 10     # Sum 1+2+...+9
call countdown 5        # Print 5,4,3,2,1,Liftoff!
call print_range 0 5    # Print 0,1,2,3,4
```

### arrays
```
import arrays
set nums to array 1 2 3 4 5
call array_sum nums     # Sum all elements
call array_max nums     # Maximum element
call array_min nums     # Minimum element
call array_find nums 3  # Index of value
call array_print nums   # Print all elements
```

### math_extra
```
import math_extra
call fact 5             # Factorial
call pow 2 8            # Power
call is_prime 17        # Is prime?
call gcd 12 8           # GCD
call digit_sum 123      # Sum of digits
```

---

## Creating Your Own Package

```bash
# Create package template
./wlpkg create mylib

# Or using make
make new-package
```

This creates `packages/mylib.wl`:

```
# mylib - Wordlang Package
# Author: your_name
# Date: 2025-12-05

define mylib_hello do
    print "Hello from mylib!"
end

define mylib_add with a b do
    return a + b
end
```

Use it:
```
import mylib
call mylib_hello
print call mylib_add 5 3
```

---

## Makefile Commands

| Command | Description |
|---------|-------------|
| `make build` | Compile the interpreter |
| `make clean` | Remove compiled files |
| `make test` | Run test.wl |
| `make install` | Install to /usr/local/bin/ (requires sudo) |
| `make uninstall` | Remove from /usr/local/bin/ |
| `make new-package` | Create a new package interactively |
| `make list-packages` | List all available packages |
| `make rebuild` | Clean and rebuild |
| `make debug` | Build with debug symbols |
| `make help` | Show all available commands |

### Build Details

```bash
gcc -Wall -O2 -I. -Isrc -o wordlang src/*.c -lm
```

| Flag | Description |
|------|-------------|
| `-Wall` | Enable all warnings |
| `-O2` | Optimization level 2 |
| `-I.` | Include project root for headers |
| `-Isrc` | Include src directory for headers |
| `-o wordlang` | Output executable name |
| `-lm` | Link math library |

---

## Project Structure

```
wordlang/
├── src/                    # Source code (modular)
│   ├── main.c              # Entry point
│   ├── types.h             # Type definitions & constants
│   ├── globals.h           # Global state declarations
│   ├── globals.c           # Global state definitions
│   ├── utils.h             # Utility function declarations
│   ├── utils.c             # Utility function implementations
│   ├── tokenizer.h         # Tokenizer declarations
│   ├── tokenizer.c         # Tokenizer implementation
│   ├── parser.h            # Parser declarations
│   └── parser.c            # Parser implementation
├── lib/
│   ├── core/               # C libraries (compiled into interpreter)
│   │   ├── core.h          # Master include file
│   │   ├── math_lib.h      # Math functions
│   │   ├── time_lib.h      # Time functions
│   │   └── string_lib.h    # String functions
│   └── std/                # Standard library (.wl files)
│       ├── utils.wl
│       ├── arrays.wl
│       ├── loops.wl
│       └── math_extra.wl
├── packages/               # User packages
├── Makefile                # Build configuration
├── wlpkg                   # Package manager script
├── test.wl                 # Test file
└── README.md               # This file
```

---

## Source Code Modules

The interpreter is organized into modular files:

| File | Purpose |
|------|---------|
| `src/types.h` | All type definitions (Token, Variable, Function, etc.) and constants |
| `src/globals.h/c` | Global state variables (tokens, variables, functions, call stack) |
| `src/utils.h/c` | Helper functions (error handling, variable lookup, token helpers) |
| `src/tokenizer.h/c` | Lexical analysis - converts source code to tokens |
| `src/parser.h/c` | Parsing and execution - expressions, statements, control flow |
| `src/main.c` | Entry point - file loading and program execution |

### Module Dependencies

```
main.c
  ├── utils.h (get_directory)
  ├── tokenizer.h (tokenize)
  ├── parser.h (parse_program)
  └── globals.h (base_path)

parser.c
  ├── types.h (Token, Variable, etc.)
  ├── globals.h (tokens, variables, etc.)
  ├── utils.h (peek, advance, find_var, etc.)
  ├── tokenizer.h (tokenize_append)
  └── lib/core/core.h (wl_* functions)

tokenizer.c
  ├── types.h (TokenType)
  └── globals.h (tokens, token_count)

utils.c
  └── globals.h (all global state)
```

---

## Complete Example

```
# FizzBuzz with imports and core functions

for num in range 1 21 do
    set div3 to num % 3
    set div5 to num % 5
    
    if div3 == 0 and div5 == 0 then
        print "FizzBuzz"
    elseif div3 == 0 then
        print "Fizz"
    elseif div5 == 0 then
        print "Buzz"
    else
        print num
    end
end

# Show current time
print "Finished at:"
print time
```

---

## Version

**Version**: 2.4  
**Features**: Classes & methods, modular source code, core libraries (math, time, string), import system, package manager, dual syntax, elseif support

---

## License

Open source educational project.
