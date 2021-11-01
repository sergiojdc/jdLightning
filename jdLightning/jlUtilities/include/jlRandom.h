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
#include "jlPlatformDefines.h"
#include "jlPlatformTypes.h"
#include "jlStdHeaders.h"
#include "jlPrerequisitesUtil.h"

namespace jlUtilitiesSDK {
  struct JL_UTILITY_EXPORT jlRandom
  {
    /**
     * @brief get two random numbers random with box miller math
     */
    static void
    RandomBoxMiller(float& result_a, float& result_b, float dMean, float dStdDeviation);

    /**
     * @brief get random float between 0 and 1
     * @return float between 0 and 1
     */
    static float
    randomFloat();

    /**
     * @brief get interger between 0 and 255
     * @return an interger between 0 and 255
     * @note recommended for colors
     */
    static uint32
    randomInt0_255();

    /**
     * @brief get interger between 0 and maxInt
     * @return an interger between 0 and maxInt
     * @note recommended for colors
     */
    static uint32
    randomInt();
  };
}