/*
 * Exercise 1-8: Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

int main(void) {
  int nl = 0;
  int nt = 0;
  int nb = 0;
  int c;

  while ((c = getchar()) != EOF)
    if (c == '\n') {
      ++nl;
    } else if (c == '\t') {
      ++nt;
    } else if (c == ' ') {
      ++nb;
    }

  printf("Number of lines: %d\n", nl);
  printf("Number of tabs: %d\n", nt);
  printf("Number of blanks: %d\n", nb);

  return 0;
}

