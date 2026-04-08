/*
 * Exercise 1-13: Write a program to print a histogram of the lengths of words
 * in its input.
 */

#include <stdio.h>

#define OUT 0
#define IN 1

int main(void) {

  int i, wlhist[10];
  for (i = 0; i < 10; ++i)
    wlhist[i] = 0;

  int c,  wl;
  int state = OUT;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == IN) {
        if (wl > 10)
          return 1;
        ++wlhist[wl - 1];
        state = OUT;
      }
    } else if (state == OUT) {
      wl = 1;
      state = IN;
    } else {
      ++wl;
    }
  }

  if (state == IN)
    ++wlhist[wl - 1];

  int j;
  for (i = 0; i < 10; ++i) {
    printf("%3d | ", (i + 1));
    for (j = 0; j < wlhist[i]; ++j)
      printf("█");
    putchar('\n');
  }

  return 0;
}

