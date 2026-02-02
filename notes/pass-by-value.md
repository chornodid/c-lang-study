# Pass by Value in C

Everything in C is passed **by value**. This includes pointers.

## Basic Pass by Value

```c
void func(int n) {
    n = 99;           /* modifies local copy only */
}

int main(void) {
    int x = 10;
    func(x);
    printf("%d\n", x); /* still 10 */
    return 0;
}
```

The function receives a copy of `x`, not `x` itself.

## Passing Pointers (Still by Value)

When you pass a pointer, the **address is copied**:

```c
void func(int *p) {
    /* p is a copy of the original pointer */
    /* both point to the same memory */
}

int main(void) {
    int x = 10;
    int *ptr = &x;
    func(ptr);        /* copies the address */
    return 0;
}
```

Visualized:

```text
main:                          func:
┌─────────┐                    ┌─────────┐
│ ptr     │───────┐     ┌──────│ p       │  (copy of address)
└─────────┘       │     │      └─────────┘
                  ▼     ▼
                ┌──────────┐
                │ x = 10   │   (same memory location)
                └──────────┘
```

## Emulating Pass by Reference

### Modifying Pointed-to Data Works

```c
void modify(int *p) {
    *p = 99;          /* modifies original x */
}

int main(void) {
    int x = 10;
    modify(&x);
    printf("%d\n", x); /* 99 */
    return 0;
}
```

This is how C emulates pass-by-reference: pass the address, dereference
to modify.

### Modifying the Pointer Itself Does NOT Work

```c
void reassign(int *p) {
    int y = 50;
    p = &y;           /* only changes local copy of pointer */
}

int main(void) {
    int x = 10;
    int *ptr = &x;
    reassign(ptr);
    printf("%d\n", *ptr); /* still 10, ptr unchanged */
    return 0;
}
```

The pointer `p` inside `func` is a copy. Reassigning it doesn't affect
`ptr` in `main`.

## Arrays Are Also Passed by Value

Arrays have special behavior when passed to functions: they **decay to
pointers**. The pointer (address) is then passed by value.

```c
void modify(int arr[], size_t len) {
    arr[0] = 99;      /* modifies original array */
}

int main(void) {
    int nums[3] = {1, 2, 3};
    modify(nums, 3);  /* nums decays to &nums[0], pointer copied */
    /* nums is now {99, 2, 3} */
    return 0;
}
```

What happens:

1. `nums` decays to a pointer to its first element (`&nums[0]`)
2. The pointer (address) is **copied by value** to `arr`
3. Both point to the same memory
4. Modifications through `arr` affect the original `nums`

This is still pass-by-value - you're passing a copy of the pointer, not
the array itself. The array never leaves `main`.

**Note:** Array parameters like `int arr[]` and `int *arr` are identical.
The array size is lost, so you must pass it separately.

For a detailed explanation of array decay and array expressions, see
[Array Expressions](array-expressions.md).

## Pointer to Pointer for Modifying Pointers

To modify the pointer itself, pass a pointer to the pointer:

```c
void reassign(int **pp) {
    static int y = 50;
    *pp = &y;         /* modifies original pointer */
}

int main(void) {
    int x = 10;
    int *ptr = &x;
    reassign(&ptr);
    printf("%d\n", *ptr); /* 50, ptr now points to y */
    return 0;
}
```

Before `reassign(&ptr)`:

```text
main:
┌─────────────┐
│ ptr = 0x100 │────────▶ ┌─────────┐
└─────────────┘          │ x = 10  │ (address 0x100)
                         └─────────┘
```

After `reassign(&ptr)`:

```text
main:                    reassign:
┌─────────────┐          ┌─────────┐
│ ptr = 0x200 │────┐     │ y = 50  │ (address 0x200, static)
└─────────────┘    │     └─────────┘
                   │          ▲
                   └──────────┘

                         ┌─────────┐
                         │ x = 10  │ (address 0x100, still exists)
                         └─────────┘
```

The variable `ptr` itself was modified:

- Was: address of `x` (e.g., `0x100`)
- Now: address of `y` (e.g., `0x200`)

Note: `y` is `static` so it survives after `reassign` returns. Without
`static`, `y` would be a local variable that disappears, leaving `ptr`
pointing to invalid memory (dangling pointer).

## Common Use Cases

### Swapping Two Values

```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int x = 1, y = 2;
swap(&x, &y);    /* x=2, y=1 */
```

### Returning Multiple Values

```c
void divide(int a, int b, int *quotient, int *remainder) {
    *quotient = a / b;
    *remainder = a % b;
}

int q, r;
divide(17, 5, &q, &r);  /* q=3, r=2 */
```

### Allocating Memory in a Function

```c
void allocate(int **pp, size_t n) {
    *pp = malloc(n * sizeof(int));
}

int *arr;
allocate(&arr, 10);    /* arr now points to allocated memory */
```

### Linked List Insertion

```c
void prepend(struct node **head, int value) {
    struct node *new = malloc(sizeof(*new));
    new->value = value;
    new->next = *head;
    *head = new;        /* modifies original head pointer */
}

struct node *list = NULL;
prepend(&list, 10);    /* list now points to new node */
```

## Summary Table

| What you pass | Can modify pointed-to data? | Can modify pointer? |
|---------------|----------------------------|---------------------|
| `int x`       | N/A                        | N/A                 |
| `int *p`      | Yes (`*p = ...`)           | No (local copy)     |
| `int **pp`    | Yes (`**pp = ...`)         | Yes (`*pp = ...`)   |

## Other Languages

| Language | Mechanism |
|----------|-----------|
| C        | Always pass by value; emulate reference with pointers |
| C++      | Pass by value or reference (`int &r`)                 |
| Java     | Primitives by value; objects by value of reference    |
| Python   | Pass by object reference (assignment rebinds name)    |
| Go       | Pass by value; use pointers for reference semantics   |
| Rust     | Move semantics by default; borrowing for references   |
