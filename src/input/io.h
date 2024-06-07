#include <stdint.h>
#include <stdlib.h>

void readFileToBuffer(const char *filename, char **buffer, size_t *size);

void write_to_file(const char *filename, uint8_t *buffer);