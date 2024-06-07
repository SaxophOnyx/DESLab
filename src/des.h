#pragma once

#include <stdint.h>

int encrypt(uint8_t* input, uint8_t* key, uint8_t* output);

int decrypt(uint8_t* input, uint8_t* key, uint8_t* output);
