# Pointer Arithmetic

## Basic Operations

Pointers support a limited set of arithmetic operations:

| Operation              | Example      | Result                        |
|------------------------|--------------|-------------------------------|
| Add integer            | `p + n`      | Pointer to n-th element after |
| Subtract integer       | `p - n`      | Pointer to n-th element before|
| Subtract pointers      | `p - q`      | Number of elements between    |
| Increment              | `p++`, `++p` | Move to next element          |
| Decrement              | `p--`, `--p` | Move to previous element      |
| Comparison             | `p < q`      | Compare positions             |

## Scaling

Pointer arithmetic automatically scales by the size of the pointed-to
type:

```c
int arr[5];
int *p = arr;      /* p points to arr[0] */

p + 1              /* points to arr[1], not 1 byte ahead */
p + 2              /* points to arr[2] */
```

If `int` is 4 bytes, `p + 1` actually adds 4 bytes to the address.
The compiler handles this scaling automatically.

```c
int *p = (int *)1000;
p + 1                    /* address 1004, not 1001 */

char *c = (char *)1000;
c + 1                    /* address 1001 */
```

## Array Indexing Is Pointer Arithmetic

These are equivalent:

```c
arr[i]      /* array subscript notation */
*(arr + i)  /* pointer arithmetic notation */
```

This is why `arr[i]` and `i[arr]` both work (though the latter is
terrible style):

```c
int arr[3] = {10, 20, 30};
arr[1]     /* 20 */
1[arr]     /* 20 - same as *(1 + arr) */
```

## Pointer Subtraction

Subtracting two pointers gives the number of elements between them:

```c
int arr[10];
int *p = &arr[2];
int *q = &arr[7];

q - p      /* 5 (not 20 bytes, but 5 elements) */
p - q      /* -5 */
```

The result type is `ptrdiff_t` (defined in `<stddef.h>`), a signed
integer type.

Both pointers must point to elements of the same array (or one past
the end). Otherwise, behavior is undefined.

## One Past the End Rule

The C standard guarantees that a pointer to one element past the end
of an array is valid for arithmetic and comparisons:

```c
int arr[10];
int *end = arr + 10;   /* valid: one past the end */

for (int *p = arr; p < end; p++)  /* valid comparison */
    *p = 0;
```

What's valid:

- Computing it: `arr + 10`
- Comparing it: `p < arr + 10`
- Subtracting: `(arr + 10) - arr` yields 10

What's NOT valid:

- Dereferencing it: `*(arr + 10)` - undefined behavior
- Going further: `arr + 11` - undefined behavior

This rule exists because the idiom "iterate until one past the end"
is fundamental in C.

## Pointer Comparison

Relational operators (`<`, `>`, `<=`, `>=`) work on pointers to elements
of the same array:

```c
int arr[10];
int *p = &arr[2];
int *q = &arr[7];

p < q      /* true: p points to earlier element */
p > q      /* false */
p == q     /* false */
```

Comparing pointers to unrelated objects is undefined behavior:

```c
int a, b;
&a < &b    /* undefined behavior! */
```

Equality operators (`==`, `!=`) can compare any pointers of compatible
types, including `NULL`:

```c
int *p = NULL;
if (p == NULL)    /* valid */
    ...
```

## Void Pointers

Arithmetic on `void *` is not allowed by the standard because
`void` has no size:

```c
void *v = ...;
v + 1              /* error in strict C */
```

GCC allows it as an extension, treating `void *` like `char *`
(1-byte increments). For portable code, cast first:

```c
void *v = ...;
(char *)v + 1      /* portable */
```

## Common Patterns

### Array traversal with pointers

```c
int arr[10];
for (int *p = arr; p < arr + 10; p++)
    *p = 0;
```

### String traversal

```c
char *s = "hello";
while (*s != '\0')
    s++;
```

### Finding array length

```c
int arr[] = {1, 2, 3, 4, 5};
size_t len = sizeof(arr) / sizeof(arr[0]);
/* or with pointers to start and end: */
size_t len = (&arr)[1] - arr;  /* clever but obscure */
```

## What's NOT Allowed

- Adding two pointers: `p + q` - meaningless
- Multiplying/dividing pointers: `p * 2`, `p / 2` - meaningless
- Arithmetic on pointers to different arrays - undefined behavior
- Dereferencing beyond array bounds - undefined behavior
