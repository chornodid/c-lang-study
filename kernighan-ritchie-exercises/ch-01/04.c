/*
 * Exercise 1-4: Write a program to print the corresponding Celsius to 
 * Fahrenheit table.
 */

#include <stdio.h>

float c_to_f(float celsius) {
  return (9.0/5.0) * celsius + 32.0;
}

int main(void) {
  static float lower = 0.0;
  static float upper = 300.0;
  static float step = 20.0;

  typedef struct {
    char *ref;
    float celsius;
  } ref_temp_t;
  static ref_temp_t ref_temps[6] = {
    { .ref = "Water freezing point", .celsius = 0.0 },
    { .ref = "Water boiling point", .celsius = 100.0 },
    { .ref = "Normal body temperature", .celsius = 37.0 },
    { .ref = "Lowest temperature on Earth (Antarctica)", .celsius = -89.2 },
    { .ref = "Highest temperature on Earth (Death Valley)", .celsius = 56.7 },
    { .ref = "Where F and C are equal", .celsius = -40.0 },
  };

  printf("Celsius to Fahrenheit conversion table:\n");
  printf("%-6s | %-6s\n", "C", "F");
  printf("---------------\n");
  for (float celsius = lower; celsius <= upper; celsius = celsius + step) {
    printf("%6.1f | %6.1f\n", celsius, c_to_f(celsius));
  }
  printf("---------------\n");

  printf("\n");
  printf("Reference temperatures:\n");
  printf("%-6s | %-6s | Reference\n", "C", "F");
  printf("-------------------------\n");
  for (size_t index = 0; index < sizeof(ref_temps)/sizeof(ref_temps[0]); index++ ) {
    ref_temp_t ref_temp = ref_temps[index];
    printf(
      "%6.1f | %6.1f | %s\n", 
      ref_temp.celsius, 
      c_to_f(ref_temp.celsius),
      ref_temp.ref
    );
  }
  printf("-------------------------\n");
  return 0;
}

