// Created by: Jakob Sachs

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros and constants
#define DBG(...)                                                               \
  do {                                                                         \
    fprintf(stderr, "\x1B[31m[Dbg]\t");                                        \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\x1B[0m\n");                                              \
  } while (0)

#define SOL(...)                                                               \
  do {                                                                         \
    fprintf(stderr, "\e[1;34m[Solution]\t");                                   \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\x1B[0m\n");                                              \
  } while (0)

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define ABS(a) ((a) < 0 ? -(a) : (a))

// Nice to have functions

char *read_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    DBG("Could not open file %s\n", filename);
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  uint64_t size = ftell(file);
  rewind(file);
  char *buffer = malloc(size + 1);
  fread(buffer, size, 1, file);
  fclose(file);
  buffer[size] = '\0';
  return buffer;
}

char **split_string(char *string, const char *delimiter, uint64_t *size) {
  uint64_t initial_cap = 10;
  char **tokens = malloc(initial_cap * sizeof(char *));

  *size = 0;
  char *token = strtok(string, delimiter);
  while (token != NULL) {
    if (*size >= initial_cap) {
      initial_cap *= 2;
      tokens = realloc(tokens, initial_cap * sizeof(char *));
    }
    tokens[*size] = token;
    (*size)++;
    token = strtok(NULL, delimiter);
  }

  return tokens;
}
