# C Escape Sequences Reference

Backslash sequences used in character and string literals.

## Character Escape Sequences

| Sequence | Name | ASCII Value | Description |
|----------|------|-------------|-------------|
| `\a` | Alert (bell) | 7 | Produces a beep sound |
| `\b` | Backspace | 8 | Moves cursor back one position |
| `\f` | Form feed | 12 | Page break (rarely used) |
| `\n` | Newline | 10 | Line break |
| `\r` | Carriage return | 13 | Move cursor to start of line |
| `\t` | Horizontal tab | 9 | Tab character |
| `\v` | Vertical tab | 11 | Vertical tab (rarely used) |
| `\\` | Backslash | 92 | Literal backslash |
| `\'` | Single quote | 39 | Literal single quote |
| `\"` | Double quote | 34 | Literal double quote |
| `\?` | Question mark | 63 | Literal question mark (rarely needed) |

## Numeric Escape Sequences

### Octal

- Format: `\ooo` (1 to 3 octal digits)
- Example: `\101` = 'A' (octal 101 = decimal 65)
- Example: `\0` = null character

### Hexadecimal

- Format: `\xhh` (1 or more hex digits)
- Example: `\x41` = 'A' (hex 41 = decimal 65)
- Example: `\xFF` = 255

### Unicode (C99 and later)

- Format: `\uhhhh` (exactly 4 hex digits)
- Example: `\u0041` = 'A'
- Format: `\Uhhhhhhhh` (exactly 8 hex digits)
- Example: `\U00000041` = 'A'

## Common Examples

```c
#include <stdio.h>

int main() {
    // Newline and tab
    printf("Name\tAge\n");
    printf("John\t25\n");

    // Backslashes in file paths
    char path[] = "C:\\Users\\name\\file.txt";
    printf("%s\n", path);

    // Quotes in strings
    printf("He said \"Hello!\"\n");

    // Hex and octal
    printf("%c\n", '\x41');    // Prints 'A'
    printf("%c\n", '\101');    // Prints 'A'

    // Special characters
    printf("Alert: \a");       // Beep
    printf("First\rSecond");   // Overwrites "First" with "Second"

    return 0;
}
```

## Unrecognized Escape Sequences

When a backslash is used with a non-registered (unrecognized) symbol, the
behavior is **undefined by the C standard**. However, in practice:

### Typical Behavior

Most compilers treat unrecognized sequences by ignoring the backslash and
using the character itself:

```c
printf("\d");      // Likely prints: d
printf("\k");      // Likely prints: k
printf("\@");      // Likely prints: @
```

### Compiler Warnings

Always compile with warning flags to catch invalid escape sequences:

```bash
gcc -Wall -Wextra -pedantic
```

This produces warnings like:

```text
warning: unknown escape sequence '\d'
```

### Why This Matters

- **Portability**: Behavior may differ across compilers
- **Debugging**: Easy to accidentally use `\d` instead of `\\d`
- **Code clarity**: Invalid sequences indicate a mistake in the code

## Notes

- Escape sequences are processed at compile time, not runtime
- Not all sequences work in all contexts (some only for strings, some for
  characters)
- The `\?` sequence is rarely needed; it's only used to prevent trigraph
  sequences
- Numeric sequences can represent any character value (0-255 for char, or
  Unicode values)
