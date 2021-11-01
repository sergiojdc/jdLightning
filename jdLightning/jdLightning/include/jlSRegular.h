/*****************************************************************************/
/**
	* @file    jlSRegular.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    1/11/2021
	* @brief   A class for Regular sample
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlSampler.h"
#include <jlRandom.h>

class jlSRegular : public jlSampler {
 public:
		/**
			* @brief default constructor
			*/
		jlSRegular() = default;

		/**
			* @brief default constructor
			*/
		jlSRegular(uint32 numSamples) {
				m_numSamples = numSamples;
		};

		/**
			* @brief default destructor
			*/
		~jlSRegular() {};

		/**
			* @brief generate sample patterns in a unit square
			*/
		virtual void
		generateSamples() override {
				auto n = (int32)sqrt(m_numSamples);
				for (int p = 0; p < m_numSets; p++) {
						for (int j = 0; j < n; j++) {
								for (int k = 0; k < n; k++) {
										jlPoint2 sp((k + 0.5f) / n,
												          (j + 0.5f) / n);
										m_samples.push_back(sp);
								}
						}
				}
		};
};
