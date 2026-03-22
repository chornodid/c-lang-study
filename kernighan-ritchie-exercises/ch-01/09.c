/*
 * Exercise 1-9: Write a program to copy its input to its output, replacing
 * each string of one or more blanks by a single blank.
 */

#include <stdio.h>

int main(void) {
  int c, prev_c = 0;

  while ((c = getchar()) != EOF) {
    if (c != ' ' || prev_c != ' ') {
      putchar(c);
    }
    prev_c = c;
  }

  return 0;
}

