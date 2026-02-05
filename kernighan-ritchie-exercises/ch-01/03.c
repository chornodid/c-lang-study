/*
 * Exercise 1-3: Modify the temperature conversion program to print a heading
 * above the table.
 */

#include <stdio.h>

float f_to_c(float fahr) {
  return (5.0/9.0) * (fahr - 32.0);
}

int main(void) {
  static float lower = 0.0;
  static float upper = 300.0;
  static float step = 20.0;

  typedef struct {
    char *ref;
    float fahr;
  } ref_temp_t;
  static ref_temp_t ref_temps[6] = {
    { .ref = "Water freezing point", .fahr = 32.0 },
    { .ref = "Water boiling point", .fahr = 212.0 },
    { .ref = "Normal body temperature", .fahr = 98.6 },
    { .ref = "Lowest temperature on Earth (Antarctica)", .fahr = -128.6 },
    { .ref = "Highest temperature on Earth (Death Valley)", .fahr = 134.0 },
    { .ref = "Where F and C are equal", .fahr = -40.0 },
  };

  printf("Fahrenheit to Celsius conversion table:\n");
  printf("%-6s | %-6s\n", "F", "C");
  printf("---------------\n");
  for (float fahr = lower; fahr <= upper; fahr = fahr + step) {
    printf("%6.1f | %6.1f\n", fahr, f_to_c(fahr));
  }
  printf("---------------\n");

  printf("\n");
  printf("Reference temperatures:\n");
  printf("%-6s | %-6s | Reference\n", "F", "C");
  printf("-------------------------\n");
  for (size_t index = 0; index < sizeof(ref_temps)/sizeof(ref_temps[0]); index++ ) {
    ref_temp_t ref_temp = ref_temps[index];
    printf(
      "%6.1f | %6.1f | %s\n", 
      ref_temp.fahr, 
      f_to_c(ref_temp.fahr),
      ref_temp.ref
    );
  }
  printf("-------------------------\n");
  return 0;
}
