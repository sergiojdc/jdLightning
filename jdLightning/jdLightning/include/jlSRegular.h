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
				for (uint32 p = 0; p < m_numSets; p++) {
						for (int32 j = 0; j < n; j++) {
								for (int32 k = 0; k < n; k++) {
										float x = k + 0.5f;
										float y = j + 0.5f;
										//if ((k + 0.5f) / n > 0.5f)
										//		x = 1;
										//if ((j + 0.5f) / n > 0.5f)
										//		y = 1;

										x = x / n;
										y = y / n;
										jlVector2 sp(x, y);
										m_samples.push_back(sp);
								}
						}
				}
		};
};
