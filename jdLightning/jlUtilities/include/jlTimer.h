/*****************************************************************************/
/**
 * @file    jlTimer.h
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
  
  using std::chrono::high_resolution_clock;
  using std::chrono::time_point;
  using std::chrono::duration;
  using std::chrono::duration_cast;

  class JL_UTILITY_EXPORT jlTimer {
   public:
    /**
     * @brief default constructor and start timing.
     */
     jlTimer();

    /**
     * @brief default destructor
     */
    ~jlTimer() {};

    /**
     * @brief Reset the timer to zero.
     */
    void
    reset();

    /**
     * @brief Returns time in milliseconds since timer was initialized or last reset.
     */
    uint64
    getMilliseconds() const;

    /**
     * @brief Returns time in microseconds since timer was initialized or last reset.
     */
    uint64
    getMicroseconds() const;

    /**
     * @brief Returns time in seconds since timer was initialized or last reset.
     */
    float
    getSeconds() const;

    /**
     * @brief Returns the time at which the timer was initialized, in milliseconds.
     * @return  Time in milliseconds.
     */
    uint64
    getStartMilliseconds() const;

		 private:
    /**
     * @brief A high resolution clock.
     */
    high_resolution_clock m_highResClock;

    /**
     * @brief the time point of the clock     
     */
    time_point<high_resolution_clock> m_startTime;
		};

}