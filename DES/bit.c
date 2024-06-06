#include "bit.h"

void setBit(uint64_t x, int bit)
{
    return x | (1 << bit);
}

int getBit(uint64_t x, int bit)
{
    return (x >> bit) & 1;
}
