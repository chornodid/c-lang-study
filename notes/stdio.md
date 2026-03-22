# Standard I/O (`<stdio.h>`)

## EOF and `char` Signedness

`EOF` is defined as `-1` (an `int`). Whether a `char` can represent it
depends on the platform, since the signedness of `char` is
implementation-defined:

- **Signed `char`** (-128 to 127): `char c = EOF` stores -1, and
  `c == EOF` is true.
- **Unsigned `char`** (0 to 255): `char c = EOF` stores 255, and
  `c == EOF` is false — the comparison silently breaks.

This is why `getchar()` returns `int`, not `char`: it must represent all
valid `unsigned char` values (0–255) **plus** EOF (-1) without ambiguity.
Always use `int` to store its return value:

```c
int c;                        /* not char! */
while ((c = getchar()) != EOF)
    putchar(c);
```
