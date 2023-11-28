
// Template file for my C-solutions to the AoC 2019 challenges.

/*****************************************************************************
 * Day 02: 1202 Program Alarm
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

int run_intcode(uint64_t *instr, const uint64_t sz) {
  uint64_t idx = 0;
  bool done = false;
  while (!done) {
    if (idx >= sz) {
      DBG("skipped end!");
      return 1;
    }

    uint64_t op = instr[idx];
    uint64_t a = instr[instr[idx + 1]];
    uint64_t b = instr[instr[idx + 2]];
    uint64_t *output_addr = &instr[instr[idx + 3]];

    switch (op) {
    case 1:
      *output_addr = a + b;
      break;
    case 2:
      *output_addr = a * b;
      break;
    case 99:
      done = true;
      break;
    default:
      DBG("Unknown opcode: %llu", op);
      return 1;
    }
    idx += 4;
  }
  return 0;
}

int main() {
  // Read input
  char *input = read_file("../inputs/day02.txt");
  uint64_t sz = 0;
  char **tkns = split_string(input, ",", &sz);
  uint64_t *instr = malloc(sz * sizeof(uint64_t));

  for (uint64_t i = 0; i < sz; i++) {
    instr[i] = atoi(tkns[i]);
  }

  // backup for part 2
  uint64_t *instr_orig = malloc(sz * sizeof(uint64_t));
  memcpy(instr_orig, instr, sz * sizeof(uint64_t));

  // Part 1
  instr[1] = 12;
  instr[2] = 2;
  run_intcode(instr, sz);
  SOL("%llu", instr[0]);

  // Part 2

  // honestly just brute force this
  for (uint64_t noun = 0; noun < 100;
       noun++) { // 20 ought to be a good cutoff i hope
    for (uint64_t verb = 0; verb < 100; verb++) { // samezies
      // restore mem
      memcpy(instr, instr_orig, sz * sizeof(uint64_t));
      instr[1] = noun;
      instr[2] = verb;
      run_intcode(instr, sz);
      if (instr[0] == 19690720) {
        SOL("%llu", noun * 100 + verb);
        return 0;
      }
    }
  }

  DBG("FOUND NO SOLUTION");
  return 1;
}
