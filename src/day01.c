
// Template file for my C-solutions to the AoC 2019 challenges.

/*****************************************************************************
 * Day 01: The Tyranny of the Rocket Equation
 * Author:  Jakob Sachs
 *****************************************************************************/

// Includes
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

/*****************************************************************************
 *                              Solutions                                    *
 *****************************************************************************/

int main() {
  char *input = read_file("../inputs/day01.txt");
  uint64_t len = 0;
  char **masses_str = split_string(input, "\n", &len);

  uint64_t *masses = malloc(len * sizeof(uint64_t));
  uint64_t fuel_needed_simple = 0;
  for (uint64_t i = 0; i < len; i++) {
    masses[i] = strtoull(masses_str[i], NULL, 10);
    // DBG("masses[%llu] = %llu\n", i, masses[i]);
    fuel_needed_simple += masses[i] / 3 - 2;
  }
  SOL("Part 1: %llu\n", fuel_needed_simple);

  uint64_t fuel_needed_true = 0;
  for (uint64_t i = 0; i < len; i++) {
    int64_t fuel = masses[i] / 3 - 2;
    while (1) {
      fuel_needed_true += fuel;
      fuel = fuel / 3 - 2;
      if (fuel <= 0) {
        break; // end on negative fuel
      }
    }
  }
  SOL("Part 2: %llu\n", fuel_needed_true);

  return 1;
}
