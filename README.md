# C Language Study

A structured study of C programming through exercises from *The C Programming
Language, second edition* (K&R) with automated compilation and testing
infrastructure.

## Features

- Exercise solutions organized by chapter
- Parallel compilation with smart caching (recompiles the source file if
  changed)
- Student-friendly compilation flags
- Tests for exercises with automated runner
- Additional notes on C language concepts

## Prerequisites

- GCC compiler with C99 support
- Ruby 2.7+ (for build and test scripts)

## Directory Structure

```text
c-lang-study/
├── kernighan-ritchie-exercises/
│   ├── ch-01/              # Chapter 1 exercises
│   ├── ch-02/              # Chapter 2 exercises
│   ├── compiled/           # Build artifacts (gitignored!)
│   └── tests/              # Test cases
├── notes/                  # notes on C language concepts
├── compile-exercises       # Compilation script
├── test-exercises          # Test runner script
└── README.md
```

## Usage

### Compiling Exercises

Compile all exercises (in parallel):

```bash
./compile-exercises
```

After you changed a source file, just run it again and the script picks up
what needs to be recompiled.

Force recompilation of everything:

```bash
./compile-exercises --force
./compile-exercises -f
```

When compilation flags (see below) are changed, all files
are forced-recompiled too.

### Running Tests

Run all tests:

```bash
./test-exercises
```

Verbose mode, show source files pending tests

```bash
./test-exercises --pending
./test-exercises -p
```

### Compilation Flags

Exercises are compiled with strict standards for learning purposes:

- `-std=c99` - C99 standard since the book is written at that time
- `-Wall -Wextra -pedantic` - Comprehensive warnings
- `-g` - Debug information
- `-fsanitize=address` - Memory error detection
- `-fsanitize=undefined` - Undefined behavior detection

See `compile-exercises` for the full configuration.

## Test Format

Tests use a simple text-based format with sections:

```text
[ARGS]
arg1 arg2

[STDIN]
input data here

[EXPECTED]
expected output here
```

ARGS and STDIN sections are optional, depending on the exercise requirements.

## Notes

The `notes/` directory contains my notes on C concepts that are either not
covered by the K&R book or require deeper exploration.

- [pass-by-value](notes/pass-by-value.md) - Pass-by-value semantics and pointer usage
- [array-expressions](notes/array-expressions.md) - Array decay and array expressions
- [type-and-structure-sizes](notes/type-and-structure-sizes.md) - Type sizes
  and memory layout
