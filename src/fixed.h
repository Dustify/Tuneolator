#ifndef FIXED_H
#define FIXED_H

#include <Arduino.h>

// TODO: sort overuse of 32-bit values

class Fixed {
public:
  static int32_t scale;

  // envelope
  static int8_t factorEnvelope(int8_t source, uint32_t numerator, uint32_t denominator) {
    uint32_t numeratorScale = numerator * scale;
    uint32_t factorScale = numeratorScale / denominator;
    int32_t resultScale = source * factorScale;
    int8_t result = resultScale / scale;

    return result;
  }

  // velocity / sustain
  static int8_t factorVelocity(int8_t source, uint8_t numerator, uint8_t denominator) {
    uint32_t numeratorScale = numerator * scale;
    uint32_t factorScale = numeratorScale / denominator;
    int32_t resultScale = source * factorScale;
    int8_t result = resultScale / scale;

    return result;
  }

  // volume
  static int16_t factorVolume(int16_t source, uint8_t numerator, uint8_t denominator) {
    uint32_t numeratorScale = numerator * scale;
    uint32_t factorScale = numeratorScale / denominator;
    int32_t resultScale = source * factorScale;
    int16_t result = resultScale / scale;

    return result;
  }

  // note
  static uint16_t factorNote(uint16_t source, uint16_t numerator, uint16_t denominator) {
    uint32_t numeratorScale = numerator * scale;
    uint32_t factorScale = numeratorScale / denominator;
    int32_t resultScale = source * factorScale;
    uint16_t result = resultScale / scale;

    return result;
  }

  // lfo
  static uint16_t factorLfo(uint16_t source, uint32_t numerator, uint32_t denominator) {
    uint32_t numeratorScale = numerator * scale;
    uint32_t factorScale = numeratorScale / denominator;
    int32_t resultScale = source * factorScale;
    uint16_t result = resultScale / scale;

    return result;
  }

  // lfo volume
  static int8_t factorLfoVolume(int8_t source, uint32_t numerator, uint32_t denominator) {
    uint32_t numeratorScale = numerator * scale;
    uint32_t factorScale = numeratorScale / denominator;
    int32_t resultScale = source * factorScale;
    int8_t result = resultScale / scale;

    return result;
  }
};

int32_t Fixed::scale = 1e4;

#endif
