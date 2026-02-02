# Declaration Follows Use

A design principle behind C's declaration syntax. A declaration shows how
you *use* the variable to get the base type.

## Basic Examples

```c
int x;        /* x is an int */
int *p;       /* *p is an int (dereference p to get int) */
int a[10];    /* a[i] is an int (index a to get int) */
int *a[10];   /* *a[i] is an int (a is array of pointers) */
int (*a)[10]; /* (*a)[i] is an int (a is pointer to array) */
int *f();     /* *f() is an int (call f, dereference result) */
int (*f)();   /* (*f)() is an int (f is function pointer) */
```

## The `*` Binds to the Variable

A syntactic fact about how C parses declarations:

```c
int* a, b, c;  /* MISLEADING: only a is a pointer! */
```

C parses this as:

```c
int (*a), (b), (c);  /* only a is a pointer */
```

The `*` attaches to `a`, not to `int`. To get three pointers:

```c
int *a, *b, *c;  /* each variable needs its own * */
```

This is why K&R style uses `int *p` rather than `int* p`.

## Mental Model vs C's Model

```text
Your mental model:     (int*) p      <- "p has type pointer-to-int"
C's actual model:      int (*p)     <- "dereferencing p gives int"
```

## Complex Declaration Example

```c
char (*(*x())[])()
```

Reading it using "declaration follows use":

1. `x()` - call x
2. `*x()` - dereference the result
3. `(*x())[]` - index into that
4. `*(*x())[]` - dereference that
5. `(*(*x())[])()` - call that, get a `char`

Result: "x is a function returning pointer to array of pointers to
functions returning char"

## Related K&R Exercises

- Exercise 5-18: Make `dcl` recover from input errors
- Exercise 5-19: Modify `undcl` so that it does not add redundant
  parentheses
- Exercise 5-20: Expand `dcl` to handle declarations with function
  argument types, qualifiers like `const`, etc.

## Other Languages

Most modern languages avoid this confusion with clearer syntax:

| Language | Syntax           | Reads as                 |
|----------|------------------|--------------------------|
| Go       | `var pi *int`    | "pi is pointer to int"   |
| Rust     | `pi: &i32`       | "pi is reference to i32" |
| Zig      | `pi: *i32`       | "pi is pointer to i32"   |
| Pascal   | `pi: ^Integer`   | "pi points to Integer"   |

These languages put type annotations after the name (`name: type`),
avoiding C's ambiguity.
