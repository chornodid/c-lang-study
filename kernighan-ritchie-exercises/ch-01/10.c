/*
 * Exercise 1-10: Write a program to copy its input to its output, replacing
 * each tab by \t, each backspace by \b, and each backslash by \\.
 */

#include <stdio.h>

int main(void) {
  int c;

  while ((c = getchar()) != EOF)
    if (c == '\b') {
      printf("\\b");
    } else if (c == '\t') {
      printf("\\t");
    } else if (c == '\\') {
      printf("\\\\");
    } else {
      putchar(c);
    }

  return 0;
}

