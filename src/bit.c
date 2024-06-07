#include "bit.h"

void setBit(uint8_t x, int bit)
{
    //return x | (1 << bit);
}

int getBit(uint8_t x, int bit)
{
    return (x >> bit) & 1;
}
