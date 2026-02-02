# Array Expressions in C

Understanding what array expressions mean and what they point to in local scope.

## Setup

```c
int arr[5] = {10, 20, 30, 40, 50};
```

## Expression Breakdown

| Expression | Type | Meaning | Value |
|------------|------|---------|-------|
| `arr` | `int *` (decayed) | Pointer to first element | Address (e.g., `0x100`) |
| `&arr` | `int (*)[5]` | Pointer to entire array | Same address (`0x100`) |
| `&arr[0]` | `int *` | Address of first element | Same address (`0x100`) |
| `arr[0]` | `int` | First element value | `10` |
| `*arr` | `int` | Dereference `arr` | `10` (same as `arr[0]`) |
| `arr[i]` | `int` | Element at index i | Value at that index |
| `*(arr + i)` | `int` | Equivalent to `arr[i]` | Value at that index |

## Key Insights

### `arr` vs `&arr`: Same Address, Different Types

```c
printf("%p\n", (void*)arr);   // 0x100
printf("%p\n", (void*)&arr);  // 0x100 (same address!)
```

**But they behave differently in pointer arithmetic:**

```c
arr + 1      // 0x104 (moves by sizeof(int) = 4 bytes)
&arr + 1     // 0x114 (moves by sizeof(arr) = 20 bytes)
```

- `arr` decays to `int *` → points to one `int`
- `&arr` is `int (*)[5]` → points to entire array of 5 ints

### Equivalences

```c
arr[i]  ≡  *(arr + i)    // Array indexing is pointer arithmetic
*arr    ≡  arr[0]        // Dereferencing arr gives first element
&arr[0] ≡  arr           // Address of first element equals decayed array
```

## Pointer Arithmetic Comparison

```text
Memory Layout:
    ┌─────┬─────┬─────┬─────┬─────┐
    │ 10  │ 20  │ 30  │ 40  │ 50  │
    └─────┴─────┴─────┴─────┴─────┘
    0x100 0x104 0x108 0x10c 0x110
    ↑                             ↑
    arr                         arr + 5
    &arr                        &arr + 1
```

Starting from `0x100`:

- `arr + 1` = `0x104` (moves 4 bytes)
- `arr + 2` = `0x108` (moves 8 bytes)
- `&arr + 1` = `0x114` (moves 20 bytes - entire array!)

## Common Pitfall: `*arr[0]`

```c
*arr[0]  // DANGER! Undefined behavior
```

Due to operator precedence, this means `*(arr[0])`:

- `arr[0]` evaluates to `10` (the value)
- `*10` tries to dereference 10 as a memory address
- Results in segmentation fault or garbage

**What you probably meant:**

```c
*arr     // First element (correct)
arr[0]   // First element (correct)
(*arr)   // Same as *arr (redundant parentheses but correct)
```

## Memory Visualization

```text
Stack Memory:
                  arr (when used in expressions, decays to this)
                  &arr (address of the array object itself)
                  &arr[0] (explicit address of first element)
                  ↓
    ┌──────┬──────┬──────┬──────┬──────┐
    │  10  │  20  │  30  │  40  │  50  │  <-- The actual array
    └──────┴──────┴──────┴──────┴──────┘
    0x100  0x104  0x108  0x10c  0x110

What they evaluate to:
- arr       → 0x100 (pointer to first element)
- &arr      → 0x100 (pointer to array, different type)
- arr[0]    → 10 (value)
- *arr      → 10 (value, equivalent to arr[0])
- arr + 1   → 0x104 (pointer to second element)
- &arr + 1  → 0x114 (pointer past the array)
```

## Type System Details

The type difference between `arr` and `&arr` is crucial:

```c
int arr[5];

// These have the same value but different types:
arr          // Type: int * (after decay)
&arr         // Type: int (*)[5]

// This matters for:
sizeof(arr)     // 20 bytes (size of array)
sizeof(&arr)    // 8 bytes (size of pointer to array)

// And for pointer arithmetic:
arr + 1         // Adds sizeof(int) = 4
&arr + 1        // Adds sizeof(int[5]) = 20
```

See also [Type and Structure Sizes](type-and-structure.sized.md)

## Why Array Decays to a Pointer

In most contexts, arrays automatically convert (decay) to pointers to their
first element:

**Contexts where decay happens:**

- Function arguments: `func(arr)`
- Assignments: `int *p = arr`
- Arithmetic: `arr + 1`
- Comparisons: `arr == NULL`

**Contexts where decay does NOT happen:**

- `sizeof(arr)` - gives array size, not pointer size
- `&arr` - gives pointer to array, not pointer to first element
- String initialization: `char s[] = "hello"`

## Practical Examples

### Accessing Elements

```c
int arr[5] = {10, 20, 30, 40, 50};

// All equivalent ways to access the first element:
arr[0]
*arr
*(arr + 0)
*(&arr[0])

// All equivalent ways to access the second element:
arr[1]
*(arr + 1)
1[arr]          // Yes, this works! (Not recommended)
```

### Passing to Functions

```c
void func(int *p) {
    // p is a pointer, not an array
    printf("%zu\n", sizeof(p));  // 8 (pointer size)
}

int main(void) {
    int arr[5];
    printf("%zu\n", sizeof(arr));  // 20 (array size)
    func(arr);                     // arr decays to int *
    return 0;
}
```

### Getting Array Address

```c
int arr[5];

int *p1 = arr;        // Pointer to first element
int (*p2)[5] = &arr;  // Pointer to entire array

// Same address value, different arithmetic:
p1 + 1;   // Moves 4 bytes
p2 + 1;   // Moves 20 bytes
```

## Summary

1. **`arr`** decays to a pointer to the first element in most contexts
2. **`&arr`** is a pointer to the entire array (different type, same address)
3. **`arr[i]`** and **`*(arr + i)`** are equivalent
4. **`*arr`** and **`arr[0]`** both give the first element's value
5. **`*arr[0]`** is undefined behavior (tries to dereference a value)
6. Pointer arithmetic depends on the pointer type:
   - `arr + 1` moves by `sizeof(int)`
   - `&arr + 1` moves by `sizeof(arr)`
7. Arrays are not pointers, but decay to pointers in most expressions
