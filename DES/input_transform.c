#include "input_transform.h"

int transform(uint8_t* input, uint8_t* output, int inputLen)
{
    for (int i = 0; i < inputLen; ++i)
    {
        int mask = 256;

        for (int j = 0; j < 8; ++j)
        {
            mask = mask >> 1;
            int bit = !(!(input[i] & mask));
            output[i * 8 + j] = bit;
        }
    }
}