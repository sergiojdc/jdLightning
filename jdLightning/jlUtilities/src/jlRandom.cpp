#include "jlRandom.h"

namespace jlUtilitiesSDK {
  void
  jlRandom::RandomBoxMiller(float& result_a, float& result_b, float dMean, float dStdDeviation) {
    float x1 = 0, x2 = 0, w = 0, y1 = 0, y2 = 0;

    while (w >= 1.0f) {
      x1 = 2.0f * randomFloat() - 1.0f;
      x2 = 2.0f * randomFloat() - 1.0f;
      w = x1 * x1 + x2 * x2;
    }

    w = Math::sqrt((-2.0f * log(w)) / w);
    y1 = x1 * w;
    y2 = x2 * w;
    result_a = (dMean + y1 * dStdDeviation);
    result_b = (dMean + y2 * dStdDeviation);
    //return(m + y1 * s);
  }

  float
  jlRandom::randomFloat() {
    srand((unsigned int)time(NULL));
    return (float(rand()) / float((RAND_MAX)));
  }

  uint32
  jlRandom::randomInt0_255() {
    srand((uint32)time(NULL));
    return uint32(rand() % 256);
  }
  uint32 
  jlRandom::randomInt() {

    srand((uint32)time(NULL));
    return uint32(rand());
  }
}
