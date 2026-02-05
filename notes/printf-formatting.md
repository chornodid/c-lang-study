# printf Formatting

The `printf` family of functions formats and prints output using format
specifiers.

## Basic Syntax

```c
printf("format string", arg1, arg2, ...);
```

Format specifiers start with `%` and specify how to format arguments.

## Common Format Specifiers

| Specifier | Type | Example Output |
|-----------|------|----------------|
| `%d` | int (decimal) | `42` |
| `%i` | int (decimal) | `42` |
| `%u` | unsigned int | `42` |
| `%x` | unsigned int (hex lowercase) | `2a` |
| `%X` | unsigned int (hex uppercase) | `2A` |
| `%o` | unsigned int (octal) | `52` |
| `%f` | double (fixed-point) | `3.140000` |
| `%e` | double (scientific, lowercase) | `3.140000e+00` |
| `%E` | double (scientific, uppercase) | `3.140000E+00` |
| `%g` | double (shortest format) | `3.14` |
| `%c` | char | `A` |
| `%s` | string (char \*) | `hello` |
| `%p` | pointer address | `0x7ffd5e8a9b40` |
| `%%` | literal % | `%` |

### Examples

```c
int x = 42;
printf("%d\n", x);              /* 42 */
printf("%i\n", x);              /* 42 */
printf("%u\n", x);              /* 42 */
printf("%x\n", x);              /* 2a */
printf("%X\n", x);              /* 2A */
printf("%o\n", x);              /* 52 */

double pi = 3.14159;
printf("%f\n", pi);             /* 3.141590 */
printf("%e\n", pi);             /* 3.141590e+00 */
printf("%g\n", pi);             /* 3.14159 */

char c = 'A';
printf("%c\n", c);              /* A */

char *str = "hello";
printf("%s\n", str);            /* hello */

int *ptr = &x;
printf("%p\n", (void *)ptr);    /* 0x7ffd5e8a9b40 */

printf("%%\n");                 /* % */
```

## Width and Precision

### Width

Minimum field width (pads with spaces by default):

```c
printf("%5d\n", 42);            /*    42 (3 spaces + 42) */
printf("%5s\n", "hi");          /*    hi (3 spaces + hi) */
printf("%-5d\n", 42);           /* 42    (42 + 3 spaces, left-aligned) */
```

### Precision

For floats: number of digits after decimal point:

```c
printf("%.2f\n", 3.14159);      /* 3.14 */
printf("%.4f\n", 3.14159);      /* 3.1416 (rounded) */
printf("%6.2f\n", 3.14159);     /*   3.14 (width 6, precision 2) */
```

For strings: maximum characters to print:

```c
printf("%.3s\n", "hello");      /* hel */
printf("%8.3s\n", "hello");     /*      hel (width 8, max 3 chars) */
```

For integers: minimum digits (pads with zeros):

```c
printf("%.5d\n", 42);           /* 00042 */
```

## Flags

| Flag | Effect | Example |
|------|--------|---------|
| `-` | Left-align | `%-5d` → "42   " |
| `+` | Show sign for numbers | `%+d` → `+42` |
| ` ` | Space before positive | `% d` → " 42" |
| `0` | Pad with zeros | `%05d` → `00042` |
| `#` | Alternate form | `%#x` → `0x2a` |

### Examples

```c
printf("%-5d\n", 42);           /* "42   " (left-aligned) */
printf("%+d\n", 42);            /* +42 */
printf("%+d\n", -42);           /* -42 */
printf("% d\n", 42);            /* " 42" (space before positive) */
printf("% d\n", -42);           /* -42 (no space for negative) */
printf("%05d\n", 42);           /* 00042 */
printf("%#x\n", 42);            /* 0x2a */
printf("%#o\n", 42);            /* 052 */
printf("%#.2f\n", 3.0);         /* 3.00 (force decimal point) */
```

## Length Modifiers

Used to specify the size of integer arguments:

| Modifier | Type | Example |
|----------|------|---------|
| `hh` | char | `%hhd` |
| `h` | short | `%hd` |
| `l` | long | `%ld` |
| `ll` | long long | `%lld` |
| `z` | size_t | `%zu` |
| `t` | ptrdiff_t | `%td` |

### Examples

```c
char c = 127;
printf("%hhd\n", c);            /* 127 */

short s = 32000;
printf("%hd\n", s);             /* 32000 */

long l = 1234567890L;
printf("%ld\n", l);             /* 1234567890 */

long long ll = 9876543210LL;
printf("%lld\n", ll);           /* 9876543210 */

size_t sz = sizeof(int);
printf("%zu\n", sz);            /* 4 (or 8 on 64-bit) */
```

