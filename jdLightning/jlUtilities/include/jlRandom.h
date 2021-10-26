/*****************************************************************************/
/**
 * @file    jlRandom.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   A basic class for random
 *
 *
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once
#include "jlPrerequisitesUtil.h"

namespace jlUtilitiesSDK {
  class JL_UTILITY_EXPORT Random
  {
   public:
    Random() {};
    ~Random() {};
    /**
     * @brief get two random numbers random with box miller math
     */
    static void
    RandomBoxMiller(float& result_a, float& result_b, float dMean, float dStdDeviation) {
      float x1 = 0, x2 = 0, w = 0, y1 = 0, y2 = 0;

      while (w >= 1.0f) {
        x1 = 2.0f * randomUnitFloat() - 1.0f;
        x2 = 2.0f * randomUnitFloat() - 1.0f;
        w = x1 * x1 + x2 * x2;
      }

      w = Math::sqrt((-2.0f * log(w)) / w);
      y1 = x1 * w;
      y2 = x2 * w;
      result_a = (dMean + y1 * dStdDeviation);
      result_b = (dMean + y2 * dStdDeviation);
      //return(m + y1 * s);
    }
   private:
    /**
     * @brief get random float between 0 and 1
     * @return float between 0 and 1
     */
    static float
    randomUnitFloat() {
      srand((unsigned int)time(NULL));
      return (float(rand()) / float((RAND_MAX)));
    }
    
    /**
     * @brief get random float
     * @return float
     */
    static float
    randomFloat() {
      srand((unsigned int)time(NULL));
      return float(rand());
    }

    /**
     * @brief get interger between 0 and 255
     * @return an interger between 0 and 255
     * @note recommended for colors
     */
    static float
    randomInt0_255() {
      srand((unsigned int)time(NULL));
      return int(rand()%256);
    }
  };
}