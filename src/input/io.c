#include "io.h"

#include <stdio.h>
#include <string.h>

void readFileToBuffer(const char *filename, char **buffer, size_t *size) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  size_t blockSize = 1024; // Размер блока 1 КБ
  size_t bufferSize = blockSize;
  *buffer = (char *)malloc(bufferSize);
  if (*buffer == NULL) {
    perror("Error allocating memory");
    fclose(file);
    return;
  }

  size_t bytesRead = 0;
  *size = 0;

  while ((bytesRead = fread(*buffer + *size, 1, blockSize, file)) > 0) {
    *size += bytesRead;
    if (*size + blockSize > bufferSize) {
      bufferSize *= 2;
      char *newBuffer = (char *)realloc(*buffer, bufferSize);
      if (newBuffer == NULL) {
        perror("Error reallocating memory");
        free(*buffer);
        fclose(file);
        return;
      }
      *buffer = newBuffer;
    }
  }

  if (ferror(file)) {
    perror("Error reading file");
    free(*buffer);
    *buffer = NULL;
    *size = 0;
  }

  fclose(file);

  while (*size % 64 != 0) {
    buffer[*size] = 0;
    ++(*size);
  }
}

void write_to_file(const char *filename, uint8_t *buffer) {}