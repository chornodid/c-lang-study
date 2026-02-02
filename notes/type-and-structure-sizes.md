# Type and Structure Sizes

## Standard Type Sizes Are Not Fixed

The C standard only guarantees minimum sizes:

| Type        | Minimum | Typical 32-bit | Typical 64-bit |
|-------------|---------|----------------|----------------|
| `char`      | 8 bits  | 8 bits         | 8 bits         |
| `short`     | 16 bits | 16 bits        | 16 bits        |
| `int`       | 16 bits | 32 bits        | 32 bits        |
| `long`      | 32 bits | 32 bits        | 32 or 64 bits  |
| `long long` | 64 bits | 64 bits        | 64 bits        |

## Factors Affecting Type/Structure Sizes

### C Standard

- Sets minimum sizes, not exact sizes
- Different standards introduce new types (`long long` in C99)

### CPU Architecture

- Word size (16/32/64-bit) influences natural type sizes
- Alignment requirements vary

### OS / ABI (Application Binary Interface)

Defines the data model:

| Model | int | long | pointer | Used by                |
|-------|-----|------|---------|------------------------|
| ILP32 | 32  | 32   | 32      | 32-bit Linux/Windows   |
| LLP64 | 32  | 32   | 64      | 64-bit Windows         |
| LP64  | 32  | 64   | 64      | 64-bit Linux/macOS     |

This is why `long` is 32 bits on Windows 64-bit but 64 bits on
Linux 64-bit.

### Compiler

- Different compilers may choose different defaults
- Compiler flags: `-m32`/`-m64`
- Packing directives: `#pragma pack`, `__attribute__((packed))`

## Structure Padding and Alignment

Most processors require data types to be aligned to addresses divisible
by their size:

```c
struct {
    char c;   /* 1 byte at offset 0 */
    int i;    /* 4 bytes - must start at offset 4, not 1 */
};
```

The compiler inserts 3 bytes of padding (the "hole") after `c`:

```text
Offset:  0       1   2   3       4   5   6   7
         [char]  [  hole  ]      [    int    ]
```

Total: 8 bytes, not 5.

### Member Order Matters

```c
struct inefficient {   /* likely 12 bytes */
    char a;            /* 1 + 3 padding */
    int b;             /* 4 */
    char c;            /* 1 + 3 padding */
};

struct efficient {     /* likely 8 bytes */
    int b;             /* 4 */
    char a;            /* 1 */
    char c;            /* 1 + 2 padding */
};
```

### Compilers Cannot Reorder Members

The C standard requires struct members to be laid out in declaration
order. You must optimize manually.

Use `-Wpadded` with GCC to get warnings about padding.

## Fixed-Width Types (C99+)

For portable code, use `<stdint.h>`:

```c
int8_t;    /* exactly 8 bits */
int16_t;   /* exactly 16 bits */
int32_t;   /* exactly 32 bits */
int64_t;   /* exactly 64 bits */
```

Plus unsigned versions: `uint8_t`, `uint16_t`, etc.

## sizeof Is a Compile-Time Constant

Once compiled, `sizeof` is baked into the binary as a literal number:

```c
printf("%zu\n", sizeof(struct example));  /* becomes: printf("%zu\n", 8); */
```

Exception: Variable Length Arrays (C99) have runtime `sizeof`.

## How Pointer-to-Array Types "Know" the Size

A common question: How does `int (*p)[10]` know the size is 10? After all,
a pointer is just an address.

**Answer: The size is encoded in the TYPE, not in the pointer value.**

### At Runtime: Just an Address

```c
int arr[10];
int *p1 = arr;           // Pointer to int
int (*p2)[10] = &arr;    // Pointer to array[10] of int
```

Both pointers store the **exact same address value**:

```text
Runtime Memory:
┌────────────┐
│ 0x7ffc...  │  p1 (8 bytes)
└────────────┘

┌────────────┐
│ 0x7ffc...  │  p2 (8 bytes - same value!)
└────────────┘
```

No size information is stored in the pointer itself!

### At Compile-Time: Type Metadata

The compiler tracks type information in its symbol table:

```text
Source Code:              Compiler's Type Table:
--------------            ---------------------
int arr[10];              arr → int[10]
int *p1 = arr;            p1 → int *
int (*p2)[10] = &arr;     p2 → int (*)[10]
```

When you write `p2 + 1`, the compiler:

1. Looks up the type: `int (*)[10]`
2. Calculates: "array of 10 ints = 10 × 4 = 40 bytes"
3. Generates machine code: "add 40 to the address"

The number `10` doesn't exist at runtime - it's **baked into the compiled
instructions**.

The compiler needs to know the size at compile time to generate the correct
pointer arithmetic code.

### Summary

| Aspect | Where it exists |
|--------|----------------|
| Pointer value | Runtime (8 bytes storing an address) |
| Array size in type | Compile-time only (in type system) |
| sizeof result | Compile-time (becomes a literal constant) |
| Pointer arithmetic offset | Compile-time (baked into instructions) |

The "size" in `int (*)[10]` is **type metadata** that the compiler uses to
generate correct machine code. At runtime, it's just an address like any
other pointer.

## Binary Portability Issues

Writing structs directly to files is not portable:

```c
fwrite(&p, sizeof(struct person), 1, f);  /* may break on other systems */
```

Problems:

1. Padding differs between compilers/systems
2. Endianness (little-endian vs big-endian)
3. Type sizes vary

Portable alternatives:

- Write each field explicitly
- Use text formats
- Define exact byte layouts for binary formats

## Pointer Past End of Array

The C standard guarantees a pointer to one element past the end of an
array is valid for arithmetic and comparisons:

```c
int arr[10];
for (int *p = arr; p < arr + 10; p++)  /* arr + 10 is valid */
    ...
```

Valid: comparing, computing, subtracting pointers.
Invalid: dereferencing `*(arr + 10)` or going further `arr + 11`.
