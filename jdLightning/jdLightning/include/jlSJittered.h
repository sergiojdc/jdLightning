/*****************************************************************************/
/**
	* @file    jlSJittered.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    31/10/2021
	* @brief   A class for Jittered sample
	*
	*
	* @bug	    No known bugs.
	*/
/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlSampler.h"
#include <jlRandom.h>

class jlSJittered : public jlSampler {
 public:
		/**
			* @brief default constructor
			*/
		jlSJittered() = default;

		/**
			* @brief default constructor
			*/
		jlSJittered(uint32 numSamples) {
				m_numSamples = numSamples;
		};
		
		/**
			* @brief default destructor
			*/
		~jlSJittered() {};

  /**
   * @brief generate sample patterns in a unit square
   */
  virtual void
  generateSamples() override {
				auto n = (int32)sqrt(m_numSamples);
				for (uint32 p = 0; p < m_numSets; p++) {
						for (int32 j = 0; j < n; j++) {
								for (int32 k = 0; k < n; k++) {
										jlVector2 sp((k + jlRandom::randomFloat()) / n,
												           (j + jlRandom::randomFloat()) / n);
										m_samples.push_back(sp);
								}
						}
				}
		};
};
