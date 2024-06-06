#include "des.h"
#include "des_tables.h"
#include "des_key_func.h"
#include <stdint.h>
#include <string.h>

void _performIP(uint8_t* input, uint8_t* output)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            int newIndex = ipMatrix[i][j];
            int outIndex = i * 8 + j;

            output[outIndex] = input[newIndex];
        }
    }
}

void _performInvP(uint8_t* input, uint8_t* output)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            int newIndex = invIpMatrix[i][j];
            int outIndex = i * 8 + j;

            output[outIndex] = input[newIndex];
        }
    }
}

int encrypt(uint8_t* input, uint8_t* key, uint8_t* output)
{
    uint8_t outputBuffer[64] = { 0 };
    uint8_t keyFuncBuffer[32] = { 0 };
    uint8_t sideBuffer[32] = { 0 };

    _performIP(input, outputBuffer);

    for (int i = 0; i < 16; ++i)
    {
        memcpy(sideBuffer, outputBuffer, 32 * sizeof(uint8_t));
        memcpy(outputBuffer, outputBuffer + 32, 32 * sizeof(uint8_t));

        keyFunc(outputBuffer + 32, key, keyFuncBuffer);

        for (int i = 0; i < 32; ++i)
        {
            sideBuffer[i] = sideBuffer[i] ^ keyFuncBuffer[i];
        }

        memcpy(outputBuffer + 32, sideBuffer, 32 * sizeof(uint8_t));
    }

    _performInvP(outputBuffer, output);

    return 0;
}

// TODO(SaxophOnyx): Implement
int decrypt(uint8_t* input, uint8_t* key, uint8_t* output)
{
    uint8_t outputBuffer[64] = { 0 };
    uint8_t keyFuncBuffer[32] = { 0 };
    uint8_t sideBuffer[32] = { 0 };

    _performInvP(input, outputBuffer);

    for (int i = 0; i < 16; ++i)
    {
        memcpy(sideBuffer, outputBuffer + 32, 32 * sizeof(uint8_t));
        memcpy(outputBuffer + 32, outputBuffer, 32 * sizeof(uint8_t));
    }

    _performIP(outputBuffer, output);

    return 0;
}