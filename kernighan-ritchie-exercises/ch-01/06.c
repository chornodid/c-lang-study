/*
 * Exercise 1-6: Verify that the expression getchar() != EOF is 0 or 1.
 */

#include <stdio.h>

int main(void) {
  // write a file with a single char and redirect stdin to the file
  FILE *fp = tmpfile();
  fputc('a', fp);
  rewind(fp);
  stdin = fp;

  // try to read two char-s
  int first = (getchar() != EOF);
  int second = (getchar() != EOF);

  printf("first char is not EOF:  %d\n", first);
  printf("second char is not EOF: %d\n", second);

  fclose(fp);
  return 0;
}

