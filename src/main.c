#include <stdio.h>

#include "des.h"
#include "input_transform.h"

void printArray(uint8_t* arr, int len)
{
    for (int i = 0; i < len; ++i)
    {
        printf("%d  ", arr[i]);
    }
}

void printBitArray(uint8_t* arr, int len)
{
    for (int i = 0; i < len; ++i)
    {      
        if (i != 0 && i % 8 == 0)
        {
            printf("\n%d  ", arr[i]);
        }
        else
        {
            printf("%d  ", arr[i]);
        }
    }
}

int main()
{
    uint8_t rawInput[8] = {'z', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    uint8_t rawKey[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    uint8_t input[64] = { 0 };
    uint8_t encoded[64] = { 0 };
    uint8_t decoded[64] = { 0 };
    uint8_t key[56] = { 0 };

    transform(rawInput, input, 8);
    transform(rawKey, key, 7);

    encrypt(input, key, encoded);
    decrypt(encoded, key, decoded);

    /*
    printBitArray(input, 64);
    printf("\n");
    printf("\n");
    printBitArray(key, 56);
    printf("\n");
    printf("\n");
    */
    printBitArray(encoded, 64);
    printf("\n");
    printf("\n");
    printBitArray(decoded, 64);

    return 0;
}