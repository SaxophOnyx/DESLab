#pragma once

#include <stdint.h>

void setBit(uint8_t x, int bit);

int getBit(uint8_t x, int bit);

void setArrayBit(uint8_t* x, int bit);

int getArrayBit(uint8_t* x, int bit);