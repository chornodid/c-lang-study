# IEEE 754 Floating-Point Standard

IEEE 754 defines how floating-point numbers are represented and
manipulated in binary. C's `float`, `double`, and `long double` follow
this standard on virtually all modern systems.

## Representation

A floating-point number is stored as three components:

```text
[sign] [exponent] [mantissa/significand]
```

| Type     | Sign | Exponent | Mantissa | Total   |
|----------|------|----------|----------|---------|
| `float`  | 1    | 8 bits   | 23 bits  | 32 bits |
| `double` | 1    | 11 bits  | 52 bits  | 64 bits |

## Precision

| Type     | Decimal digits | Smallest positive normal |
|----------|----------------|--------------------------|
| `float`  | ~7             | ~1.2 * 10^-38            |
| `double` | ~15-16         | ~2.2 * 10^-308           |

## Special Values

| Value       | Meaning                        | Example          |
|-------------|--------------------------------|------------------|
| `+Inf`      | Positive infinity              | `1.0 / 0.0`     |
| `-Inf`      | Negative infinity              | `-1.0 / 0.0`    |
| `NaN`       | Not a number (invalid result)  | `0.0 / 0.0`     |
| `+0` / `-0` | Positive and negative zero     | `-1.0 * 0.0`    |

```c
printf("%f\n", 1.0 / 0.0);    /* inf */
printf("%f\n", 0.0 / 0.0);    /* -nan */
printf("%d\n", 0.0 == -0.0);  /* 1 — positive and negative zero
                                  compare equal */
```

## Rounding Rules

When a result can't be represented exactly, IEEE 754 defines rounding
modes:

- **Round to nearest, ties to even** (default) — rounds to the nearest
  representable value; if exactly halfway, rounds to the value with an
  even least significant bit
- **Round toward zero** — truncates
- **Round toward +infinity** — rounds up
- **Round toward -infinity** — rounds down

## Exceptions

| Exception         | Trigger                   | Default result |
|-------------------|---------------------------|----------------|
| Division by zero  | `1.0 / 0.0`              | +/-Inf         |
| Invalid operation | `0.0 / 0.0`, `sqrt(-1)`  | NaN            |
| Overflow          | Result too large          | +/-Inf         |
| Underflow         | Result too close to zero  | +/-0 or denorm |

## NaN Behavior

NaN has unusual comparison semantics — it is not equal to anything,
including itself:

```c
double x = 0.0 / 0.0;
printf("%d\n", x == x);     /* 0 — NaN != NaN */
printf("%d\n", x != x);     /* 1 — this is how you detect NaN */
```

C99 provides `isnan()` in `<math.h>` for this purpose.

## Floats Are Not Real Numbers

Floating-point numbers are a finite subset of rational numbers, not
the continuous real number line. There are gaps between every two
adjacent representable values.

The gaps are **not uniform** — they grow with magnitude. For example,
adjacent `float` values near 0.1 (the gap is ~7.5 * 10^-9):

```text
0.09999997913837432861
0.09999998658895492554
0.09999999403953552246
0.10000000149011611938  <-- closest float to 0.1
0.10000000894069671631
0.10000001639127731323
0.10000002384185791016
```

Notice that 0.1 itself is not representable — the nearest `float` is
off by ~1.5 * 10^-9.

The mantissa
has a fixed number of bits, so as the exponent increases, each bit
represents a larger value:

- Near 1.0, the gap between adjacent `float` values is ~10^-7
- Near 10^6, the gap is ~0.06

This means there's a threshold beyond which consecutive integers can
no longer be represented. The mantissa runs out of bits:

| Type     | Max exact integer | Threshold |
|----------|-------------------|-----------|
| `float`  | 16,777,216        | 2^24      |
| `double` | 9,007,199,254,740,992 | 2^53  |

```c
float f = 16777216.0f;
printf("%f\n", f);       /* 16777216.000000 */
printf("%f\n", f + 1);   /* 16777216.000000 — can't distinguish! */
```

## Practical Impact in C

- `float` arithmetic can produce slightly different results than
  `double` due to precision differences
- Comparing floating-point values with `==` is unreliable for computed
  results — use a tolerance instead
- Integer-to-float conversion can lose precision for large values
  (a 32-bit `int` has more precision than a `float` for values > 2^24)
