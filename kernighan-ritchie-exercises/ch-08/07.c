/*
 * Exercise 8-7: malloc accepts a size request without checking its
 * plausibility; free believes that the block it is asked to free was allocated
 * by malloc. Improve these routines so they make more pains to verify that
 * the request is reasonable, that malloc returns a valid pointer, and that
 * free frees only valid blocks.
 */

#include <stdio.h>

int main(void) {
  fprintf(stderr, "PENDING\n");
  return 0;
}

