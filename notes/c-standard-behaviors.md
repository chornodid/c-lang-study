# C Standard Behaviors

The C standard defines several categories of behavior to specify what
compilers and programs must, may, or cannot do.

## Defined Behavior

Behavior that is fully specified by the standard. All conforming
implementations must behave the same way.

```c
int x = 5 + 3;    /* always 8 */
```

## Implementation-Defined Behavior

Behavior that may vary between implementations, but:

- Must be consistent within an implementation
- Must be documented by the implementation

**Examples:**

| Behavior | Typical values |
|----------|----------------|
| Size of `int` | 16, 32, or 64 bits |
| Size of `long` | 32 or 64 bits |
| Signedness of `char` | Signed or unsigned |
| Right shift of negative numbers | Arithmetic or logical |
| Byte order (endianness) | Little or big endian |
| Null pointer representation | Usually all zeros |

```c
printf("%zu\n", sizeof(int));   /* implementation-defined */

char c = 255;
if (c < 0)                      /* depends on signedness of char */
    ...
```

You can write code that depends on implementation-defined behavior, but
it may not be portable.

## Unspecified Behavior

Behavior where the standard provides options, but:

- Implementation doesn't need to document the choice
- May vary between executions or even within the same program

**Examples:**

| Behavior | Issue |
|----------|-------|
| Order of evaluation of function arguments | `f(a(), b())` |
| Order of evaluation of subexpressions | `x + y * z` |
| Memory layout of function parameters | Compiler's choice |
| Interleaving of memory allocations | `malloc` behavior |

```c
int a = 1;
printf("%d %d\n", a++, a++);  /* unspecified: which a++ happens first? */

/* Could print "1 2" or "2 1" depending on evaluation order */
```

```c
f(g(), h());   /* g() might be called before or after h() */
```

## Undefined Behavior (UB)

The standard imposes **no requirements**. Anything can happen:

- Program may crash
- Program may silently corrupt data
- Program may appear to work
- Compiler may assume UB never happens and optimize accordingly

**Common causes:**

| Cause | Example |
|-------|---------|
| Array out of bounds | `arr[10]` when size is 10 |
| Null pointer dereference | `*p` when `p` is NULL |
| Signed integer overflow | `INT_MAX + 1` |
| Use after free | `free(p); *p;` |
| Uninitialized variables | `int x; printf("%d", x);` |
| Division by zero | `x / 0` |
| Modifying string literals | `char *s = "hi"; s[0] = 'H';` |
| Multiple modifications without sequence point | `i = i++` |
| Dereferencing past end of array | `*(arr + 11)` when size is 10 |

**Why UB is dangerous:**

```c
int arr[4] = {0, 1, 2, 3};
int x = arr[5];   /* UB: out of bounds */
```

Compiler may:

1. Generate code that reads garbage
2. Assume this never happens and remove related code
3. Cause unrelated code to misbehave

**Compiler optimizations assume no UB:**

```c
int f(int *p) {
    int x = *p;       /* dereference p */
    if (p == NULL)    /* compiler may remove this check! */
        return 0;     /* "p was dereferenced, so it can't be NULL" */
    return x;
}
```

## Locale-Specific Behavior

Behavior that depends on local conventions:

```c
setlocale(LC_ALL, "");
printf("%c\n", islower('ä'));  /* depends on locale */
```

## Comparison Table

| Behavior Type | Consistent? | Documented? | Portable? |
|---------------|-------------|-------------|-----------|
| Defined | Yes | By standard | Yes |
| Implementation-defined | Yes | By compiler | Maybe |
| Unspecified | No | No | No |
| Undefined | No | No | No |

## Practical Advice

1. **Avoid undefined behavior** - use tools like `-fsanitize=undefined`
2. **Know your implementation-defined behaviors** - check compiler docs
3. **Don't rely on unspecified behavior** - don't depend on evaluation
   order
4. **Use standard types for portability** - `int32_t` instead of `int`
   when size matters

## Detection Tools

| Tool | Detects |
|------|---------|
| `gcc -Wall -Wextra` | Many potential issues |
| `gcc -fsanitize=undefined` | Runtime UB detection |
| `gcc -fsanitize=address` | Memory errors |
| Valgrind | Memory errors at runtime |
| Static analyzers | Potential issues at compile time |
