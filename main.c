#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_SIZE 100
#define NUM_VALUES 3

bool get_values(const char *prompt, int values[], int size);
bool validate_digits(const char input[]);

int main() {
  FILE *file;
  file = fopen("Linear_equations_algebra.txt", "w");

  if (!file) {
    perror("Failed to open file");
    return 1;
  }

  char input[BUFFER_SIZE];
  int x_values[NUM_VALUES];
  int y_values[NUM_VALUES];
  size_t i = 0, j = 0;

  if (!get_values("Enter X values", x_values, NUM_VALUES)) {
    fclose(file);
    return 1;
  }

  printf("\n");

  if (!get_values("Enter Y values", y_values, NUM_VALUES)) {
    fclose(file);
    return 1;
  }

  fprintf(file, "Values\n");

  // Display array of x values
  fprintf(file, "- X Values: ");
  printf("\nX Values: ");
  for (i = 0; i < NUM_VALUES; i++) {
    fprintf(file, "%d%s", x_values[i], i != NUM_VALUES - 1 ? ", " : "");
    printf("%d%s", x_values[i], i != NUM_VALUES - 1 ? ", " : "");
  }
  printf("\n");

  // Display array of y values
  fprintf(file, "\n- Y Values: ");
  printf("Y Values: ");
  for (j = 0; j < NUM_VALUES; j++) {
    fprintf(file, "%d%s", y_values[j], j != NUM_VALUES - 1 ? ", " : "");
    printf("%d%s", y_values[j], j != NUM_VALUES - 1 ? ", " : "");
  }
  printf("\n");

  // -------------------------------------------------------------------------
  //    Formula to find slope represented by 'm'
  //    y2 represents the second y value, y1 represents the first y value
  //
  //    y2 - y1
  //    ------- = m
  //    x2 - x1
  // -------------------------------------------------------------------------

  // Term = number (mathematical terminology)
  int y_first_term = y_values[0];
  int y_second_term = y_values[1];
  int x_first_term = x_values[0];
  int x_second_term = x_values[1];

  if (x_second_term == x_first_term) {
    printf("\nError: Division by 0\n");
    return 1;
  }

  double slope = (double)(y_second_term - y_first_term) / (x_second_term - x_first_term);
  printf("\n");
  fprintf(file, "\n\nFormula Calculations");
  fprintf(file, "\n- Slope: %.2f", slope);
  printf("Slope: %.2f", slope);

  // ------------------------
  //    Point slope formula
  //    y - y1 = m(x - x1)
  // ------------------------

  fprintf(file, "\n- Point-Slope: y - %d = %.2f(x - %d)\n", y_first_term, slope, x_first_term);
  printf("\nPoint-Slope: y - %d = %.2f(x - %d)\n", y_first_term, slope, x_first_term);

  fclose(file);

  return 0;
}

// Get values x, y
bool get_values(const char *prompt, int values[], int size)
{
  char input[BUFFER_SIZE];
  size_t i = 0;

  while (i < size) {
    printf("%s %zu: ", prompt, i + 1);
    if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
      perror("Failed reading input");
      return false;
    }
    input[strcspn(input, "\n")] = '\0';

    if (!validate_digits(input)) {
      printf("Only enter digits\n");
      continue;
    }

    values[i] = atoi(input);
    i++;
  }
  return true;
}

// Check input for only digits
bool validate_digits(const char input[]) {
  size_t length = strlen(input);

  size_t start = 0;
  if (input[0] == '-') {
    start = 1;
  }

  for (size_t i = start; i < length; i++) {
      if (!isdigit(input[i])) {
        return false;
      }
  }
  return true;
}

