#ifndef FIXED_H
#define FIXED_H

#include <Arduino.h>

class Fixed {
public:
  static int32_t scale;

  // envelope
  static int8_t factor(int8_t source, uint32_t numerator, uint32_t denominator) {
    uint32_t numeratorScale = numerator * scale;
    uint32_t factorScale = numeratorScale / denominator;
    int32_t resultScale = source * factorScale;
    int8_t result = resultScale / scale;

    return result;
  }

  // note
  static uint16_t factor(uint16_t source, uint16_t numerator, uint16_t denominator) {
    uint32_t numeratorScale = numerator * scale;
    uint32_t factorScale = numeratorScale / denominator;
    int32_t resultScale = source * factorScale;
    uint16_t result = resultScale / scale;

    return result;
  }

  // lfo
  static uint16_t factor(uint16_t source, uint32_t numerator, uint32_t denominator) {
    uint32_t numeratorScale = numerator * scale;
    uint32_t factorScale = numeratorScale / denominator;
    int32_t resultScale = source * factorScale;
    uint16_t result = resultScale / scale;

    return result;
  }
};

int32_t Fixed::scale = 1e4;

#endif
