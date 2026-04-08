/*
 * Exercise 1-14: Write a program to print a histogram of the frequencies of
 * different characters in its input.
 */

#include <stdio.h>

int main(void) {
  int i, cfhist[256];
  for (i = 0; i < 256; ++i)
    cfhist[i] = 0;

  int c;
  while ((c = getchar()) != EOF)
    ++cfhist[c];

  int cf, j;
  for (i = 0; i < 256; ++i) {
    cf = cfhist[i];
    if (cf > 0) {
      if (i >= ' ' && i <= '~')
        printf("   %c | ", i);
      else
        printf("0x%02x | ", i);
      for (j = 0; j < cf; ++j)
        printf("█");
      putchar('\n');
    }
  }

  return 0;
}

