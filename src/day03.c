
// Template file for my C-solutions to the AoC 2019 challenges.

/*****************************************************************************
 * Day 03 - Crossed Wires
 * Author:  Jakob Sachs
 *****************************************************************************/

// Includes
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

/*****************************************************************************
 *                              Solutions                                    *
 *****************************************************************************/
uint64_t find_distance(const int64_t *a1, const int64_t *a2, const int64_t *b1,
                       const int64_t *b2) {
  // Check if first segment is vertical (x values are the same)
  if (a1[0] == a2[0] && b1[1] == b2[1]) {
    // A is vertical, B is horizontal
    if (a1[0] >= MIN(b1[0], b2[0]) && a1[0] <= MAX(b1[0], b2[0]) &&
        b1[1] >= MIN(a1[1], a2[1]) && b1[1] <= MAX(a1[1], a2[1])) {
      return ABS(a1[0]) + ABS(b1[1]);
    }
  } else if (a1[1] == a2[1] && b1[0] == b2[0]) {
    // A is horizontal, B is vertical
    if (a1[1] >= MIN(b1[1], b2[1]) && a1[1] <= MAX(b1[1], b2[1]) &&
        b1[0] >= MIN(a1[0], a2[0]) && b1[0] <= MAX(a1[0], a2[0])) {
      return ABS(b1[0]) + ABS(a1[1]);
    }
  }

  return INT64_MAX; // No intersection
}

void parseSegment(int64_t *x, int64_t *y, char *segment) {
  int distance = atoi(segment + 1);
  switch (segment[0]) {
  case 'U':
    *y += distance;
    break;
  case 'D':
    *y -= distance;
    break;
  case 'L':
    *x -= distance;
    break;
  case 'R':
    *x += distance;
    break;
  default:
    DBG("Invalid direction: %c\n", segment[0]);
    exit(1);
  }
}

int main() {
  // Read input
  char *input = read_file("../inputs/day03.txt");
  char *first_wire_str = input;
  char *second_wire_str = strchr(input, '\n');
  *second_wire_str = '\0';
  second_wire_str++;

  uint64_t first_len, second_len;
  char **first_segments = split_string(first_wire_str, ",", &first_len);
  char **second_segments = split_string(second_wire_str, ",", &second_len);
  assert(first_len == second_len);

  // calculate wire paths
  // wire[i][0] = x-coordinate of i-th point of wire (so wire[0] = origin + 1st
  // move)
  int64_t first_wire[first_len + 1][2];
  int64_t second_wire[first_len + 1][2];

  first_wire[0][0] = 0;
  first_wire[0][1] = 0;
  second_wire[0][0] = 0;
  second_wire[0][1] = 0;

  for (uint64_t i = 1; i < first_len + 1; i++) {
    first_wire[i][0] = first_wire[i - 1][0];
    first_wire[i][1] = first_wire[i - 1][1];

    second_wire[i][0] = second_wire[i - 1][0];
    second_wire[i][1] = second_wire[i - 1][1];

    parseSegment(&first_wire[i][0], &first_wire[i][1], first_segments[i - 1]);
    parseSegment(&second_wire[i][0], &second_wire[i][1],
                 second_segments[i - 1]);
  }

  uint64_t min_dist = UINT64_MAX;
  // iterate over all matches of segments
  for (uint64_t i = 0; i < first_len + 1; i++) {
    for (uint64_t j = 0; j < first_len + 1; j++) {
      // check if segments i & j intersect
      const int64_t *a1 = first_wire[i];
      const int64_t *a2 = first_wire[i + 1];
      const int64_t *b1 = second_wire[j];
      const int64_t *b2 = second_wire[j + 1];

      uint64_t dist = find_distance(a1, a2, b1, b2);

      if (dist <= min_dist) {
        min_dist = dist;
      }
    }
  }

  SOL("Part 1: %llu", min_dist);

  // Part 2
  uint64_t total_steps = UINT64_MAX;
  // iterate over all matches of segments
  for (uint64_t i = 0; i < first_len + 1; i++) {
    for (uint64_t j = 0; j < first_len + 1; j++) {
      // check if segments i & j intersect
      const int64_t *a1 = first_wire[i];
      const int64_t *a2 = first_wire[i + 1];
      const int64_t *b1 = second_wire[j];
      const int64_t *b2 = second_wire[j + 1];

      uint64_t dist = find_distance(a1, a2, b1, b2);
      if (dist == INT64_MAX) { // No intersection
        continue;
      }

      // compute steps to intersection
      uint64_t steps = 0;

      // we found two intersections, now
      // iterate over all segments up to current indices,
      // of both wires and sum up steps
      for (uint64_t k = 0; k < i; k++) {
        steps += atoi(first_segments[k] + 1);
      }

      for (uint64_t k = 0; k < j; k++) {
        steps += atoi(second_segments[k] + 1);
      }

      // add steps to intersection
      steps += ABS(a1[0] - b1[0]) + ABS(a1[1] - b1[1]);

      total_steps = MIN(total_steps, steps);
    }
  }

  SOL("Part 2: %llu", total_steps);

  return 0;
}
