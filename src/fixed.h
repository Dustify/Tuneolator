#ifndef FIXED_H
#define FIXED_H

#include <Arduino.h>

// TODO: sort overuse of 32-bit values

class Fixed {
public:
  static int32 scale;

  // envelope
  static int8 factorEnvelope(int8 source, uint32 numerator, uint32 denominator) {
    uint32 numeratorScale = numerator * scale;
    uint32 factorScale = numeratorScale / denominator;
    int32 resultScale = source * factorScale;
    int8 result = resultScale / scale;

    return result;
  }

  // velocity
  static int8 factorVelocity(int8 source, uint8 numerator, uint8 denominator) {
    uint32 numeratorScale = numerator * scale;
    uint32 factorScale = numeratorScale / denominator;
    int32 resultScale = source * factorScale;
    int8 result = resultScale / scale;

    return result;
  }

  // volume
  static int16 factorVolume(int16 source, uint8 numerator, uint8 denominator) {
    uint32 numeratorScale = numerator * scale;
    uint32 factorScale = numeratorScale / denominator;
    int32 resultScale = source * factorScale;
    int16 result = resultScale / scale;

    return result;
  }

  // note
  static uint16 factorNote(uint16 source, uint16 numerator, uint16 denominator) {
    uint32 numeratorScale = numerator * scale;
    uint32 factorScale = numeratorScale / denominator;
    int32 resultScale = source * factorScale;
    uint16 result = resultScale / scale;

    return result;
  }

  // lfo
  static uint16 factorLfo(uint16 source, uint32 numerator, uint32 denominator) {
    uint32 numeratorScale = numerator * scale;
    uint32 factorScale = numeratorScale / denominator;
    int32 resultScale = source * factorScale;
    uint16 result = resultScale / scale;

    return result;
  }

  // lfo volume
  static int8 factorLfoVolume(int8 source, uint32 numerator, uint32 denominator) {
    uint32 numeratorScale = numerator * scale;
    uint32 factorScale = numeratorScale / denominator;
    int32 resultScale = source * factorScale;
    int8 result = resultScale / scale;

    return result;
  }
};

int32 Fixed::scale = 1e4;

#endif