## Combining Width, Precision, and Flags

Format: `%[flags][width][.precision][length]specifier`

```c
printf("%+8.2f\n", 3.14159);    /*    +3.14 */
printf("%-8.2f\n", 3.14159);    /* 3.14     */
printf("%08.2f\n", 3.14159);    /* 00003.14 */
printf("%#8.2f\n", 3.14);       /*     3.14 */
```

## Dynamic Width and Precision

Use `*` to specify width/precision via arguments:

```c
int width = 8;
int precision = 2;
printf("%*.*f\n", width, precision, 3.14159);  /*     3.14 */

/* Equivalent to: */
printf("%8.2f\n", 3.14159);
```

## Related Functions

### fprintf - Print to File Stream

```c
fprintf(stderr, "Error: %s\n", "something failed");
fprintf(stdout, "Output: %d\n", 42);  /* same as printf */

FILE *fp = fopen("output.txt", "w");
fprintf(fp, "Result: %d\n", 42);
fclose(fp);
```

### sprintf - Print to String

```c
char buffer[100];
sprintf(buffer, "x = %d, y = %d", 10, 20);
/* buffer now contains "x = 10, y = 20" */
```

**WARNING:** `sprintf` doesn't check buffer size - can overflow!

### snprintf - Print to String with Size Limit (Safer)

```c
char buffer[20];
int written = snprintf(buffer, sizeof(buffer), "x = %d, y = %d", 10, 20);
/* buffer contains "x = 10, y = 20" (null-terminated) */
/* written = 13 (number of chars that would be written, excluding null) */

/* If buffer too small: */
char small[10];
int n = snprintf(small, sizeof(small), "x = %d, y = %d", 10, 20);
/* small contains "x = 10, y" (truncated, but still null-terminated) */
/* n = 13 (tells you how much space you needed) */
```

**Always use `snprintf` instead of `sprintf` for safety.**

## Common Pitfalls

### 1. Mismatched Format Specifier and Argument Type

```c
int x = 42;
printf("%f\n", x);              /* WRONG: %f expects double, not int */
printf("%d\n", (double)3.14);   /* WRONG: %d expects int, not double */

/* Correct: */
printf("%d\n", x);
printf("%f\n", 3.14);
```

### 2. Missing Arguments

```c
printf("%d %d\n", 42);          /* WRONG: missing second argument */
                                /* Undefined behavior! */
```

### 3. Wrong Length Modifier

```c
long long x = 9876543210LL;
printf("%d\n", x);              /* WRONG: truncates on 32-bit systems */
printf("%lld\n", x);            /* CORRECT */
```

### 4. Printing size_t

```c
size_t sz = sizeof(int);
printf("%d\n", sz);             /* WRONG: size_t might be unsigned long */
printf("%zu\n", sz);            /* CORRECT */
```

### 5. String Literal as Variable

```c
char *name = "Alice";
printf(name);                   /* WRONG: if name contains %, crashes */
printf("%s", name);             /* CORRECT */
```

### 6. Forgetting to Cast void Pointers

```c
int x = 42;
int *p = &x;
printf("%p\n", p);              /* Works but technically undefined */
printf("%p\n", (void *)p);      /* CORRECT */
```

## Return Value

`printf` returns the number of characters printed (excluding null terminator),
or a negative value on error:

```c
int n = printf("Hello, world!\n");
/* n = 14 (13 chars + newline) */

char buffer[50];
n = snprintf(buffer, sizeof(buffer), "x = %d", 42);
/* n = 6 (would write "x = 42" which is 6 characters) */

/* If buffer too small: */
char small[5];
n = snprintf(small, sizeof(small), "x = 42");
/* small = "x = " (truncated, null-terminated) */
/* n = 6 (tells you how many chars were NEEDED) */
```

## Summary Table: Format Specifier Components

```text
%[flags][width][.precision][length]specifier
 │      │      │           │        │
 │      │      │           │        └─ d, f, s, etc.
 │      │      │           └─────────── hh, h, l, ll, z, t
 │      │      └─────────────────────── .N (precision)
 │      └────────────────────────────── N (min width)
 └───────────────────────────────────── -, +, 0, #, space
```

## Best Practices

1. **Always match format specifiers to argument types**
2. **Use length modifiers for non-int integers** (`%ld`, `%lld`, `%zu`)
3. **Prefer `snprintf` over `sprintf`** to avoid buffer overflows
4. **Use `%p` with `(void *)` cast** for printing pointers
5. **Check return value** when you need to know output length
6. **Never use variable as format string** without `%s`
