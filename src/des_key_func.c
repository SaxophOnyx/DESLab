#include "des_key_func.h"

#include "des_tables.h"

void _performExtend(uint8_t *input, uint8_t *output) {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 6; ++j) {
      int newIndex = extendFuncMatrix[i][j];
      int outIndex = i * 6 + j;

      output[outIndex] = input[newIndex];
    }
  }
}

void _applyPMatrix(uint8_t *input, uint8_t *output) {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 4; ++j) {
      int newIndex = pMatrix[i][j];
      int outIndex = i * 4 + j;

      output[outIndex] = input[newIndex];
    }
  }
}

void _writeBinaryToOutput(uint8_t *output, int value, int offset) {
  switch (value) {
  case 0:
    output[offset + 0] = 0;
    output[offset + 1] = 0;
    output[offset + 2] = 0;
    output[offset + 3] = 0;
    break;

  case 1:
    output[offset + 0] = 0;
    output[offset + 1] = 0;
    output[offset + 2] = 0;
    output[offset + 3] = 1;
    break;

  case 2:
    output[offset + 0] = 0;
    output[offset + 1] = 0;
    output[offset + 2] = 1;
    output[offset + 3] = 0;
    break;

  case 3:
    output[offset + 0] = 0;
    output[offset + 1] = 0;
    output[offset + 2] = 1;
    output[offset + 3] = 1;
    break;

  case 4:
    output[offset + 0] = 0;
    output[offset + 1] = 1;
    output[offset + 2] = 0;
    output[offset + 3] = 0;
    break;

  case 5:
    output[offset + 0] = 0;
    output[offset + 1] = 1;
    output[offset + 2] = 0;
    output[offset + 3] = 1;
    break;

  case 6:
    output[offset + 0] = 0;
    output[offset + 1] = 1;
    output[offset + 2] = 1;
    output[offset + 3] = 0;
    break;

  case 7:
    output[offset + 0] = 0;
    output[offset + 1] = 1;
    output[offset + 2] = 1;
    output[offset + 3] = 1;
    break;

  case 8:
    output[offset + 0] = 1;
    output[offset + 1] = 0;
    output[offset + 2] = 0;
    output[offset + 3] = 0;
    break;

  case 9:
    output[offset + 0] = 1;
    output[offset + 1] = 0;
    output[offset + 2] = 0;
    output[offset + 3] = 1;
    break;

  case 10:
    output[offset + 0] = 1;
    output[offset + 1] = 0;
    output[offset + 2] = 1;
    output[offset + 3] = 0;
    break;

  case 11:
    output[offset + 0] = 1;
    output[offset + 1] = 0;
    output[offset + 2] = 1;
    output[offset + 3] = 1;
    break;

  case 12:
    output[offset + 0] = 1;
    output[offset + 1] = 1;
    output[offset + 2] = 0;
    output[offset + 3] = 0;
    break;

  case 13:
    output[offset + 0] = 1;
    output[offset + 1] = 1;
    output[offset + 2] = 0;
    output[offset + 3] = 1;
    break;

  case 14:
    output[offset + 0] = 1;
    output[offset + 1] = 1;
    output[offset + 2] = 1;
    output[offset + 3] = 0;
    break;

  case 15:
    output[offset + 0] = 1;
    output[offset + 1] = 1;
    output[offset + 2] = 1;
    output[offset + 3] = 1;
    break;
  }
}

void keyFunc(uint8_t *right, uint8_t *key, uint8_t *output) {
  uint8_t extendedBuffer[48] = {0};
  uint8_t outputBuffer[32] = {0};

  _performExtend(right, extendedBuffer);

  for (int i = 0; i < 48; ++i) {
    extendedBuffer[i] = extendedBuffer[i] ^ key[i];
  }

  for (int i = 0; i < 8; ++i) {
    int start = i * 6;

    int row = (extendedBuffer[start] << 1) + extendedBuffer[start + 5];

    int column = 0;
    for (int j = 0; j < 4; ++j) {
      column = column << 1;
      column += extendedBuffer[start + j];
    }

    int sValue = sMatrices[i][row][column];
    _writeBinaryToOutput(outputBuffer, sValue, 4 * i);
  }

  _applyPMatrix(outputBuffer, output);
}