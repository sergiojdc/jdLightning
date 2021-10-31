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

class jlSJittered : public jlSample {
public:
		/**
			* @brief default constructor
			*/
		jlSJittered() = default;
		
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
				for (int p = 0; p < m_numSets; p++) {
						for (int j = 0; j < n; j++) {
								for (int k = 0; k < n; k++) {
										jlPoint2 sp((k + jlRandom::randomUnitFloat()) / n, 
												          (j + jlRandom::randomUnitFloat()) / n);
										m_samples.push_back(sp);
								}
						}
				}
		};

private:

};