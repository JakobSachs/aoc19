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
    fprintf(stderr, "\x1B[31m[Dbg] ");                                         \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\x1B[0m");                                                \
  } while (0)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))

// Nice to have functions

void print_array(int *array, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

char *read_file(char *filename) {
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

char **split_string(char *string, char *delimiter, uint64_t *size) {
  char **result = NULL;
  char *token = strtok(string, delimiter);
  while (token != NULL) {
    result = realloc(result, (*size + 1) * sizeof(char *));
    result[*size] = token;
    (*size)++;
    token = strtok(NULL, delimiter);
  }
  return result;
}
